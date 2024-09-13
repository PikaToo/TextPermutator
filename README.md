# TextPermutator
This is a C++17 program that allows you to quickly add different combinations of text onto a base text file, quickly allowing you to get different permutations of the text that you want. 
You can write instructions in different files in the instructions directory, with each line in each instruction file telling a line to add at a specific line number. 
Then, you can run the program with each file desired to be added as a parameter and all the text you specified will be added to the base file and given as an output file.  

## How To Use
### 1. Compiling the Program (once)
You will need C++ to compile this. C++17 or higher is required. Run the following command to compile the program:

`g++ -o main main.cc file_permutator.cc initial_indexed_string_list.cc`

Note this step only ever has to be done once, unless you edit parameters within the files. 

### 2. Getting your Base File
Modify base_file.txt to contain the starting file you would like to have before adding additional lines into it. 

You can change the name of this file, as long as you also change it in main.cc (labelled 'TEXT_BASE_FILE' in the #define). Remember to recompile if you do this. 

Note that any empty lines at the end of this file are ignored.


### 3. Creating Instructions
Add additional files into the instructions subdirectory. You can rename this directory like with the base file from main.cc (labelled INSTRUCTIONS_DIRECTORY in the #define).

Each file needs to follow proper syntax:
- The first character(s) of the file should be a line number.
  -  This line number must be between 1 and the line number of the final non-empty line of your base file.
  -  The line number you write should be based on where you want the text to appear in the the base file.
  -  The program automatically accounts for lines shifting when more text is added, so only place it where you would like it relative to the base file. 
  - Telling two instructions to place at the same line will cause them to be one after the other in order, with the first instruction being the first in the text document. 
- The next character should be a whitespace character (e.g., a space).
- After this, add the text you would like to be added at the line number. 


A line with just a number and no text can be used to create a new blank line at that line. 

See an example of instructions at sample.txt


### 4. Running the Program
Run with `./main.exe <instruction_name_1.txt> <instruction_name_2.tex> ...`

You can rename the output file from main.cc (labelled OUTPUT_FILE in the #define).

Ensure you include the file extension of each file. 
