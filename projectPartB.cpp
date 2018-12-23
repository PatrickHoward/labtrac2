/*
  PROJECT PART B - Patrick M. Howard (pmh41) - LabTrac
  Copyright 2018, all rights reserved. 
  pmh41@zips.uakron.edu
  ver 0.34 9.28.2018
  Purpose: This program manages computer labs for several different universities. It can sign on, sign off users and keep track of 
           where they are in the system. 
*/

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

#include "ioHandiling.hpp"

#include "Lab.hpp"

//Global Constants
//Number of computer Labs
const int NUMLABS = 8;
//Number of computers in each lab;
const int LABSIZES[NUMLABS] = {19, 15, 24, 33, 4, 17, 55, 37};

//Universities currently under constract.
const std::string UNIVERSITYNAMES[NUMLABS] = {
                                              "The University of Michigan", 
                                              "The University of Pittsburgh", 
                                              "Stanford University",
                                              "Arizona State University", 
                                              "North Texas State University", 
                                              "The University of Alabama, Huntsville", 
                                              "Princeton University", 
                                              "Duquesne University"
                                            };

std::string logfile = "labTrac_log.txt";

struct Menu
{

    //Pr - Nothing
    //Po - Prints the header
    void printHeader(); 
    //Pr - Nothing
    //Po - Prints the available labs to select from.
    void printLabs();

    //Pr - Nothing
    //Po - Prints the menu to select from.
    void printMenu();

    //Pr - A logfile object is needed
    //Po - Writes a timestamp to the log, this function is used only for testing purposes
    void startupTimestamp(ioHandiling::LogFile& log); 

    //Pr - Nothing
    //Po - Prints the top three functions, respectively.
    void printStartup();

    //Pr - Nothing
    //Po - Uses ioHandiling::promptInt to get an int within a valid range.
    int promptUserId();

    //Pr - Nothing
    //Po - Uses ioHandiling::promptInt to get an int within a valid range.
    int promptUniversitySelection();

    //Pr - Takes the array of labs, log file, and a map
    //Po - Goes through the UI jargon to add a user to the active system.
    void simulateLogin(Lab labArray[], ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers);

    //Pr - Same thing as login
    //Po - Does the reverse of login.
    void simulateLogoff(Lab labArray[], ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers);

    //Pr - Takes in the map object.
    //Po - Searches the map to locate a user.
    /* EXCEPTION HANDELED -> */void searchLab(std::map<int, Computer*>& activeComputers); /* <- EXCEPTION HANDELED */

    //Pr - Takes in an array of lab objects 
    //Po - Displays 
    void displayLab(Lab labArray[]);

    //Pr - Takes in the LabArray and the logFile object.
    //Po - Recovers a user based on their ID number.
    void recoverUser(Lab labArray[], ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers);

    //Pr - Takes in a logFile object.
    //Po - Returns a bool causing the while loop to break, exiting the program. 
    bool quitLabTrac(ioHandiling::LogFile& file);
};

enum class MenuOption
{
    reprint = 0,
    login = 1,
    logoff = 2,
    search = 3,
    displayLab = 4,
    recover = 5,
    quit = 6,
};

int main()
{
    srand(time(0)); //Setting the seed for rand

    Menu instance; 
    instance.printStartup();

    ioHandiling::LogFile activityTracker(logfile); //Logfile
    //instance.startupTimestamp(activityTracker); //For logging purposes, uncomment for startup.

	std::map<int, Computer*> activeComputers;

    bool active = true;

    Lab availableLabs[NUMLABS];
    for(int i = 0; i < NUMLABS; ++i)
    {
        availableLabs[i].assignLabName(UNIVERSITYNAMES[i]);
        availableLabs[i].assignLabSize(LABSIZES[i]);
        availableLabs[i].assignLabLocation(i + 1);
    }

    while(active)
    {
        MenuOption selection = (MenuOption)ioHandiling::promptInt("Please select a menu item. ", 0, 6);

        switch(selection)
        {
            case MenuOption::reprint:
                instance.printMenu();
                break;

            case MenuOption::login:
                instance.simulateLogin(availableLabs, activityTracker, activeComputers);
                break;

            case MenuOption::logoff:
                instance.simulateLogoff(availableLabs, activityTracker, activeComputers);
                break;

            case MenuOption::search:
                instance.searchLab(activeComputers);
                break;

            case MenuOption::displayLab:
                instance.displayLab(availableLabs);
                break;

            case MenuOption::recover:
                instance.recoverUser(availableLabs, activityTracker, activeComputers);
                break;

            case MenuOption::quit:
                active = instance.quitLabTrac(activityTracker);
                break;
        }
    }
} 

