WARNING_FLAGS = -Wall -Wextra -Werror -Wformat\
				-fstrict-overflow -Wstrict-overflow=2\
				-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes\
				-Wmissing-prototypes -Wcast-align

CFLAGS = -std=c99 -m64 -O3 $(WARNING_FLAGS)

CLIBS =lib/libisentlib.a -lm -lGL -lGLU -lglut -lX11

all: main.o  moteur.o  affichage.o outils.o
	gcc -o main main.o  moteur.o  affichage.o outils.o $(CLIBS)



main.o:	main.c modules/moteur.h modules/affichage.h
	indent --line-length200 -linux -bl -bli0  main.c
	gcc $(CFLAGS) -c main.c

moteur.o : modules/moteur.c modules/moteur.h
	indent --line-length200 -linux -bl -bli0  modules/moteur.c modules/moteur.h
	gcc $(CFLAGS) -c modules/moteur.c

affichage.o: modules/affichage.c modules/affichage.h
	indent --line-length200 -linux -bl -bli0  modules/affichage.c modules/affichage.h
	gcc $(CFLAGS) -c modules/affichage.c

outils.o: modules/outils.c modules/outils.h
	indent --line-length200 -linux -bl -bli0  modules/outils.c modules/outils.h
	gcc $(CFLAGS) -c modules/outils.c

unitTester: unitTester.o  moteur.o  affichage.o outils.o
	gcc -o unitTester unitTester.o  moteur.o  affichage.o outils.o $(CLIBS)
	rm *~

unitTester.o:	unitTester.c modules/moteur.h modules/affichage.h
	indent --line-length200 -linux -bl -bli0  unitTester.c
	gcc $(CFLAGS) -c unitTester.c

clean:
	rm -f *.o
	rm -f main unitTester
	rm -f modules/*~
