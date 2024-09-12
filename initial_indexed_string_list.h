#ifndef INITIAL_INDEXED_STRING_LIST_H
#define INITIAL_INDEXED_STRING_LIST_H

#include <string>
#include <fstream>
#include <unordered_map>

class ListNode {
    public:
        std::string value;
        ListNode* next;
        ListNode* prev;
        ListNode() : value{0}, next{nullptr}, prev{nullptr} {}
        ListNode(std::string value) : value{value}, next{nullptr}, prev{nullptr} {}
        ListNode(std::string value, ListNode* next, ListNode* prev) : value{value}, next{next}, prev{prev} {}
};

/*
A class that holds a list of strings that is only indexed once at the start. 
    All subsequent additions to the list will be placed and stored, but will not change indexing.
    These additions will be placed right before the index requested, but after the index of the previous node.
    These non-initial nodes can be only accessed through the class' iterator. 
*/
class InitialIndexedStringList {
    public:
        /*
        Constructor. Note the default constructor is only here to allow you to initialize a class containing
            an InitialIndexedStringList, but the class will be useless. The starting string values are required to have
            an initial string list, which are obtained from an ifstream. The ifstream is mutated until fully iterated. 
        */
        InitialIndexedStringList();
        InitialIndexedStringList(std::ifstream& starting_file);

        /*
        Adds an unindexed string to the string list. 
        */
        void addString(int index, std::string const& line_text);

        /*
        Iterator through the class intended primarily for range-based for loops. 
        */
        class iterator {
            private: 
                ListNode* p;
                iterator(ListNode* p); 
                
            public: 
                bool operator!=(const iterator& other) const; 
                std::string& operator*(); 
                iterator& operator++();
            
            friend class InitialIndexedStringList;
        };

        iterator begin();
        iterator end();

    // Internal implementation details. 
    private:
        // Linked list used internally. 
        ListNode* head_;

        // Map of line number to where in linked list item should be inserted. 
        std::unordered_map<int, ListNode*> items_;
        int final_line_;
};

#endif // INITIAL_INDEXED_STRING_LIST_H