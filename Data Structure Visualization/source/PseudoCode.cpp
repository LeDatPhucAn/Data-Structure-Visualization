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
        "if(!curr)\n"
        "   return false\n"
        "if(curr->key == key)\n"
        "   return true\n"
        "if(curr->key > key)\n"
        "   return search(curr->left)\n"
        "if(curr->key < key)\n"
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
    std::string GraphAddNode =
        "Insert Node at min-index(from 1)";
    std::string GraphRemoveNode =
        "Find node which we want to remove\n"
        "Remove all edges which have a removing node\n"
        "Remove node\n";
    std::string GraphAddEdge =
        "Find nodeFrom = Graph::getNodeById(from)\n"
        "Find nodeTo = Graph::getNodeById(to)\n"
        "if nodeFrom and nodeTo found, draw Edge\n"
        "if nodeFrom or nodeTo not found, return\n";
    std::string GraphRemoveEdge =
        "Find nodeFrom = Graph::getNodeById(from)\n"
        "Find nodeTo = Graph::getNodeById(to)\n"
        "if nodeFrom and nodeTo found, remove Edge\n";
    std::string GraphDijkstra =
        "Traversal all vertices which haven't been visited.\n"
        "Set u as the current vertex with the smallest cost\n"
        "Mark visited[u] is True\n"
        "If d(v) > d(u) + (u,v). Update d(v)\n"
        "Update the shortest path to v (path[v])\n";
}
