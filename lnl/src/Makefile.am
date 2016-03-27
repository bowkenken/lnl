#

# Debug

if CHK_DEBUG
#CFLAGS_DEBUG = -p -DDEBUG -DD_TEST_TRAP
CFLAGS_DEBUG = -p -DDEBUG
else
CFLAGS_DEBUG = -DNDEBUG
endif

# Clock

if CHK_DEF_CLK_TCK
CFLAGS_CLK_TCK = '-DCLK_TCK=1000000'
endif

# Mac

if CHK_MAC
CFLAGS_MAC = '-arch ppc -arch i386'
LDFLAGS_MAC = '-arch ppc -arch i386'
endif

#
AM_CFLAGS = $(CFLAGS_DEBUG) $(CFLAGS_CLK_TCK) $(CFLAGS_MAC) -Wall
AM_LDFLAGS = $(CFLAGS_MAC)

bin_PROGRAMS = lnl
lnl_SOURCES = \
	abl-kind.h amenu-prot.h amenu-tab.h amenu.c amenu.h call-prot.h \
	call.cpp chr-prot.h chr.c chr.h class-dflt-tab.h class-tab.h \
	skill.c skill.h skill-prot.h skill-tab.h \
	config.h crsr-ptn.h curs-def.h curs-prot.h curs.c curs.h \
	draw-prot.h draw-tab.h draw.c draw.h \
	dun-prot.h dun-tab.h dun.c dun.h \
	map-event-prot.h map-event.h map-event.c \
	extern.h fight-prot.h fight.c fight.h \
	fx-menu-tab.h fx-prot.h fx.c fx.h \
	gf-conf.c gf-crsr.c gf-gconf.c gf-outmap.c gf-replay.c gf-save.c \
	gf-town.c gfile-prot.h gfile-tab.h gfile-ver.h gfile.c gfile.h \
	gmain-prot.h gmain.c gmain.h imenu-prot.h imenu-tab.h imenu.c \
	inc.h item-acce-tab.h item-anthology-tab.h item-armor-tab.h \
	item-coin-tab.h item-food-tab.h item-inst-tab.h item-kind.h \
	item-light-tab.h item-pipe-tab.h item-potion-tab.h item-prot.h \
	item-range-tab.h item-rare-goods-tab.h item-scroll-tab.h \
	item-stick-tab.h item-tab.h item-tobacco-tab.h item-wpn-tab.h \
	item-randm-art.h item-randm-art-tab.h \
	item.c item.h \
	main-prot.h \
	main-unix-prot.h main-unix.c menu-prot.h menu-tab.h menu.c \
	menu.h misc-prot.h misc.c misc.h mmenu-prot.h mmenu-tab.h \
	mmenu.c mnstr-act-prot.h mnstr-act.c mnstr-gen-tab.h \
	mnstr-kind.h mnstr-prot.h mnstr-tab.h mnstr.c mnstr.h \
	msg-eng.h msg-jpn-utf8.h msg-jpn-sjis.h msg-jpn.h \
	msg-prot.h msg-t.h msg.c \
	msg.h nest-flg-prot.h nest-flg.c nest-flg.h \
	party-prot.h party.c party.h pet-prot.h pet.c pet.h \
	play-rep-prot.h play-rep.c play-rep.h \
	replay.c replay.h replay-prot.h \
	request-prot.h \
	request-tab.h request.c request.h resi.h rumor-tab.h \
	scene-prot.h scene.c scene.h \
	spell-gen-tab.h spell-kind.h spell-prot.h spell-tab.h \
	spell.c spell.h \
	stay-inn-kind.h \
	tmenu-prot.h tmenu-tab.h tmenu.c town-prot.h town-tab.h \
	town.c town.h trap-prot.h trap.c trap.h turn-prot.h turn.c \
	turn.h ver.h vfx-kind.h \
	win-kind.h music-kind.h sound-kind.h joy-kind.h \
	key-item.c key-item.h key-item-prot.h \
	last-boss.c last-boss.h last-boss-prot.h last-boss-tab.h \
	ending-ep.c ending-ep.h ending-ep-prot.h \
	ending-space.c ending-space.h ending-space-prot.h 

# main-dos-prot.h main-dos.c


#bin_SCRIPTS = msg.h
msg-jpn-utf8.h: msg-jpn.h 
	./msg-cv-utf8

msg.h: msg-eng.h msg-jpn.h msg-jpn-utf8.h
	./msg-def

EXTRA_DIST = \
	msg-def msg-def-sub msg-cv-utf8 town-ptn.xpm \
	main-dos.c main-dos-prot.h \
	lnl-dos/AssemblyInfo.cpp lnl-dos/ReadMe.txt \
	lnl-dos/app.ico lnl-dos/app.rc lnl-dos/config-dos.h \
	lnl-dos/lnl-dos.cpp lnl-dos/resource.h lnl-dos/stdafx.cpp \
	lnl-dos/stdafx.h
