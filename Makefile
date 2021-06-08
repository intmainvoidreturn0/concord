CC           ?= gcc
OBJDIR	     := obj
LIBDIR	     := lib
SPECSDIR     := specs-code
ACTOR_OBJDIR := actor_obj
SHELL        := /bin/bash

ACC          ?= gcc


# common src with utility functions
COMMON_SRC  := $(wildcard common/*.c) $(wildcard common/**/*.c)
CEE_UTILS_SRC  := $(wildcard cee-utils/*.c) 
# API specific src
DISCORD_SRC := $(wildcard discord-*.c)
SLACK_SRC   := $(wildcard slack-*.c)
GITHUB_SRC  := $(wildcard github-*.c)
REDDIT_SRC  := $(wildcard reddit-*.c)

DB_SRC      := $(wildcard sqlite3/*.c)

SPECS      	:= $(sort $(wildcard specs/*/*.json))
SPECS_SUBDIR:= $(sort $(patsubst specs/%, %, $(dir $(SPECS))))
SPECS_SRC   := $(patsubst specs/%, $(SPECSDIR)/%, $(SPECS:%.json=%.c))

ACTOR_GEN_SRC = cee-utils/orka-utils.c 	\
				cee-utils/json-actor.c 	\
				cee-utils/ntl.c 			\
				cee-utils/json-string.c 	\
				cee-utils/json-scanf.c 	\
				cee-utils/json-struct.c 	\
				cee-utils/json-printf.c 	\
				cee-utils/log.c \
				specs/specs-gen.c

ACTOR_GEN_OBJS := $(ACTOR_GEN_SRC:%=$(ACTOR_OBJDIR)/%.o)

CEE_UTILS_OBJS  := $(CEE_UTILS_SRC:%=$(OBJDIR)/%.o)
COMMON_OBJS  := $(COMMON_SRC:%=$(OBJDIR)/%.o)
DISCORD_OBJS := $(DISCORD_SRC:%=$(OBJDIR)/%.o)
SLACK_OBJS   := $(SLACK_SRC:%=$(OBJDIR)/%.o)
GITHUB_OBJS  := $(GITHUB_SRC:%=$(OBJDIR)/%.o)
REDDIT_OBJS  := $(REDDIT_SRC:%=$(OBJDIR)/%.o)
SPECS_OBJS   := $(SPECS_SRC:%=$(OBJDIR)/%.o)
DB_OBJS      := $(DB_SRC:%=$(OBJDIR)/%.o)

OBJS := $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(DISCORD_OBJS) $(SLACK_OBJS) $(GITHUB_OBJS) $(REDDIT_OBJS)

BOT_SRC  := $(wildcard bots/bot-*.c)
BOT_EXES := $(patsubst %.c, %.exe, $(BOT_SRC))

BOTX_SRC  := $(wildcard botx/bot-*.c)
BOTX_EXES := $(patsubst %.c, %.bx, $(BOTX_SRC))

BOTZ_SRC  := $(wildcard add-ons/bot-*.c)
BOTZ_EXES := $(patsubst %.c, %.bz, $(BOTZ_SRC))

TEST_SRC  := $(wildcard test/test-*.cpp test/test-*.c)
TEST_EXES := $(filter %.exe, $(TEST_SRC:.cpp=.exe) $(TEST_SRC:.c=.exe))

LIBDISCORD_CFLAGS	:= -I./ -I./mujs  -I./sqlite3 -I./add-ons
LIBDISCORD_LDFLAGS	:= -L./$(LIBDIR) -ldiscord -lpthread

ifeq ($(BEARSSL),1)
	LIBDISCORD_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL
else ifeq ($(CC),stensal-c)
	LIBDISCORD_LDFLAGS += -lcurl-bearssl -lbearssl -static
	CFLAGS += -DBEARSSL
	#LIBDISCORD_LDFLAGS += -lcurl-ssl -lssl -lcrypto -lm -static
else
	LIBDISCORD_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcurl -lcrypto -lm
endif


LIBS_CFLAGS  := $(LIBDISCORD_CFLAGS)
LIBS_LDFLAGS := $(LIBDISCORD_LDFLAGS)

LIBDISCORD   := $(LIBDIR)/libdiscord.a


CFLAGS += -Wall -std=c11 -O0 -g \
	-Wno-unused-function -Wno-unused-but-set-variable \
	-I. -I./cee-utils -I./common -I./common/third-party -DLOG_USE_COLOR

ifeq ($(release),1)
else
	CFLAGS +=  -D_STATIC_DEBUG
endif

ifeq ($(DEBUG_JSON),1)
	CFLAGS += -D_STRICT_STATIC_DEBUG
