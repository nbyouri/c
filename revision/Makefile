CC=	clang
CFLAGS=	-Weverything
#CFLAGS+= -g
LDFLAGS=	
SRCS=	main.c init.c index.c search.c files.c
TARGET=	class

all:
	${CC} ${CFLAGS} ${SRCS} -o ${TARGET}

clean:
	if [ -f *.o ]; then rm *.o; fi
	if [ -f ${TARGET} ]; then rm ${TARGET}; fi
