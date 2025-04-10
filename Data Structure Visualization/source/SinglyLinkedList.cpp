#include "../header/SinglyLinkedList.h"
#include "../header/Edge.h"
#include "../header/Animation.h"
#include "../header/tinyfiledialogs.h"
#include <fstream>
vector<CBEdge*> LinkedList::Edges;

void LinkedList::loadFromFile() {
    const char* filter[] = { "*.txt" };
    const char* filePath = tinyfd_openFileDialog(
        "Select a text file", // Title
        "", // Default path (empty = open from last used folder)
        1, // Number of filter patterns
        filter, // Filter patterns
        "Text file (*.txt)", // Filter description
        0 // Single file seclection mode
    );

    if (filePath) {
        cout << "Trying to open the file: " << filePath << "\n";
        ifstream fin(filePath);
        if (fin.is_open()) {
            clear();
            string line;
            int pos = 1;
            int key = 0;
            while (fin>>key) {
                randominsert(key,pos);
                pos++;
            }
        }
        else cerr << "Error: Can not open file\n";
        fin.close();
    }
}
void LinkedList::adjustPos(LLNode* pHead) {
    LLNode* prev = nullptr;
    while (pHead) {
        if (prev) {
            pHead->setCenterX(prev->getCenterX() + 200);
        }

        prev = pHead;
        pHead = pHead->next;
    }
}

