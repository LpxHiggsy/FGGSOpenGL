#include "Linkedlist.h"
#include <iostream>
#include <fstream>
using namespace std;


Linkedlist::Linkedlist()
{
	head = nullptr;
}


Linkedlist::~Linkedlist()
{
}	

listnode* Linkedlist::makeNode(SceneObject* d)
{
	listnode* newNode;
	newNode = new listnode;
	newNode->data = d;
	newNode->next = nullptr;
	return newNode;
}

void Linkedlist::printList(listnode* head) 
{
	listnode* p = head;
		if (p != nullptr)
		{		
			printf("%5d", p->data);
			p = p->next;
			printList(p);
		}
}

void Linkedlist::insertAfter(listnode* head, listnode* newNode)
{
	newNode->next = head->next;
	head->next = newNode;
}

void Linkedlist::insertFirst(listnode* newNode)
{
	newNode->next = head;
	head = newNode;  //new head of the list 
}

void Linkedlist::deleteList(listnode* head) 
{
	listnode* pTemp;	
	if (head != nullptr)
	{
		pTemp = head;
		head = head->next;
		delete pTemp;
		deleteList(head);
	}
}
listnode* Linkedlist::getNode(listnode* head, int pos)
{
	int count = 0;
	if (head != nullptr)
	{
		if (count == pos) 
		{
			return head;
		}
		count++;
		head = head->next;
		getNode(head, pos);
	}
	
	return nullptr; // not a valid position 
}

listnode * Linkedlist::Find(listnode* head, SceneObject* v)
{
	if (head != nullptr)
	{
		if (head->data == v)
		{
			return head;
		}
			
		head = head->next;

		Find(head, v);
	}

	
	return nullptr; // val not in list 
}

void Linkedlist::deleteAfter(listnode* p) 
{
	listnode* pTemp;
	if (p != nullptr && p->next != nullptr) 
	{
		pTemp = p->next;
		p->next = pTemp->next;
		delete pTemp;
	}
}









