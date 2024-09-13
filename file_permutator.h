#ifndef FILE_PERMUTATOR_H
#define FILE_PERMUTATOR_H

#include "initial_indexed_string_list.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

/*
A class that handles all actions to permute text bases according to instructions. 
*/
class FilePermutator {
    public:
        /*
        Constructor. Requires: 
            - the path to the directory containing all instructions
            - the path to the text base
        Additionally, initializes the internal output file with the text base.
        */
        FilePermutator(std::string path_to_instruction_text_base, std::string path_to_text_bases);

        /*
        Applies an instruction into the internal output file.
        */
        void processInstruction(std::string instruction_file_name);

        /*
        Outputs the internal output file into a file of path specified. 
        */
        void createOutputFile(std::string path_to_output);

    private:
        // Removes the line number from a correctly formatted instruction line and returns it.
        int popLineNumber(std::string& instruction);

        // ifstream containing the contents of the instructions file and text base file respectively.
        std::ifstream instructions_;

        // Path strings.
        std::string path_to_instruction_directory_;

        // Internal output file. Used to construct the output file.
        InitialIndexedStringList internal_output_file_;
};

#endif // FILE_PERMUTATOR_H