#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <string>

#include "ioHandiling.hpp"


class Computer
{
  public:
    Computer();
    
    //Pr - Takes in a LogFile object so a login can be written to labTrac_log.txt.
    //Po - Void function, Performs the login logic
    void login(ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers);

    //Pr - Takes in everything that a computer object needs to be succssful.
    //Po - Overloaded form used for the recovery feature.
    void login(int userID_, std::string studentName_, int timeUsed_, ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers);

    //Pr - Takes in the logfile object for logging.
    //Po - Void function, performs the logout logic
    void logout(ioHandiling::LogFile& file);

    //The following five access their appropriate attributes.
    int getID() const;
    std::string getStudentName() const;
    int getSeatLoc() const;
    int getLabLoc() const;

    //The following five take in their respective objects that they modify within the computer object.
    void assignID(int userID_);
    void assignStudentName(std::string& studentName_);
    void assignTime(int timeUsed_);
    void assignSeatLocation(int seatLoc_);
    void assignLabLocation(int labLoc_);

  private:
    int userID;
    int labLoc;
    int seatLoc;
    std::string studentName; //Max 35 chars.
    int timeUsed;

    //Pr - Nothing
    //Po - Returns a pseudorandomized integer from 1 to 99999 
    int makeID();

    //Pr - Takes in a character for the flag, and the logfile stream.
    //Po - Void function, writes to the logfile's log with information specified in the specification.
    void writeToLog(char flag, ioHandiling::LogFile& log);

    //Pr - 
    //Po - Returns a bool that checks if the seat is already occupied.
    bool isOccupied();
};

#endif