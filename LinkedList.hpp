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

        head = NULL;
        tail = NULL;
    }

    void appendNode(Computer addThis, int seatLoc, int labLoc)
    {
        ++size;

        CompuNode* tempNode = new CompuNode;
        tempNode->data = addThis;
        tempNode->next = NULL;

        if(head == NULL)
        {
            head = tempNode;
            tail = tempNode; 

            tempNode = NULL;
        }
        else
        {
            tail->next = tempNode;
            tail = tempNode;
        }

        tail->data.assignSeatLocation(seatLoc);
        tail->data.assignLabLocation(labLoc);

    }

    void removeNode(CompuNode* deleteThis)
    {
        CompuNode* tempNode = head;
        while(tempNode->next != deleteThis)
        {
            tempNode = tempNode->next;

            if(tempNode == tail->next)
            {
                return;
            }

        }

        tempNode->next = deleteThis->next;
        delete deleteThis;
    }

    CompuNode* goToNComp(int n)
    {
        CompuNode* tmp = head;

        for (int i = 0; i < n-1; ++i)
        {
            tmp = tmp->next;
        }

        return tmp;
    }

    CompuNode* findComputerByID(int userID)
    {
        CompuNode* tmp = head;
        while(tmp->data.getID() != userID && tmp->next != NULL)
        {
            tmp = tmp->next;

        }

        return tmp;
    }

    void displayEach(CompuNode* current, int index)
    {
        if(current == nullptr)
        {
            std::cout << "| !! - No active computers in this lab - !!\n";
            return;
        }

        if(current->next == nullptr)
        {
            return;
        }

        std::cout
            << ioHandiling::formatUserID(current->data.getID())
            << " - "
            << current->data.getStudentName()
            << ", ";
        
        if(index == 1)
        {

        }
        else if(index % 5 == 0)
        {
            std::cout << "\n";
        }

        displayEach(current->next, index + 1);

    }

    void reIndex(CompuNode* current, int index)
    {
        if(current == nullptr)
        {
            std::cout << "| !! - No active computers in this lab - !!\n";
        }

        if(current->next == nullptr)
        {
            return;
        }

        current->data.assignSeatLocation(index);
        reIndex(current->next, index + 1);
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