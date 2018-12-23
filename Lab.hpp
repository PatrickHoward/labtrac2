#ifndef LAB_HPP
#define LAB_HPP

#include <string>
#include <map>

#include "ioHandiling.hpp"
#include "LinkedList.hpp"


class Lab
{
public:
    Lab();

    //Pr - Takes in an int labSize_ and a string labName_
    //Po - Void function, creates a new Lab object with labSize,
    //     labName, and a Linked List of computer objects.
    Lab(int labSize_, std::string labName_);
 
    //Pr - Needs the log for writing to the log, and a map object for keeping track for the interface.
    //Po - Void funciton, assigns values to a computer object within the linked list.
    void simulateLogin(ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers);

    //Pr - Asks for the userID
    //Po - Void function, resets computer object within the linked list.
    bool simulateLogoff(int userID, ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers);

    //Pr - Takes in a recovered string and a logfile object.
    //Po - Void function, parses the linked list 
    void assignToFirstAvailable(std::string line, ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers);

    //Pr - Nothing
    //Po - Void function, accesses and loops through the linked list.
    void displayLab();

    //Pr - Searches its local map to find the computer object.
    //Po - 
    void searchLab(int userID, int labLoc);

    //Pr - A integer labSize_
    //Po - Void function, modifier for the labSize attribute.
    void assignLabSize(int labSize_);

    //Pr - A string labName_
    //Po - Void fuction, modifier for the labName attribute.
    void assignLabName(std::string labName_);

    //Pr - An interger labLoc
    //Po - Void function, modifer for the labLoc attribute.
    void assignLabLocation(int labLoc_);

    //Pr - Lab needs to have been constructued using the default constructor.
    //Po - Void function, adds labSize nodes to compuLab and initializes labOccupancy to 0.
    void fillWithCompuNodes();

private:

    //Pr - Nothing
    //Po - Returns a boolean based on if the current lab occupancy is full.
    bool isFull();

    //Pr - Takes in an int as UserID
    //Po - Spits out a bool determining if 
    bool find(int userID);
    
    int labOccupancy;
    int labSize;
    int labLoc;
    std::string labName;


    LinkedList compuLab;
};

#endif
