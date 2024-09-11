#include "file_permutator.h"

FilePermutator::FilePermutator(std::string path_to_instructions_directory, std::string path_to_text_base) {
    // Storing strings in class. This could be in an initializer list but would make the line very long.
    path_to_instruction_directory_ = path_to_instructions_directory;
    path_to_text_base_ = path_to_text_base;

    // Opening files.
    instructions_ = std::ifstream(path_to_instructions_directory);
    text_base_ = std::ifstream(path_to_text_base);

    // If failed to open files, send error warning.

    if (!text_base_.is_open()) {
        std::cerr << "Failed to open file: " << path_to_text_base << std::endl;
        return;
    }

    // Getting base file converted into vector of strings to then build on.
    for (std::string line; getline(text_base_, line); ) {
        internal_output_file_.push_back(line);
    }
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

        // If failed to read, exit.
        if (line_to_add == -1) {
            std::cerr << "Instruction failed to follow proper formatting:" << std::endl << line << std::endl;
            return;
        }
        
        // If fails to add line because it's index is below possible value, exit.
        if (line_to_add < 1) {
            std::cerr << "Line index was not possible to achieve" << std::endl << line_to_add << std::endl << line << std::endl;
            return;
        }

        // If adding to line beyond what exists, add blank lines.
        while (line_to_add > internal_output_file_.size()) {
            internal_output_file_.push_back("");
        }

        // Add line. Subtracts 1 from line_to_add because of 0-indexing of vector but 1-indexing of line numbers.
        //      This causes the new line added to be positioned where the old line of the same number was,
        //      pushing the old line forward 1.
        internal_output_file_.insert(internal_output_file_.begin() + line_to_add-1, line);
    }
}

void FilePermutator::createOutputFile(std::string path_to_output) {
    std::ofstream out ("output.txt");
    for (std::string line : internal_output_file_) {
        out << line << std::endl;
    }
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
