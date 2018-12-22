#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Computer.hpp"
#include "ioHandiling.hpp"
#include <iostream>

struct CompuNode
{
    Computer data;
    CompuNode* next;
};

class LinkedList
{
public:
    LinkedList()
    {
        size = 0;

        head = nullptr;
        tail = nullptr;
    }

    Computer* appendNode(Computer addThis, int seatLoc, int labLoc)
    {
        ++size;

        CompuNode* tempNode = new CompuNode;
        tempNode->data = addThis;
        tempNode->next = nullptr;

        if(head == nullptr)
        {
            head = tempNode;
        }

        tail = tempNode;

        tail->data.assignSeatLocation(seatLoc);
        tail->data.assignLabLocation(labLoc);

        return &(tail->data);

    }

    void removeNode(Computer* deleteThis)
    {
        if(head == nullptr)
        {
            return;
        }

        CompuNode* tempNode = findByPointer(deleteThis);

        CompuNode* deleteNode = tempNode->next;
        
        if(tempNode == tail)
        {
            return;
        }

        tempNode->next = deleteNode->next;
        

        delete deleteNode;

        --size;
    }

    CompuNode* findComputerBySeat(int seatLoc)
    {
        CompuNode* tmp = head;

        if(tmp == nullptr)
        {
            return nullptr;
        }

        while(tmp->data.getSeatLoc() != seatLoc)
        {
            tmp = tmp->next;
        }

        return tmp;
    }

    int nearestSeatAvailable(int largestSeatLoc_)
    {
        CompuNode* temp = head;
        int largestSeatLoc = largestSeatLoc_ ;

        while(temp != tail)
        {
            if(temp->data.getSeatLoc() < largestSeatLoc)
            {
                largestSeatLoc = temp->data.getSeatLoc() - 1;
            }
            
            temp = temp->next;
        }

        return largestSeatLoc;

    }

    CompuNode* findByPointer(Computer* compPointer)
    {
        if(head == nullptr)
        {
            return nullptr;
        }

        CompuNode* finder = head;
        while(finder->data.getID() != compPointer->getID())
        {
            if(finder == tail && compPointer->getID() != tail->data.getID())
            {
                return nullptr;
            }

            finder = finder->next;
        }

        return finder;
    }

	~LinkedList()
	{
        CompuNode* temp = head;

        while(temp != nullptr)
        {
            if(temp == nullptr)
            {
                break;
            }
            CompuNode* toDelete = temp;
            temp = temp->next;

            delete toDelete;
        }
	}

    int size;
    CompuNode* head;
    CompuNode* tail;

};

#endif