#include "../header/PseudoCode.h"

namespace PseudoCode {
    std::string LLInsertHead =
        "  Node InsertedNode = new Node;\n"
        "  InsertedNode->next = head;\n"
        "  head = InsertedNode";

    std::string LLInsertPos =
        "  Node cur = head;\n"
        "  for (int i = 1; i < pos-1; i++)\n"
        "    cur = cur->next;\n"
        "  Node InsertedNode = new Node(Value);\n"
        "  InsertedNode->next = cur->next;\n"
        "  cur->next = InsertedNode;\n";

    std::string LLRemoveHead =
        "if (head == nullptr)\n"
        "   return false;\n"
        "if (head->data == Value)\n"
        "  Node del = head;\n"
        "  head = head->next;\n"
        "  delete del;\n"
        "  return true;\n";

    std::string LLRemoveBody =
        "Node cur = head;\n"
        "while(cur->next!=nullptr)\n"
        "  if (cur->next->data == Value)\n"
        "    Node del = cur->next;\n"
        "    cur->next = del->next;\n"
        "    delete del;\n"
        "    return true;\n"
        "  cur = cur->next\n"
        "return false;\n";

    std::string LLSearch =
        "Node cur = head;\n"
        "while (cur != nullptr)\n"
        "   if (cur->data == value)\n"
        "        return true;\n"  
        "   cur = cur->next;\n"
        "return false;\n";


    std::string TreapInsert =
        "if(!root)\n"
        "   return node(key, priority)\n"
        "if(root->key == key)\n"
        "   return root\n"
        "else if(root->key > key)\n"
        "   root->left = insert(root->left, key, priority)\n"
        "   if(root->left->priority > root->priority)\n"
        "       root = rotateRight(root)\n"
        "else if(root->key < key)\n"
        "   root->right = insert(root->right, key, priority)\n"
        "   if(root->right->priority > root->priority)\n"
        "       root = rotateLeft(root)\n";

    std::string TreapRemove =
        "if(!root) return nullptr\n"
        "if(root->key > key)\n"
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
        "if(!curr)\n"
        "   return false\n"
        "if(curr->key == key)\n"
        "   return true\n"
        "else if(curr->key > key)\n"
        "   return search(curr->left)\n"
        "else if(curr->key < key)\n"
        "   return search(curr->right)\n";
    
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
