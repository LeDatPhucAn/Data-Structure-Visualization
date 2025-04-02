#include "../header/HashTable.h"
#include "../header/Animation.h"
using namespace std;
vector<Edge*> HashTable::Edges;

void HashTable::insertHashTable(int value) {
    int index = value % size;
    Vector2 pos = { 0, 0 };
    Node* newNode = new Node(value, pos, 30);
    newNode->animation = new NodeInitializeAnimation(newNode, 0.5f);
    data[index].push_back(newNode);

    if (data[index].size() > 1) {
        Edge::addEdge(Edges, data[index][data[index].size() - 2], newNode);
    }
    adjustPos(index);
}

bool HashTable::findHashTable(int value) {
    int index = value % size;
    for (auto node : data[index]) {
        if (node->data == value) {
            return true;
        }
    }
    return false;
}

void HashTable::deleteHashTable(int value) {
    int index = value % size;
    for (auto it = data[index].begin(); it != data[index].end(); ++it) {
        if ((*it)->data == value) {
            Node* delNode = *it;
            if (data[index].size() > 1) {
                if (it == data[index].begin()) {
                    Edge::removeEdge(Edges, delNode, *(it + 1));
                }
                else if (it == data[index].end() - 1) {
                    Edge::removeEdge(Edges, *(it - 1), delNode);
                }
                else {
                    Edge::removeEdge(Edges, *(it - 1), delNode);
                    Edge::removeEdge(Edges, delNode, *(it + 1));
                    Edge::addEdge(Edges, *(it - 1), *(it + 1));
                }
            }
            data[index].erase(it);
            delete delNode;
            adjustPos(index);
            return;
        }
    }
}

void HashTable::display() {
    for (int i = 0; i < size; ++i) {
        std::cout << "Bucket " << i << ": ";
        for (auto node : data[i]) {
            std::cout << node->data << " ";
        }
        std::cout << std::endl;
    }
}

void HashTable::adjustPos(int bucketIndex) {
    float bucketX = 100 + bucketIndex * (100 + 20);
    float bucketY = 200 + 80;
    for (int j = 0; j < data[bucketIndex].size(); ++j) {
        Vector2 newPos = { bucketX + 50, bucketY + (j + 1) * (60 + 10) };
        data[bucketIndex][j]->position = newPos;
    }
}

void HashTable::deleteEdges() {
    for (auto edge : Edges) {
        delete edge;
    }
    Edges.clear();
}
