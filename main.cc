/*
Main program to generate file permutation. 
Additionally contains #define parameters linked to desired directory, base file, and output file.

Requirements:
- C++17.

Compile as: g++ -o main main.cc file_permutator.cc initial_indexed_string_list.cc
Run with ./main.exe <instruction_name_1.txt> <instruction_name_2.tex> ...

Input: 
- Arguments containing file name of each desired instruction (e.g., 1.txt, addText.tex)
- Instructions must be of the following form:
    <int>_<string>
    Where _ is a whitespace character.
  Instructions add the <string> to the line number <int> of the text base file, you do NOT need to account for the lines
  shifting around as instructions occur, this is handled internally. Only number the line where you want it to be in the base file.
  Two instructions on the same number will be added in order, with the first one being higher up (lower end line number).
  An instruction that contains only a line number will add a blank line at line number <int>.

Output:
- File containing text base file with all added instructions.

*/

#include "file_permutator.h"

#define INSTRUCTIONS_DIRECTORY   "instructions/"
#define TEXT_BASE_FILE           "base_file.txt"
#define OUTPUT_FILE              "output.txt"

int main(int argc, char** argv) {
    // Initialize FilePermutator.
    FilePermutator fp (INSTRUCTIONS_DIRECTORY, TEXT_BASE_FILE);

    // Apply each instruction passed.
    for (int i = 1; i < argc; i++) {
        fp.processInstruction(argv[i]);
    }

    // Output.
    fp.createOutputFile(OUTPUT_FILE);    
}