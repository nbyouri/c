SRC=	pkgin.c
TARGET=	pkgin
CFLAGS=	-Wall -I/usr/pkg/include
LDFLAGS=	-L/usr/pkg/lib -lList -lsqlite3

all:
	cc ${SRC} ${CFLAGS} ${LDFLAGS} -o ${TARGET}
