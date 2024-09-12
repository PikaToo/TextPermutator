#include "file_permutator.h"
#include <iostream>

FilePermutator::FilePermutator(std::string path_to_instructions_directory, std::string path_to_text_base) {
    // Storing strings in class. This could be in an initializer list but would make the line very long.
    path_to_instruction_directory_ = path_to_instructions_directory;
    path_to_text_base_ = path_to_text_base;

    // Opening files.
    text_base_ = std::ifstream(path_to_text_base);

    // If failed to open files, send error warning.

    if (!text_base_.is_open()) {
        std::cerr << "Failed to open file: " << path_to_text_base << std::endl;
        return;
    }

    internal_output_file_ = InitialIndexedStringList(text_base_);
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
    internal_output_file_.createOutputFile(path_to_output);
}

int FilePermutator::popLineNumber(std::string& instruction) {
    std::istringstream iss (instruction);

    int line_number;

    if (iss >> line_number) {
        // Discard leading whitespace.
        iss >> std::ws;

        // Read value.
        std::string rest_of_string;
        getline(iss >> std::ws, rest_of_string);

        // Replace line to now exclude the line number. 
        instruction = rest_of_string;

        // Return line number.
        return line_number;
        
    } else {
        // Integer was not found.
        return -1;
    }
}