endif

ifeq ($(CC),stensal-c)
	CFLAGS += -D_DEFAULT_SOURCE
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif


PREFIX ?= /usr/local

.PHONY : install clean purge mujs
.ONESHELL:


all : mkdir cee_utils common discord | bots

get_cee_utils:
	if [[ ! -d cee-utils ]]; then \
		./scripts/get-cee-utils.sh; \
	fi

cee_utils: mkdir get_cee_utils $(CEE_UTILS_OBJS)
common: mkdir $(COMMON_OBJS)
discord: mkdir $(DISCORD_OBJS) libdiscord
slack: mkdir $(SLACK_OBJS)
github: mkdir $(GITHUB_OBJS)
reddit: mkdir $(REDDIT_OBJS)
db: mkdir $(DB_OBJS)

specs: mkdir $(SPECS_SRC) $(SPECS_OBJS)

echo:
	@echo SPECS:        $(SPECS)
	@echo SPECS_SRC:    $(SPECS_SRC)
	@echo SPECS_OBJS:   $(SPECS_OBJS)
	@echo SPECS_SUBDIR: $(SPECS_SUBDIR)
	@echo BOTZ_SRC:     $(BOTZ_SRC)
	@echo BOTZ_EXES:    $(BOTZ_EXES)

##@todo should we split by categories (bot_discord, bot_github, etc)?
bots: $(BOT_EXES)
botx: mkdir cee_utils common discord | $(BOTX_EXES)
botz: mkdir cee_utils common discord | $(BOTZ_EXES)

##@todo should we split by categories too ?
test: cee_utils common discord slack github reddit $(TEST_EXES)

mkdir :
	mkdir -p $(OBJDIR)/cee-utils
	mkdir -p $(ACTOR_OBJDIR)/cee-utils
	mkdir -p $(ACTOR_OBJDIR)/common/third-party  $(ACTOR_OBJDIR)/specs
	mkdir -p $(OBJDIR)/common/third-party $(LIBDIR)
	mkdir -p $(addprefix $(SPECSDIR)/, $(SPECS_SUBDIR)) $(addprefix $(OBJDIR)/$(SPECSDIR)/, $(SPECS_SUBDIR))
	mkdir -p $(OBJDIR)/test
	mkdir -p $(OBJDIR)/sqlite3 
	mkdir -p $(OBJDIR)/add-ons


$(ACTOR_OBJDIR)/%.c.o : %.c
	$(ACC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<

#generic compilation
$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<


all_headers: $(SPECS)
	rm -rf $(SPECSDIR)/*/all_*
	$(foreach var, $(SPECS),./bin/actor-gen.exe -S -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_structs.h) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -E -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_enums.h) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -F -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_functions.h) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -O -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_opaque_struct.h) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -c -o $(patsubst specs/%, $(SPECSDIR)/%, $(var:%.json=%.c)) $(var);)
	$(foreach var, $(SPECS),./bin/actor-gen.exe -d -o $(patsubst specs/%, $(SPECSDIR)/%, $(var:%.json=%.h)) $(var);)


actor-gen.exe: mkdir $(ACTOR_GEN_OBJS)
	$(ACC) -o $@ $(ACTOR_GEN_OBJS) -lm
	mkdir -p bin
	mv $@ ./bin

#generic compilation
%.bx:%.c discord mujs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) -lmujs -lsqlite3
%.bz:%.c discord mujs 
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) 
%.exe:%.c libdiscord mujs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) -lmujs

#API libraries compilation
libdiscord: mkdir $(OBJS) $(SPECS_OBJS)
	$(AR) -cvq $(LIBDISCORD) $(OBJS) $(SPECS_OBJS)

mujs:
	$(MAKE) -C mujs
	mkdir -p $(LIBDIR)
	cp mujs/build/release/libmujs.a $(LIBDIR)

install :
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/orca
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h cee-utils/*.h common/*.h common/**/*.h $(PREFIX)/include/orca/
	install -d $(PREFIX)/include/orca/$(SPECSDIR)/discord/
	install -m 644 $(SPECSDIR)/discord/*.h $(PREFIX)/include/orca/$(SPECSDIR)/discord/

specs_clean :
	rm -rf $(SPECSDIR)

clean : 
	rm -rf $(OBJDIR) *.exe test/*.exe bots/*.exe
	rm -rf botx/*.bx
	rm -rf $(LIBDIR)

clean_actor_gen:
	rm -rf $(ACTOR_OBJDIR) bin/*

purge : clean
	rm -rf $(LIBDIR)
	rm -rf $(ACTOR_OBJDIR)
	rm -rf cee-utils
