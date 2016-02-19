#pragma once
#include "Structures.h"

class Linkedlist
{
public:
	
	Linkedlist();
	~Linkedlist();
	
	listnode* head;
	listnode* makeNode(SceneObject* d);

	void insertFirst(listnode* newNode);
	void printList(listnode* head);
	void deleteList(listnode* head);

	void insertAfter(listnode* head, listnode* newNode);
	listnode* getNode(listnode* head, int pos);
	listnode* Find(listnode * head, SceneObject* v);
	void deleteAfter(listnode* head);
	
};

