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
    
}

void HashTableUI::displayScene() {
    drawHashTable();
}

void HashTableUI::updateScene() {
    
}
