CC=			clang
SRCS=		gmpd.c
TARGET=		gmpd
CFLAGS=		-Wall $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS=	$(shell pkg-config --libs gtk+-3.0)

all:
	${CC} ${SRCS} -o ${TARGET} ${CFLAGS} ${LDFLAGS}
clean:
	rm ${TARGET}
