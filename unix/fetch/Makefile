CC=	cc 
PREFIX=	/usr/pkg
SRCS=	fetch.c 
CFLAGS=	-I/usr/pkg/include  -Wall
LDFLAGS=-L/usr/pkg/lib -lfetch -lssl -lcrypto -lxmalloc -lprogressmeter
TARGET=	fetch

all:
	${CC} ${SRCS} ${CFLAGS} ${LDFLAGS} -o ${TARGET}

install:
	test -d ${DESTDIR}${PREFIX}/bin || mkdir -p ${DESTDIR}${PREFIX}/bin
	install -pm 755 ${TARGET} ${DESTDIR}${PREFIX}/bin/${TARGET}

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/${TARGET}

clean:
	rm ${TARGET}
