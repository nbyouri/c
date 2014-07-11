CC=	cc 
SRCS=	fetch.c 
CFLAGS=	-Weverything -I/usr/pkg/include 
LDFLAGS=-L/usr/pkg/lib -lfetch -lssl -lcrypto -lxmalloc
TARGET=	fetch

all:
	${CC} ${SRCS} ${CFLAGS} ${LDFLAGS} -o ${TARGET}
