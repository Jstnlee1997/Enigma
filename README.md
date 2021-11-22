# Enigma
During WW2, German military used an Enigma machine to encrypt/decrypt messages.   
Combining three rotors from a set of five, each of the 3 rotor settings with 26 positions, and the plugboard with ten pairs of letters connected, 
the military Enigma has **158,962,555,217,826,360,000** different combinations (nearly 159 quintillion or about 67 bits).

## Rules
Letter configurations are represented by their corresponding numbers:  
 i.e. 'A' -> 0, 'B' -> 1, ..., 'Z' -> 25
### Plugboards
> - Requires even number of numbers with no repetitions
> - Numbers are mapped to their counterparts
> - Can have 0 - 13 pairs
### Reflectors
> - Requires exactly 13 pairs of numbers (all letters must be mapped)
> - There cannot be any repetitions
### Rotors
> CONFIGURATION FILES (.rot)
> - Can have *as many rotors* as you want (but also none)
> - Each rotor file needs to **FIRST**:  
consist of exactly 13 pairs of numbers (all letters must be mapped)
> - There cannot be any repetitions
> - **SECOND**: Include optional notches after (up to 26 notches), where rotors would only rotate the next rotor if they land on a notch position
> - There cannot be any repetitions

> POSITION FILE (.pos)
> - Starting positions of each rotor (neutral position is 0)
> - Must include one number for each configuration file

## Instructions
1. Clone the repository into your local machine

2. Configure/create any plugboards, reflectors, or rotors files (in their respective folders)

3. Execute the command `make` to compile the program

4. Run the executable, along with your desired plugboard, reflector, and rotor file(s) e.g.:  
`./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos` (Three rotor files)

5. Type in your desired message to encrypt/decrypt, ensuring each character is a **CAPITAL LETTER**

6. Try running the program again and type in the result of your encrypted message, enjoy!!! 
