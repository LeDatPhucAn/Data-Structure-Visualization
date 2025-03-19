#include "../header/PseudoCode.h"

namespace PseudoCode {
    std::string LLInsert =
        "If pos < 1, return\n"
        "If pos == 1 or list is empty:\n"
        "  Create new node with x\n"
        "  Set new node's next to head\n"
        "  Adjust positions\n"
        "  Add edge new node to head\n"
        "  Set new node as head\n"
        "Else:\n"
        "  Traverse to pos-1\n"
        "  If node found:\n"
        "    Create new node with x\n"
        "    Set new node's next to current node's next\n"
        "    Add edge new node to current node's next\n"
        "    Remove edge current node to current node's next\n"
        "    Set current node's next to new node\n"
        "    Adjust positions\n"
        "    Add edge current node to new node\n";

    std::string HashTableInsert =
        "Calculate index = value % size\n"
        "Insert value into bucket at index\n";

    std::string TreapInsert =
        "Insert node with key and priority\n"
        "Reposition nodes\n";
}
