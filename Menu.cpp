#include "Menu.hpp"

void Menu::runSelection()
{
    MenuOption selection = (MenuOption)ioHandiling::promptInt("Please select a menu item. ", 0, 6);

    switch(selection)
    {
        case MenuOption::reprint:
            printMenu();
            break;

        case MenuOption::login:
            simulateLogin();
            break;

        case MenuOption::logoff:
            simulateLogoff();
            break;

        case MenuOption::search:
            searchLab();
            break;

        case MenuOption::displayLab:
            displayLab();
            break;

        case MenuOption::recover:
            recoverUser();
            break;

        case MenuOption::quit:
            quitLabTrac();
            break;
    }
}

void Menu::printHeader()
{
    std::cout << "\n\n|-- LabTrac 2 - Student Computer Lab Tracking System --|\n"
          << "|-- Created by Patrick M. Howard - For education use --|\n|\n";

}

void Menu::printLabs()
{
    for(int i = 0; i < labGroup.getTotalLabs(); ++i)
    {
        auto lab = labGroup.getLabById(i);
        std::cout << "| Lab #" << i + 1 << " for " << lab->getUniversityName() << "\n";
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
    for(int i = 0; i < TOTAL_OPTIONS; ++i)
    {
        std::cout << "| " << i+1 << ") " << menuOptions[i] << "\n";
    }

    std::cout << "|\n"; 

}

void Menu::startupTimestamp() 
{
    logFile.writeLine("LabTrac2 Started on " + ioHandiling::getTime());
}

void Menu::printStartup()
{
    printHeader();
    printLabs();
    printMenu();
    std::cout << "| Tip: Select \"0\" to reprint this menu! \n";
}

void Menu::quitLabTrac()
{
    std::cout << "|-- Now exiting, goodbye!\n" << "|-- LabTrac 2 - By Patrick M. Howard\n";

    userQuit = true;
}

int Menu::promptUserId()
{
    return ioHandiling::promptInt("Please input a user ID.", 1, 99999);
}

int Menu::promptUniversitySelection()
{
    return ioHandiling::promptInt("Please select a lab.", 1, labGroup.getTotalLabs()) - 1;
}

void Menu::simulateLogin()
{
    int uniSelection = promptUniversitySelection();
    auto lab = labGroup.getLabById(uniSelection);

    std::cout << "| Selected " << lab->getUniversityName() << "\n";

    lab->simulateLogin(logFile, labGroup.getActiveComputers());
}

void Menu::simulateLogoff()
{
    int userID = promptUserId();
    
    try
    {
        labGroup.simulateLogoff(userID);
    }
    catch(std::bad_alloc e1)
    {
        std::cout << " !! - Unable to locate userID " << ioHandiling::formatUserID(userID) << " - !!\n|\n";  
    }
}

void Menu::searchLab()
{
    int userID = promptUserId();

    try
    {
        if(labGroup.hasAnyActiveComputers())
        {
            std::cout << "| !! - No computers are active, please initiate a computer - !!\n";
            return;
        }

        auto selectedComp = labGroup.findUserComputer(userID);

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
        std::cout << " !! - Unable to locate userID " << ioHandiling::formatUserID(userID) << " - !!\n|\n";  
    }

}

void Menu::displayLab()
{ 
    int uniSelection = promptUniversitySelection();

    auto lab = labGroup.getLabById(uniSelection);
    lab->displayLab();
}

void Menu::recoverUser()
{
    int userID = promptUserId();

    auto userRecoveryRecord = userRecoveryLogic.findUserRecoveryRecord(userID);

    if(!userRecoveryRecord.wasFound)
    {
        std::cout << "| !! - Could not find " << ioHandiling::formatUserID(userID) << " in logfile. - !!\n";
    }
    else
    {
        std::cout << "| Found user ID " << ioHandiling::formatUserID(userID) << " in logfile.\n" ;

        int universityId = promptUniversitySelection();
        userRecoveryLogic.recoverUser(userRecoveryRecord, universityId);
    }
}