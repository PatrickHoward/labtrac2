#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>

#include "ioHandiling.hpp"
#include "Computer.hpp"

Computer::Computer()
{
  userID = -1;
  studentName = "empty";
  timeUsed = 0;
  labLoc = 0;
}

void Computer::login(ioHandiling::LogFile& file, std::map<int, Computer*>& activeComputers)
{
    if(isOccupied())
    {
        return;
    }

    //Call mkID and assign userID.
    userID = makeID();
    std::cout << "| Assigned user to: " << ioHandiling::formatUserID(userID) << "\n";

    studentName = ioHandiling::promptString("Please input a name.", 0, 35);

    do
    {
        timeUsed = ioHandiling::promptInt("Please input time used in 15 minute increments.", 15, 60);
    
    }while(timeUsed % 15 != 0);

    std::cout << "| Assigned " << studentName << " to user# " << userID << ".\n"; 

    activeComputers.insert(std::pair<int, Computer*>(userID, this));
    writeToLog('I', file);

}

void Computer::login(int userID_, std::string studentName_, int timeUsed_, ioHandiling::LogFile& file, std::map<int, Computer*>& activeComputers)
{
    if(isOccupied())
    {
        return;
    }

    userID = userID_;
    studentName = studentName_;
    timeUsed = timeUsed_;

    std::cout << "| Assigned " << studentName << " into seat " << seatLoc << " \n";

    activeComputers.insert(std::pair<int, Computer*>(userID, this));
    writeToLog('I', file);
    
}

void Computer::logout(ioHandiling::LogFile& file)
{   
    std::cout << "| " << studentName << " has been signed out. \n";

    writeToLog('O', file);

    userID = -1;
    studentName = "empty";
    timeUsed = 0;
}

int Computer::getID() const
{    
    return userID;
}

std::string Computer::getStudentName() const
{
    return studentName;
}

int Computer::getSeatLoc() const
{
    return seatLoc;
}

int Computer::getLabLoc() const
{
    return labLoc;
}

void Computer::assignID(const int userID_)
{
    userID = userID_;
}
void Computer::assignStudentName(std::string& studentName_)
{
    studentName = studentName_;
}

void Computer::assignTime(int timeUsed_)
{
    timeUsed = timeUsed_;
}

void Computer::assignSeatLocation(int seatLoc_)
{
    seatLoc = seatLoc_;
}

void Computer::assignLabLocation(int labLoc_)
{
    labLoc = labLoc_;
}

int Computer::makeID()
{
    return rand()%99999;
}

void Computer::writeToLog(char flag, ioHandiling::LogFile& log)
{
    std::ostringstream logLine;
    logLine << ioHandiling::getTime() << " - " << flag << " - " << userID << " - " <<  timeUsed << " - " << studentName << "\n";

    std::string output = logLine.str();

    log.writeLine(output);
}

bool Computer::isOccupied()
{
    if(userID != -1)
    {
        std::cout << "| !! - Seat already occupied, please select another. - !!\n";
        return true;
    }

    return false;
}