void Menu::printHeader()
{
    std::cout << "\n\n|-- LabTrac 2 - Student Computer Lab Tracking System --|\n"
          << "|-- Created by Patrick M. Howard - For education use --|\n|\n";

}

void Menu::printLabs()
{
    for(int i = 0; i < NUMLABS; ++i)
    {
        std::cout << "| Lab #" << i+1 << " for " << UNIVERSITYNAMES[i] << "\n";
    }
}

void Menu::printMenu()
{
    std::string menuOptions[6] =
    {
        "Simulate Login",
        "Simulate Logoff", 
        "Search",
        "Display Lab",
        "Recover User",
        "Quit"
    };

    std::cout << "|\n| MAIN MENU\n";
    for(int i = 0; i < 6; ++i)
    {
        std::cout << "| " << i+1 << ") " << menuOptions[i] << "\n";
    }

    std::cout << "|\n"; 

}

void Menu::startupTimestamp(ioHandiling::LogFile& file) 
{
    file.writeLine("LabTrac2 Started on " + ioHandiling::getTime());
}

void Menu::printStartup()
{
    printHeader();
    printLabs();
    printMenu();
    std::cout << "| Tip: Select \"0\" to reprint this menu! \n";
}

bool Menu::quitLabTrac(ioHandiling::LogFile& file)
{
    std::cout << "|-- Now exiting, goodbye!\n" << "|-- LabTrac 2 - By Patrick M. Howard\n";
    //file.writeLine("Exited LabTrac2 on " + ioHandiling::getTime());
    return false;
}

int Menu::promptUserId()
{
    return ioHandiling::promptInt("Please input a user ID.", 1, 99999);
}

int Menu::promptUniversitySelection()
{
    return ioHandiling::promptInt("Please select a lab.", 1, NUMLABS);
}

void Menu::simulateLogin(Lab labArray[], ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers)
{
    int uniSelection = promptUniversitySelection();
    std::cout << "| Selected " << UNIVERSITYNAMES[uniSelection - 1] << "\n";
    labArray[uniSelection].simulateLogin(log, activeComputers);


}

void Menu::simulateLogoff(Lab labArray[], ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers)
{
    int userID = promptUserId();
    bool loggedOutAUser = false;
    
    for(int i = 0; i < NUMLABS; i++)
    {
        loggedOutAUser = labArray[i].simulateLogoff(userID, log, activeComputers);
    }
    
    
}

//============================================ EXCEPTION HANDLED
void Menu::searchLab(std::map<int, Computer*>& activeComputers)
{
    int userID = promptUserId();

    try
    {
        if(activeComputers.empty())
        {
            std::cout << "| !! - No computers are active, please initiate a computer - !!\n";
            return;
        }


        Computer* selectedComp = activeComputers.find(userID)->second;

        if(selectedComp != nullptr)
        {
            std::cout << "| " 
                    << selectedComp->getStudentName() 
                    << " in Lab " 
                    << selectedComp->getLabLoc()
                    << " at seat " 
                    << selectedComp->getSeatLoc()
                    << "\n";

            return;
        }

    }
    catch(std::bad_alloc e1)
    {

        std::cout << " !! - Unable to locate userID " << ioHandiling::formatUserID(userID) << " - !!\n";  

    }

}
//============================================ EXCEPTION HANDLED



void Menu::displayLab(Lab labArray[])
{ 
    int uniSelection = promptUniversitySelection();
    labArray[uniSelection - 1].displayLab();
}

void Menu::recoverUser(Lab labArray[], ioHandiling::LogFile& log, std::map<int, Computer*>& activeComputers)
{
    int userID = promptUserId();
    int uniSelection = promptUniversitySelection();

    int recoveredID = -1;
    std::string currentLine;

    while (recoveredID != userID)
    {
        currentLine = log.pullLine(0);

        if(currentLine == "eof")
        {
            break;
        }
        if(currentLine.length() > 27)
        {
            recoveredID = stoi(currentLine.substr(27, 5));
        }
    }

    if (recoveredID == userID)
    {
        
        labArray[uniSelection - 1].assignToFirstAvailable(currentLine, log, activeComputers);
    }
}