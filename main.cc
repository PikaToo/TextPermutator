/*
Requirements:
- C++17.

Main program to generate file permutation. 
Additionally contains #define parameters linked to desired directory, base file, and output file.

Input: 
- Arguments containing file name of each desired instruction (e.g., 1.txt, addText.tex)
- Instructions must be of the following form:
    <int>_<string>
    Where _ is a whitespace character.
  Instructions add the <string> to the line number <int> of the text base file.
  An instruction that contains only a line number will add a blank line at line number <int>.

Output:
- File containing text base file with all added instructions.

*/

#include "file_permutator.h"

using namespace std;

#define INSTRUCTIONS_DIRECTORY   "instructions/"
#define TEXT_BASE_FILE           "latex_base.tex"
#define OUTPUT_FILE              "output.tex"

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