bool LinkedList::remove(AnimationManager& animManager, int x) {
    if (!head) return false;
    if (head && head->getNumber() == x) {
        LLNode* del = head;
        head = head->next;

        if(head){
            CBEdge::removeEdge(Edges, del, head);
            // adjusting position
            head->setCenterX(100);
            adjustPos(head);
        }
        delete del;
        del = nullptr;
        return true;
    }
    LLNode* cur = head;
    while (cur->next) {
        animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f));
        for (auto& edge : Edges) {
            if (edge->from == cur) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edge, 0.5f, PURPLE));
                break;
            }
        }
        if (cur->next->getNumber() == x) {

            LLNode* temp = cur->next;

            animManager.addAnimation(new CircleHighLightAnim(temp, 0.5f,GREEN,RAYWHITE,GREEN));

            CBEdge::removeEdgeAndAnim(animManager,Edges, cur, temp);


            CBEdge::removeEdgeAndAnim(animManager,Edges, temp, temp->next);

            animManager.addAnimation(new Animation(0.5f, [this,&animManager,&cur, &temp]() {
                cur->next = temp->next;
                CBEdge::addEdgeAndAnim(animManager, Edges, cur, cur->next);
                //reposition in accordance to animation
                animManager.addAnimation(new Animation(0.5f, [this, cur, &temp]() {
                    adjustPos(cur);
                    delete temp;
                    temp = nullptr;
                    }));
                }));

            //cur->next = temp->next;

            
            ////reposition in accordance to animation
            //animManager.addAnimation(new Animation(0.5f, [this, cur, &temp]() {
            //    adjustPos(cur);
            //    delete temp;
            //    temp = nullptr;
            //    }));
            //
            
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void LinkedList::printlist() {
    LLNode* cur = head;
    while (cur) {
        cout << cur->getNumber() << " ";
        cur = cur->next;
    }
    cout << endl;
}
bool LinkedList::search(int x) {
    LLNode* cur = head;
    while (cur) {
        if (cur->getNumber() == x) {
            return true;
        }
        cur = cur->next;

    }
    return false;
}
void LinkedList::deletelist() {
    while (head) {
        LLNode* del = head;
        head = head->next;
        delete del;
    }
    head = nullptr;
}
void LinkedList::deleteEdges() {
    for (auto edge : Edges) {
        delete edge;
    }
    Edges.clear();
}
void LinkedList::clear() {
    deletelist();
    deleteEdges();
}
void LinkedList::insertnode(AnimationManager& animManager,int x, int pos) {
    if (pos < 1) {
        return;
    }
    if (pos == 1 || !head) {
        LLNode* temp = new LLNode(x,100,100);
        temp->onClick = [temp]() {
            cout << temp->getCenterX() << " " << temp->getCenterY() << "\n";
            };
        temp->next = head;
        adjustPos(temp);
		animManager.addAnimation(new CircleHighLightAnim(temp, 0.5f,GREEN,RAYWHITE,GREEN));
        CBEdge::addEdgeAndAnim(animManager,Edges, temp, head);
        head = temp;
        return;
    }
    LLNode* cur = head;

    //highlight traversal to pos
    for (int i = 1; i < pos - 1 && cur && cur->next; i++) {
        animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f));
        for (auto& edge : Edges) {
            if (edge->from == cur) {
                cout << cur->getNumber() << " ";
                animManager.addAnimation(new CBEdgeHighLightAnim(edge, 0.5f, PURPLE));
                break;
            }
        }
        cur = cur->next;
    }
    cout << "\n";
    animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f));

	// highlight the last node
    if (!cur->next) {
        LLNode* newnode = new LLNode(x, cur->getCenterX() + 200, cur->getCenterY());
        cur->next = newnode;
        newnode->noDraw = true;


		CBEdge::addEdgeAndAnim(animManager,Edges, cur, newnode);
		Edges.back()->noDraw = true;
        
        Animation* InsertNode = new CircleHighLightAnim(newnode, 0.5f, GREEN, RAYWHITE, GREEN);
        InsertNode->Function = [newnode]() {
            newnode->noDraw = false; // when we traverse to the desired position, we draw the inserted node outside the linked list
            newnode->animation->reset();
         };

        // highlight inserted node
        animManager.addAnimation(InsertNode);
        return;
    }



	//// highlight the current node

    /// the node to be inserted
    LLNode* newnode = new LLNode(x,cur->getCenterX() + 200, 400);


	
    Animation* InsertNode = new CircleHighLightAnim(newnode, 0.5f, GREEN, RAYWHITE, GREEN);
	InsertNode->Function = [newnode]() {
        newnode->animation->reset();
		newnode->noDraw=false; // when we traverse to the desired position, we draw the inserted node outside the linked list
		};

    // highlight inserted node
    animManager.addAnimation(InsertNode);
    
	// initially the inserted node is not drawn
    newnode->noDraw = true;
    newnode->onClick = [newnode]() {
        cout << newnode->getCenterX() << " " << newnode->getCenterY() << "\n";
    };

    LLNode* next = cur->next;

    //connect first edge
    cur->next = newnode;

    //first edge
    CBEdge::addEdgeAndAnim(animManager, Edges, cur, newnode);
    Edges.back()->noDraw = true;

    // connect next edge
    newnode->next = next;

    //reposition in accordance to animation
    animManager.addAnimation(new Animation(0.5f, [this,newnode]() {
		adjustPos(newnode);
        }));
    

    // Add next edge
    CBEdge::addEdgeAndAnim(animManager,Edges, newnode, next);
	Edges.back()->noDraw = true;


	// remove the edge between cur and next with animation done
	CBEdge::removeEdgeAndAnim(animManager, Edges, cur, next);  

    // add the node in
    animManager.addAnimation(new CircleMoveAnim(newnode, 2, newnode->getCenterX(), 400, newnode->getCenterX(),cur->getCenterY()));
    

}

void LinkedList::randominsert(int x, int pos) {
    if (pos < 1) {
        return;
    }
    if (pos == 1 || !head) {
        LLNode* temp = new LLNode(x,100,100);
        temp->onClick = [temp]() {
            cout << temp->getCenterX() << " " << temp->getCenterY() << "\n";
            };
        temp->next = head;
        adjustPos(temp);
        CBEdge::addEdge(Edges, temp, head);
        head = temp;
        return;
    }
    LLNode* cur = head;
    for (int i = 1; i < pos - 1 && cur && cur->next; i++) {
        cur = cur->next;
    }

    LLNode* newnode = new LLNode(x,cur->getCenterX() + 200, cur->getCenterY());
    newnode->onClick = [newnode]() {
        cout << newnode->getCenterX() << " " << newnode->getCenterY() << "\n";
        };
    newnode->next = cur->next;
    CBEdge::addEdge(Edges, newnode, cur->next);
    CBEdge::removeEdge(Edges, cur, cur->next);
    cur->next = newnode;
    adjustPos(newnode);
    CBEdge::addEdge(Edges, cur, newnode);
}
