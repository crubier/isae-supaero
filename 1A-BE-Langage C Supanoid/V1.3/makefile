CC=gcc

CCOPTS=-g -Wall

PLATFORM=linux

JNI_INCL=-Iinclude -Iinclude/${PLATFORM}

JVM_CLIENT_PATH=/usr/java/jdk/jre/lib/i386/client

supanoid: main.o graphic.o 
	${CC} main.o graphic.o ${CCOPTS} -L${JVM_CLIENT_PATH} -ljvm -o supanoid

main.o:	main.c
	${CC} ${CCOPTS} -c main.c 

graphic.o: graphic.c graphic.h key.h
	${CC} ${CCOPTS} ${JNI_INCL} -c graphic.c 

clean:
	rm *.o supanoid

