#pragma once

#include <cstdlib>

#include "LabGroup.hpp"
#include "Menu.hpp"
#include "UserRecoveryLogic.hpp"

struct Config
{
    std::string logFileName;

    const LabProperties* labProperties;
    int totalLabs;
};

struct ProgramContext
{
    LogFile* logFile;
    LabGroup* labGroup;
    Menu* menu;
    UserRecoveryLogic* userRecoveryLogic;
};

class Program
{
public:
    Program(Config& config)
    {
        setRandomSeed();

        context = createProgramContext(config);
    }

    void run()
    {
        auto& menu = *context->menu;
        menu.printStartup();

        while(menu.continueRunningProgram())
        {
            menu.runSelection();
        }
    }

private:
    void setRandomSeed()
    {
        srand(time(0));
    }

    ProgramContext* createProgramContext(Config& config)
    {
        auto logFile = new LogFile(config.logFileName);
        auto labGroup = new LabGroup(
            config.totalLabs,
            config.labProperties,
            *logFile);

        auto userRecoveryLogic = new UserRecoveryLogic(*logFile, *labGroup);
        auto menu = new Menu(*logFile, *labGroup, *userRecoveryLogic);

        auto context = new ProgramContext;
        context->logFile = logFile;
        context->labGroup = labGroup;
        context->menu = menu;
        context->userRecoveryLogic = userRecoveryLogic;

        return context;
    }

    ProgramContext* context;
};