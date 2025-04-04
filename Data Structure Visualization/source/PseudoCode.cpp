#include "../header/PseudoCode.h"

namespace PseudoCode {
    std::string LLInsertHead =
        "  Create new node with x\n"
        "  Set new node's next to head\n"
        "  Set new node as head\n";
    std::string LLInsertPos =
        "  Traverse to pos-1\n"
        "  If node found:\n"
        "    Create new node with x\n"
        "    Set new node's next to current node's next\n"
        "    Set current node's next to new node\n";

    std::string LLRemove =
        "If list is empty, return false\n"
        "If head node's data is x:\n"
        "  Remove head node\n"
        "  Return true\n"
        "Else:\n"
        "  Traverse to find node whose next node's data is x\n"
        "  If node found:\n"
        "    Set current node's next to next node's next\n"
        "    Delete node with data x\n";

    std::string LLSearch =
        "Traverse list to find node with data x\n"
        "If node found, return true\n"
        "If node not found, return false\n";


    std::string TreapInsert =
        "If tree is empty, create new node with key and priority\n"
        "If key < current node's key:\n"
        "  Insert into left subtree\n"
        "  If left child's priority > current node's priority, rotate right\n"
        "Else:\n"
        "  Insert into right subtree\n"
        "  If right child's priority > current node's priority, rotate left\n";

    std::string TreapRemove =
        "If tree is empty, return\n"
        "If key < current node's key, remove from left subtree\n"
        "Else if key > current node's key, remove from right subtree\n"
        "Else (current node's key == key):\n"
        "  If node has no children, delete it\n"
        "  Else if node has only left child, replace with left child\n"
        "  Else if node has only right child, replace with right child\n"
        "  Else:\n"
        "    If left child's priority > right child's priority\n" 
        "       Rotate right and remove from right subtree\n"
        "    Else, rotate left and remove from left subtree\n";

    std::string TreapSearch =
        "If tree is empty, return nullptr\n"
        "If key == current node's key, return current node\n"
        "If key < current node's key, search in left subtree\n"
        "Else, search in right subtree\n";
    
    std::string HashTableInsert =
        "Calculate index = value % size\n"
        "Insert value into bucket at index\n";

    std::string HashTableRemove =
        "Calculate index = value % size\n"
        "Traverse bucket at index to find value\n"
        "If value found, remove it from bucket\n";

    std::string HashTableSearch =
        "Calculate index = value % size\n"
        "Traverse bucket at index to find value\n"
        "If value found, return true\n"
        "If value not found, return false\n";




}
