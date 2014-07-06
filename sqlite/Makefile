CC=	clang
CFLAGS=	-Weverything -I/usr/pkg/include
LDFLAGS=	-L/usr/pkg/lib -lsqlite3
SRCS=	sqlite.c
TARGET=	db_query

all:
	${CC} ${CFLAGS} ${SRCS} ${LDFLAGS} -o ${TARGET}
