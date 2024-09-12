#include "initial_indexed_string_list.h"
#include <iostream>

InitialIndexedStringList::InitialIndexedStringList() {}
InitialIndexedStringList::InitialIndexedStringList(std::ifstream& starting_file) {
    // Head is a dummy head not actually part of the file. 
    // We set it as 0 to be able to access it later.
    head_ = new ListNode(); 

    // Adding nodes and mapping them. 
    ListNode* cur = head_;
    int line_number = 1;

    for (std::string line; getline(starting_file, line); ) {
        // Create the ith line. 
        cur->next = new ListNode(line, nullptr, cur);

        // Update cur so that it points to the ith line.
        cur = cur->next;
        
        // Line number i is mapped to the node we just created.
        items_[line_number] = cur;
        
        line_number++;
    }

    // Final line is inclusive of the final line. 
    final_line_ = line_number - 1;
}

/*
Adds a string as a node. 
*/
void InitialIndexedStringList::addString(int line_position, std::string const& line_text) {
    // If failed to read, exit.
    if (line_position == -1) std::cerr << "Instruction failed to follow proper formatting:" << std::endl << line_text << std::endl;

    // If fails to add line because it's index is below possible value, exit.
    else if (line_position < 1) std::cerr << "Line index is lower than 1: " << std::endl << line_position << std::endl << line_text<< std::endl;
    
    // If adding to line beyond what exists, exit. 
    else if (line_position > final_line_) std::cerr << "Line index is larger than file's largest line index: " << std::endl << line_position << std::endl << line_text << std::endl;
    
    // Add the node.
    else {
        // Get the node at the expected position. 
        ListNode* line_node = items_[line_position];
        
        // Make the new node and set my next to the original node, and my prev to the one before. 
        ListNode* new_node = new ListNode{line_text, line_node, line_node->prev};
        
        // Set the prev node's next to me, and set the next node's prev to me. 
        (line_node->prev)->next = new_node;
        line_node->prev = new_node;
    }
}

/*
*/
void InitialIndexedStringList::createOutputFile(std::string path_to_output) {
    std::ofstream out (path_to_output);
    ListNode* cur = head_->next;
    while (cur) {
        out << cur->value << std::endl;
        cur = cur->next;
    }
}