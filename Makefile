enigma: main.o enigma.o helper.o
	g++ -g main.o enigma.o helper.o -o enigma

main.o: main.cpp enigma.h helper.h
	g++ -Wall -g -c main.cpp

helper.o: helper.cpp helper.h
	g++ -Wall -g -c helper.cpp

enigma.o: enigma.cpp enigma.h helper.h
	g++ -Wall -g -c enigma.cpp

clean:
	rm -f *.o enigma