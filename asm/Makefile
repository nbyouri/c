ASM=	yasm -f macho64
LD=		ld -macosx_version_min 10.5
SRCS=	hello.asm
TARGET=	hello

all:
	${ASM} ${SRCS} -o ${TARGET}.o
	${LD} ${TARGET}.o -o ${TARGET}

clean:
	rm ${TARGET} ${TARGET}.o
