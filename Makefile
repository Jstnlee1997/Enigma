enigma: main.o enigma.o plugboard.o reflector.o rotor.o
	g++ -g main.o enigma.o plugboard.o reflector.o rotor.o -o enigma

main.o: main.cpp enigma.h plugboard.h reflector.h rotor.h
	g++ -Wall -g -c main.cpp

plugboard.o: plugboard.cpp plugboard.h
	g++ -Wall -g -c plugboard.cpp

reflector.o: reflector.cpp reflector.h
	g++ -Wall -g -c reflector.cpp

rotor.o: rotor.cpp rotor.h
	g++ -Wall -g -c rotor.cpp

enigma.o: enigma.cpp enigma.h reflector.h plugboard.h rotor.h
	g++ -Wall -g -c enigma.cpp

clean:
	rm -f *.o enigma