#pragma once
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <memory>
#include <iostream>

template <typename T>
struct DoubleNode {
	T data;
	std::shared_ptr<DoubleNode<T>> next;
	std::shared_ptr<DoubleNode<T>> prev;

	DoubleNode(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoubleLinkedList {

	public:
		int length;
		std::shared_ptr<DoubleNode<T>> head;
		std::shared_ptr<DoubleNode<T>> tail;

		DoubleLinkedList() : head(nullptr), tail(nullptr), length(0) {}

		void add(T value);
		void remove(T value);
		void display();

};

template<typename T>
void DoubleLinkedList<T>::add(T value)
{
	std::shared_ptr<DoubleNode<T>> newNode = std::make_shared<DoubleNode<T>>(value);

	if (length == 0)
	{
		head = newNode;
		tail = newNode;

		newNode->next = newNode;
		newNode->prev = newNode;
	}
	else
	{
		std::shared_ptr<DoubleNode<T>> temp = tail;

		tail->next = newNode;
		tail = newNode;
		tail->next = head;
		tail->prev = temp;

		head->prev = tail;
	}

	length++;
}

template<typename T>
void DoubleLinkedList<T>::remove(T value)
{
	if (!head)
	{
		return;
	}

	if (head->data == value)
	{
		head = head->next;
		tail->next = head;

		head->prev = tail;

		length--;
		return;
	}

	int tempCount = 2;
	std::shared_ptr<DoubleNode<T>> temp = head->next;
	while (temp && tempCount <= length)
	{

		std::cout << tempCount << std::endl;

		if (temp->data == value)
		{
			std::shared_ptr<DoubleNode<T>> next = temp->next;
			std::shared_ptr<DoubleNode<T>> prev = temp->prev;

			prev->next = next;
			next->prev = prev;

			if (tempCount == length)
			{
				tail = prev;
			}

			length--;
			return;
		}

		temp = temp->next;
		tempCount++;
	}
}

template<typename T>
void DoubleLinkedList<T>::display()
{
	int tempCount = 0;

	std::shared_ptr<DoubleNode<T>> temp = head;
	while (tempCount < length)
	{
		std::cout << temp->data << " -> ";
		std::cout << "(prev) " << temp->prev->data << " (next) " << temp->next->data << std::endl;
		temp = temp->next;
		tempCount++;
	}
	std::cout << "nullptr" << std::endl;
}

#endif
