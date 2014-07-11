CC=	cc 
SRCS=	fetch.c 
CFLAGS=	-Weverything -I/usr/pkg/include 
LDFLAGS=-L/usr/pkg/lib -lfetch -lssl -lcrypto -lxmalloc -lprogressmeter
TARGET=	fetch

all:
	${CC} ${SRCS} ${CFLAGS} ${LDFLAGS} -o ${TARGET}

install:
	test -d ${DESTDIR}${PREFIX}/bin || mkdir -p ${DESTDIR}${PREFIX}/bin
	install -pm 755 fetch ${DESTDIR}${PREFIX}/bin

clean:
	rm ${TARGET}
