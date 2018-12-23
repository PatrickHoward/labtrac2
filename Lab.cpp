#include <iostream>
#include <string>
#include <map>

#include "ioHandiling.hpp"
#include "Lab.hpp"


Lab::Lab()
{
	labName = "uniname";
	labSize = 0;
    labOccupancy = 0;
    labLoc = 0;
}

Lab::Lab(int labSize_, std::string labName_)
    : labSize(labSize_),
    labName(labName_)
{
    labOccupancy = 0;
    //fillWithCompuNodes();
}

void Lab::simulateLogin(ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers)
{
    if(isFull())
    {
        return;
    }

    ++labOccupancy;

    int seatSelection = ioHandiling::promptInt("Please select a seat assignment.", 1, labSize);

    Computer tmpComp;
    tmpComp.login(log);

    Computer* addToMap;
    addToMap = compuLab.appendNode(tmpComp, seatSelection, labLoc);
    activeComputers.insert(std::pair<int, Computer*>(tmpComp.getID(), addToMap));

    // CompuNode* selectedComp;
    // selectedComp = compuLab.goToNComp(seatSelection);
    // selectedComp->data.login(log, activeComputers);
    
    return;
}

void Lab::simulateLogoff(int userID, ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers)
{
    auto selectedComp = activeComputers.find(userID)->second;

    if(selectedComp->getID() == userID)
    {
        selectedComp->logout(log);
        compuLab.removeNode(selectedComp);
        activeComputers.erase(userID);
    }
}

void Lab::assignToFirstAvailable(std::string line, ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers)
{
    if(isFull())
    {
        return;
    }

    ++labOccupancy;

    int userID = stoi(line.substr(27, 5));
    int timeUsed = stoi(line.substr(35, 2));
    int seatLoc = compuLab.nearestSeatAvailable(labSize);

    std::string studentName = line.substr(40, line.length());

    Computer tempComp;
    tempComp.login(userID, studentName, timeUsed, log);

    Computer* addToMap;
    addToMap = compuLab.appendNode(tempComp, seatLoc, labLoc);
    activeComputers.insert(std::pair<int,Computer*>(tempComp.getID(), addToMap));

    // CompuNode* selectedComp;
    // selectedComp = compuLab.findComputerByID(-1);
    // selectedComp->data.login(userId, studentName, timeUsed, log, activeComputers);
}

void Lab::displayLab()
{
    int userID = -1;
    std::string studentName = "EMPTY";

    for(int i = 0; i < labSize; ++i)
    {
        CompuNode* currentLoc;
        currentLoc = compuLab.findComputerBySeat(i);

        if(currentLoc)
        {
            userID = currentLoc->data.getID();
            studentName = currentLoc->data.getStudentName();
        }
        else
        {
            userID = -1;
            studentName = "EMPTY";
        }

        std::cout << "| ";

        std::cout
            << i + 1 << ": "
            << ioHandiling::formatUserID(userID)
            << " - "
            << studentName
            << ", ";
        
        if(i == 0)
        {

        }
        else if(i % 5 == 0)
        {
            std::cout << "\n| ";
        }

    }

    //compuLab.displayEach(compuLab.head, 1);
    std::cout << "\n";
}

void Lab::assignLabSize(int labSize_)
{
    labSize = labSize_;
}

void Lab::assignLabName(std::string labName_)
{
    labName = labName_;
}

void Lab::assignLabLocation(int labLoc_)
{
    labLoc = labLoc_;
}

bool Lab::isFull()
{
    if (labOccupancy >= labSize)
    {
        std::cout << "| !! - Lab occupancy is full at this time, please try again later. - !!\n|\n";
        return true;
    }

    return false;
}

