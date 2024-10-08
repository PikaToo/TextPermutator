#include "file_permutator.h"
#include <iostream>

FilePermutator::FilePermutator(std::string path_to_instructions_directory, std::string path_to_text_base) : internal_output_file_(path_to_text_base) {
    // Storing strings in class. This could be in an initializer list but would make the line very long.
    path_to_instruction_directory_ = path_to_instructions_directory;
}

void FilePermutator::processInstruction(std::string instruction_file_name) {
    // Open file.
    std::string path = path_to_instruction_directory_ + instruction_file_name;
    std::ifstream instructions (path);

    if (!instructions.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    // Apply instruction.
    for (std::string line; getline(instructions, line); ) {
        int line_to_add = popLineNumber(line);
        internal_output_file_.addString(line_to_add, line);
    }
}

void FilePermutator::createOutputFile(std::string path_to_output) {
    std::ofstream out (path_to_output);
    for (std::string& p : internal_output_file_) {
        out << p << std::endl;
    }
}

int FilePermutator::popLineNumber(std::string& instruction) {
    std::istringstream iss (instruction);

    int line_number;

    if (iss >> line_number) {
        // Discard single whitespace.
        iss.ignore();

        // Read value.
        std::string rest_of_string;
        getline(iss, rest_of_string);

        // Replace line to now exclude the line number. 
        instruction = rest_of_string;

        // Return line number.
        return line_number;
        
    } else {
        // Integer was not found.
        return -1;
    }
}
