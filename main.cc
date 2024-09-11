#include <fstream> 
#include <sstream>
#include <iostream> 
#include <string> 
#include <vector>
#include <ctype.h>

using namespace std;

#define INSTRUCTIONS_FILE   "instructions.txt"
#define LATEX_BASE_FILE     "latex_base.tex"

/*
Input: a string from the instruction file following expected syntax as follows:<integer> <string> 
Output: the integer in at the start of the instruction. The string provided is mutated as to remove 
        this integer and the space, leaving just:<string>
*/ 
int get_line_position (string& line) {
    istringstream iss (line);

    int num;

    if (iss >> num) {
        // Discard leading whitespace, then replace line to now exclude the starting integer.
        getline(iss >> std::ws, line);
        return num;
        
    } else {
        // Integer was not found.
        return -1;
    }
}

int main() {
    // Opening files.
    ifstream instructions (INSTRUCTIONS_FILE);
    ifstream latex_base (LATEX_BASE_FILE);

    // If failed to open files, send error warning.
    if (!instructions.is_open()) {
        cerr << "Failed to open file: " << INSTRUCTIONS_FILE << endl;
        return -1;
    }

    if (!latex_base.is_open()) {
        cerr << "Failed to open file: " << LATEX_BASE_FILE << endl;
        return -1;
    }

    // Getting base file converted into vector of strings to then build on.
    vector<string> file_vector;
    for (string line; getline(latex_base, line); ) {
        file_vector.push_back(line);
    }

    // Reading instructions. 
    for (string line; getline(instructions, line); ) {

        int line_to_add = get_line_position(line);

        // If failed to read, exit.
        if (line_to_add == -1) {
            cerr << "Instruction failed to follow proper formatting:" << endl << line << endl;
            return -1;
        }
        
        // If fails to add line because it's index is below possible value, exit.
        if (line_to_add < 1) {
            cerr << "Line index was not possible to achieve" << endl << line_to_add << endl << line << endl;
            return -1;
        }

        // If adding to line beyond what exists, add blank lines.
        while (line_to_add > file_vector.size()) {
            file_vector.push_back("");
        }

        // Add line. Subtracts 1 from line_to_add because of 0-indexing of vector but 1-indexing of line numbers.
        //      This causes the new line added to be positioned in where the old line of the same number was,
        //      pushing the old line forward 1.
        file_vector.insert(file_vector.begin() + line_to_add-1, line);
    }

    // Write file to output.
    ofstream out ("output.txt");
    for (string line : file_vector) {
        out << line << endl;
    }
    return 1;
}