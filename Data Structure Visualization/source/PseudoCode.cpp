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
        "if(root->key > key) root->left = remove(root->left, key)\n"
        "else if(root->key < key) root->right = remove(root->right, key)\n"
        "else if(root->key == key)\n"
        "   if(!root->left && !root->right) return nullptr\n"
        "   else if(!root->left) return root->right\n"
        "   else if(!root->right) return root->left\n"
        "   if(root->left->priority > root->right->priority)\n"
        "       root = rotateRight(root)\n"
        "       root->right = remove(root->right, key)\n"
        "   else if(root->right->priority > root->left->priority)\n"
        "       root = rotateLeft(root)\n"
        "       root->left = remove(root->left, key)\n";
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
