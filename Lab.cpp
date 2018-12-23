#include <iostream>
#include <string>
#include <map>

#include "ioHandiling.hpp"
#include "Lab.hpp"


Lab::Lab()
{
	labName = "uniname";
	labSize = 0;
}

Lab::Lab(int labSize_, std::string labName_)
    : labSize(labSize_),
    labName(labName_)
{
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
    tmpComp.login(log, activeComputers);
    compuLab.appendNode(tmpComp, labOccupancy, labLoc);

    // CompuNode* selectedComp;
    // selectedComp = compuLab.goToNComp(seatSelection);
    // selectedComp->data.login(log, activeComputers);
    
    return;
}

bool Lab::simulateLogoff(int userID, ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers)
{
    CompuNode* selectedComp;
    selectedComp = compuLab.findComputerByID(userID);

    if(selectedComp->data.getID() == userID)
    {
        activeComputers.erase(selectedComp->data.getID());
        selectedComp->data.logout(log);
        compuLab.removeNode(selectedComp);

        --labOccupancy;
    }


    // Old code, based on the assumption that all of the computer objects would be created beforehand.
    // if(selectedComp->data.getID() != -1)
    // {
    //     activeComputers.erase(selectedComp->data.getID());
    //     selectedComp->data.logout(log);

    //     --labOccupancy;
        
    //     return true;
    // }
    
    return false;
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
    



    std::string studentName = line.substr(40, line.length() - 40);

    Computer tempComp;
    tempComp.login(userID, studentName, timeUsed, log, activeComputers);
    compuLab.appendNode(tempComp, 1, labLoc);
    
    // CompuNode* selectedComp;
    // selectedComp = compuLab.findComputerByID(-1);
    // selectedComp->data.login(userId, studentName, timeUsed, log, activeComputers);
}

void Lab::searchLab(int userID, int labLoc)
{
    CompuNode* selectedComp;

    selectedComp = compuLab.findComputerByID(userID);
    if(selectedComp->data.getID() == userID)
    {
        std::cout << "| Found " << selectedComp->data.getStudentName() << " in Lab " << labLoc 
                  << " at seat " << selectedComp->data.getSeatLoc() << "\n"; 
        return;  
    }
}

void Lab::displayLab()
{
    compuLab.displayEach(compuLab.head, 1);
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

void Lab::fillWithCompuNodes()
{
    Computer newComputer;

    labOccupancy = 0;
    for(int i = 0; i < labSize; i++)
    {
        compuLab.appendNode(newComputer, i + 1 , labLoc);
    }
}

bool Lab::isFull()
{
    if (labOccupancy >= labSize)
    {
        std::cout << "| !! - Lab occupancy is full at this time, please try again later. - !!\n";
        return true;
    }

    return false;
}

