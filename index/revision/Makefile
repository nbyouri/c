CC=	clang -Weverything
SRCS=	main.c init.c index.c search.c files.c tools.c

OBJS= $(SRCS:.c=.o)

.PHONY: clean class

class: ${OBJS}
	${CC} -o class ${OBJS} 

clean:
	rm *.o
	rm class
	rm -r data
