#pragma once
#include "UI.h"
typedef enum Scenes { 
	MENU = 0,
	LINKEDLIST,
	HASHTABLE,
	TREAP,
	GRAPH
} Scene;

class SceneManager : public UI{
public:
	Scene CurrentScene;
	virtual void updateScene() = 0;
	virtual void displayScene() = 0;
    virtual ~SceneManager() = default;
};
