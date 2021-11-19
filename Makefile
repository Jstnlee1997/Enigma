objects = main.o enigma.o plugboard.o reflector.o rotor.o
headers = enigma.h plugboard.h reflector.h rotor.h

enigma: $(objects)
	g++ -g $(objects) -o enigma

main.o: $(headers)

enigma.o: $(headers)

plugboard.o: plugboard.h

reflector.o: reflector.h

rotor.o: rotor.h

.PHONY: clean
clean:
	rm -f $(objects) enigma