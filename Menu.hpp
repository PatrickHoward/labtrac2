#pragma once

#include "ioHandiling.hpp"
#include "LabGroup.hpp"
#include "UserRecoveryLogic.hpp"

using ioHandiling::LogFile;

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

class Menu
{
public:
    Menu(LogFile& logFile_, LabGroup& labGroup_, UserRecoveryLogic& userRecoveryLogic_)
        : logFile(logFile_),
        labGroup(labGroup_),
        userRecoveryLogic(userRecoveryLogic_),
        userQuit(false)
    {

    }

    bool continueRunningProgram()
    {
        return !userQuit;
    }

    void printStartup();
    void runSelection();

private:
    void printHeader(); 

    void printLabs();

    void printMenu();

    void startupTimestamp(); 

    int promptUserId();

    int promptUniversitySelection();

    void simulateLogin();

    void simulateLogoff();

    void searchLab();

    void displayLab();

    void recoverUser();

    void quitLabTrac();

    static const int TOTAL_OPTIONS = 6;

    LogFile& logFile;
    LabGroup& labGroup;
    UserRecoveryLogic& userRecoveryLogic;

    bool userQuit;
};

