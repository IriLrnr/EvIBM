.PHONY : build run clean doc options

SRC = $(wildcard source/*.c main.c)
OBJ = ${SRC:.c=.o}
CCFLAGS = -g -I/usr/include/gsl -O2 -Wall -c
LDFLAGS = -ansi -pedantic -Wall -lgsl -lgslcblas -lm

main : ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

options :
	@echo Options:
	@echo ${SRC}

%.o : %.c
	${CC} ${CCFLAGS} -o $@ $<

run : main
	./run.sh

clean:
	rm -f *.o out* run

doc:
	slip merge .source_doc.md > DOCUMENTATION.md
