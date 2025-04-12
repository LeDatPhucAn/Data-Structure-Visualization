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

void LinkedList::adjustPosWithAnim(AnimationManager& animManager,LLNode* pHead) {
    if (!pHead)return;
    LLNode* prev = pHead;
    LLNode* cur = pHead;
    cur = cur->next;
    int i = 200;
    while (cur) {
        animManager.addAnimation(new CircleMoveXAnim(cur, 0.2f, cur->getCenterX(), prev->getCenterX() + i));
        i += 200;
        cur = cur->next;
    }
}

void LinkedList::adjustPosWithAnim2(AnimationManager& animManager,LLNode* pHead) {
    if (!pHead)return;
    LLNode* prev = pHead;
    LLNode* cur = pHead;
    cur = cur->next;
    int i = 200;
    stack<Animation*> reverse;
    while (cur) {
        reverse.push(new CircleMoveXAnim(cur, 0.2f, cur->getCenterX(), prev->getCenterX() + i));
        i += 200;
        cur = cur->next;
    }
    while (!reverse.empty()) {
        animManager.addAnimation(reverse.top());
        reverse.pop();
    }
}

bool LinkedList::remove(AnimationManager& animManager, int x) {
    if (!head) return false;
    if (head && head->getNumber() == x) {
        LLNode* del = head;

        animManager.addAnimation(new CircleHighLightAnim(del, 0.5f, GREEN, RAYWHITE, GREEN));

        // delay by 1 second
        animManager.addAnimation(new Animation(1.0f));
        
        animManager.addAnimation(new CircleHighLightAnim(del, 0.5f, RAYWHITE, RAYWHITE, RAYWHITE));

        animManager.addAnimation(new Animation(0.1f, [this, &animManager,del]() {
        
            head = head->next;

            if (head) {

                CBEdge::removeEdgeAndAnim(animManager, Edges, del, head);

                //reposition
                animManager.addAnimation(new Animation(0.1f, [&animManager,this,del]() {
                    delete del;
                    head->setCenterX(100);
                    adjustPosWithAnim(animManager,head);
                    }));

            }
            }));

        return true;
    }
    LLNode* cur = head;
    while (cur->next) {

        // animate traversal
        animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f));
        for (auto& edge : Edges) {
            if (edge->from == cur && edge->to == cur->next) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edge, 0.5f, PURPLE));
                break;
            }
        }

        if (cur->next->getNumber() == x) {

            LLNode* temp = cur->next;

            animManager.addAnimation(new CircleHighLightAnim(temp, 0.5f,GREEN,RAYWHITE,GREEN));

            CBEdge::removeEdgeAndAnim(animManager,Edges, cur, temp);

            CBEdge::removeEdgeAndAnim(animManager,Edges, temp, temp->next);


            animManager.addAnimation(new CircleHighLightAnim(temp, 0.5f,RAYWHITE,RAYWHITE,RAYWHITE));

            animManager.addAnimation(new Animation(0.1f, [this,&animManager,cur,temp]() {

                cur->next = temp->next;
                CBEdge::addEdgeAndAnim(animManager, Edges, cur, cur->next);
                delete temp;
                //reposition
                adjustPosWithAnim(animManager,cur);

            }));

                

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


void LinkedList::clearIndicates() {
    LLNode* cur = head;
    while (cur) {
        cur->indicateNode = "";
        cur = cur->next;
    }
}
bool LinkedList::search(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x) {
    
    
    ///// Clear All instances of the variable indicator "cur" which I draw under each node during traversal
    clearIndicates();




    LLNode* cur = head;
    
    // highlight cur = head
    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks,cur]() {
        CodeBlocks[1]->highlight();
        cur->indicateNode = "cur";
        }));
    animManager.addAnimation(new Animation(0.1f, [&CodeBlocks,cur]() {
        CodeBlocks[1]->unhighlight();
        }));
    while (cur) {
        
        ///// PseudoCode:
        //    "Node cur = head;\n"              // CodeBlocks[1]
        //    "while (cur != nullptr)\n"        // CodeBlocks[2]
        //    "   if (cur->data == value)\n"    // CodeBlocks[3]
        //    "        return true;\n"          // CodeBlocks[4]
        //    "   cur = cur->next;\n"           // CodeBlocks[5]
        //    "return false;\n";                // CodeBlocks[6]
        

        // highlight while(cur != nullptr)
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[2]->highlight();
            }));

        // highlight if (cur->data == value)
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[2]->unhighlight();
            CodeBlocks[3]->highlight();
            }));

        if (cur->getNumber() == x) {

            // highlight return true
            animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f, GREEN, RAYWHITE, GREEN, [&CodeBlocks]() {
                CodeBlocks[3]->unhighlight();
                CodeBlocks[4]->highlight();
                }));
            return true;
        }

        //unhighlight line 3
        animManager.addAnimation(new Animation(0.1f, [&CodeBlocks]() {
            CodeBlocks[3]->unhighlight();
            }));

        // Highlight cur = cur->next
        animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f, ORANGE, RAYWHITE, ORANGE, [&CodeBlocks]() {
            CodeBlocks[5]->highlight();
            }));
        

        animManager.addAnimation(new Animation(0.1f, [&CodeBlocks,cur]() {
            CodeBlocks[5]->unhighlight();
            cur->indicateNode = "";
            }));
        for (auto& edge : Edges) {
            if (edge->from == cur && edge->to == cur->next) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edge, 0.5f, PURPLE, [cur]() {
                    if (cur->next)cur->next->indicateNode = "cur";
                    }));
                break;
            }
        }

        cur = cur->next;
    }

    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
        CodeBlocks[6]->highlight();
        }));
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
void LinkedList::insertnode(vector<RectButton*>& CodeBlocks, AnimationManager& animManager,int x, int pos) {
    if (pos < 1) {
        return;
    }
    if (pos == 1 || !head) {
        LLNode* temp = new LLNode(x,100,100);
        temp->onClick = [temp]() {
            cout << temp->getCenterX() << " " << temp->getCenterY() << "\n";
            };
        temp->next = head;
        adjustPosWithAnim2(animManager,temp);
		animManager.addAnimation(new CircleHighLightAnim(temp, 0.5f,GREEN,RAYWHITE,GREEN));
        temp->noDraw = true;
        CBEdge::addEdgeAndAnim(animManager,Edges, temp, head);
        Edges.back()->noDraw = true;
        head = temp;
        return;
    }

    LLNode* cur = head;
    animManager.addAnimation(new Animation(0.1f, [&CodeBlocks]() {
        CodeBlocks[1]->highlight();
        }));
    for (int i = 1; i < pos - 1 && cur && cur->next; i++) {
        animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f,ORANGE,RAYWHITE,ORANGE, [&CodeBlocks]() {
            CodeBlocks[1]->unhighlight();
            CodeBlocks[2]->highlight();
            CodeBlocks[3]->unhighlight();
            }));
        for (auto& edge : Edges) {
            if (edge->from == cur && edge->to == cur->next) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edge, 0.5f, PURPLE));
                break;
            }
        }
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[2]->unhighlight();
            CodeBlocks[3]->highlight();
            }));
        cur = cur->next;
    }

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
    /*animManager.addAnimation(new Animation(0.5f, [this,newnode]() {
		adjustPos(newnode);
        }));*/
    adjustPosWithAnim2(animManager, newnode);

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
