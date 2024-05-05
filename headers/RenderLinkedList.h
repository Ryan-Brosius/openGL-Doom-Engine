#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "RenderObject.h"

//Linked list for render objects
class Node
{
	public:
		RenderObject* data;
		Node* next;

		Node(RenderObject* renderObject)
			: data(renderObject), next(NULL) {}

};

class RenderLinkedList
{
	public:
		Node* head;
		Node* tail;

		RenderLinkedList() : head(NULL), tail(NULL) {}
		void insert(RenderObject* renderObject);
		bool empty();
};

#endif