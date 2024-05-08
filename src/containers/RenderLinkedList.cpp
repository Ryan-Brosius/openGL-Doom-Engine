#include "RenderLinkedList.h"

void RenderLinkedList::insert(RenderObject* renderObject)
{
	Node* newNode = new Node(renderObject);

	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = newNode;
}

bool RenderLinkedList::empty()
{
	return this->head == NULL;
}