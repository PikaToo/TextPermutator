#ifndef HASHMAPPED_LINKED_LIST_H
#define HASHMAPPED_LINKED_LIST_H

#include <string>
#include <fstream>
#include <unordered_map>

/*

*/
class HashmappedLinkedList {
    public:
        /*
        */
        HashmappedLinkedList();
        HashmappedLinkedList(std::ifstream& starting_file);

        /*
        */
        void addNode(int line_position, std::string const& line_text);

        /*
        */
        void createOutputFile(std::string path_to_output);

    private:
        // Linked list used internally. 
        class ListNode {
            public:
                std::string value;
                ListNode* next;
                ListNode* prev;
                ListNode() : value{0}, next{nullptr}, prev{nullptr} {}
                ListNode(std::string value) : value{value}, next{nullptr}, prev{nullptr} {}
                ListNode(std::string value, ListNode* next, ListNode* prev) : value{value}, next{next}, prev{prev} {}
};
        ListNode* head_;

        // Map of line number to where in linked list item should be inserted. 
        std::unordered_map<int, ListNode*> items_;
        int final_line_;
};

#endif // HASHMAPPED_LINKED_LIST_H