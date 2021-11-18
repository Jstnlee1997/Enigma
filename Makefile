objects = main.o enigma.o plugboard.o reflector.o rotor.o
headers = enigma.h src/plugboard.h src/reflector.h src/rotor.h

enigma: $(objects)
	g++ -g $(objects) -o enigma

main.o: $(headers)

enigma.o: $(headers)

plugboard.o: src/plugboard.h
	g++ -Wall -g -c src/plugboard.cpp

reflector.o: src/reflector.h
	g++ -Wall -g -c src/reflector.cpp

rotor.o: src/rotor.h
	g++ -Wall -g -c src/rotor.cpp

.PHONY: clean
clean:
	rm -f $(objects) enigma