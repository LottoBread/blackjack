# Example makefile for CPE 464
#

CC = g++
CFLAGS = -g -Wall -Werror
OS = $(shell uname -s)
PROC = $(shell uname -p)
EXEC_SUFFIX=$(OS)-$(PROC)

ifeq ("$(OS)", "SunOS")
	OSLIB=-L/opt/csw/lib -R/opt/csw/lib -lsocket -lnsl
	OSINC=-I/opt/csw/include
	OSDEF=-DSOLARIS
else
ifeq ("$(OS)", "Darwin")
	OSLIB=
	OSINC=
	OSDEF=-DDARWIN
else
	OSLIB=
	OSINC=
	OSDEF=-DLINUX
endif
endif

all:  blackjack-tcp-$(EXEC_SUFFIX)

blackjack-tcp-$(EXEC_SUFFIX): blackjack-tcp.cpp
	$(CC) $(CFLAGS) $(OSINC) $(OSLIB) $(OSDEF)  -o $@ blackjack-tcp.cpp server.cpp Client.cpp Deck.cpp

clean:
	-rm -rf blackjack-tcp-* blackjack-tcp-*.dSYM