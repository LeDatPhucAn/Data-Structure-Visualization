#include "UI.h"
#include "HashTableUI.h"
#include "SceneHandler.h"

HashTableUI::HashTableUI() : HashTable(5) {  // Initial size: 5
    init();
}

HashTableUI::HashTableUI(SceneHandler* handler) : HashTable(5), scenehandler(handler) {
    init();
}

void HashTableUI::init() {
    insertHashTable(10); // example
    insertHashTable(15);
    insertHashTable(7);
    insertHashTable(12);
}

void HashTableUI::drawHashTable() {
    for (int i = 0; i < size; ++i) {
        float bucketX = startX + i * (Width + spacing);
        float bucketY = startY;

        Rectangle bucketRec = { bucketX, bucketY, Width, Height };
        DrawRectangleLinesEx(bucketRec, 2.0f, BLACK);
        drawtext2("Bucket " + to_string(i), bucketX + Width / 2, bucketY - 20, DARKGRAY);

        for (int j = 0; j < data[i].size(); ++j) {
            Vector2 nodePos = { bucketX + Width / 2, bucketY + Height + (j + 1) * (nodeRadius * 2 + 10) };
            Node* node = new Node(data[i][j], nodePos, nodeRadius);
            drawNode(node);

            if (j == 0) {
                DrawLine(bucketX + Width / 2, bucketY + Height, nodePos.x, nodePos.y - nodeRadius, BLACK);
            }
            else {
                Vector2 prevNodePos = { bucketX + Width / 2, bucketY + Height + j * (nodeRadius * 2 + 10) };
                DrawLine(prevNodePos.x, prevNodePos.y + nodeRadius, nodePos.x, nodePos.y - nodeRadius, BLACK);
            }

            delete node;
        }
    }
}

void HashTableUI::displayScene() {
    drawHashTable();
}

void HashTableUI::updateScene() {
    
}
