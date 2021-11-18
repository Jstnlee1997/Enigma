objects = main.o enigma.o src/plugboard.o src/reflector.o src/rotor.o
headers = enigma.h src/plugboard.h src/reflector.h src/rotor.h

enigma: $(objects)
	g++ -g $(objects) -o enigma

main.o: $(headers)

enigma.o: $(headers)

src/plugboard.o: src/plugboard.h

src/reflector.o: src/reflector.h

src/rotor.o: src/rotor.h

.PHONY: clean
clean:
	rm -f *.o enigma