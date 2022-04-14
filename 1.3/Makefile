PROGRAMM = main
KOMPILAATOR = gcc
LIPUD = `pkg-config --cflags gtk+-3.0`
TEEGID = `pkg-config --libs gtk+-3.0`

${PROGRAMM}: ${PROGRAMM}.c
	${KOMPILAATOR} ${LIPUD} -o ${PROGRAMM} ${PROGRAMM}.c ${TEEGID}
