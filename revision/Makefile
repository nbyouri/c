CC=	clang
#CFLAGS+= -g
LDFLAGS=	
SRCS=	main.c init.c index.c search.c files.c tools.c
TARGET=	class

all:
	${CC} ${CFLAGS} ${SRCS} -o ${TARGET}

clean:
	if [ -f *.o ]; then rm *.o; fi
	if [ -f ${TARGET} ]; then rm ${TARGET}; fi
	if [ -f *.txt ]; then rm *.txt; fi
	if [ -f *.bin ]; then rm *.bin; fi
