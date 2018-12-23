#pragma once

#include <string>
#include <map>

#include "ioHandiling.hpp"
#include "Lab.hpp"

using ioHandiling::LogFile;

struct LabProperties
{
    int size;
    std::string universityName;
};

struct LabGroup
{
    LabGroup(int totalLabs_, const LabProperties* labProperties, LogFile& logFile_)
        : logFile(logFile_)
    {
        totalLabs = totalLabs_;
        labs = new Lab[totalLabs];

        for(int i = 0; i < totalLabs; ++i)
        {
            labs[i].assignLabName(labProperties[i].universityName);
            labs[i].assignLabSize(labProperties[i].size);
            labs[i].assignLabLocation(i + 1);
        }
    }

    Lab* getLabById(int id)
    {
        if(id < 0 || id > totalLabs)
        {
            return nullptr;     // Or throw exception?
        }

        return &labs[id];
    }

    void simulateLogoff(int userID)
    {
        Computer* selectedComp = activeComputers.find(userID)->second;

        if(selectedComp != nullptr)
        {
            int labId = selectedComp->getLabLoc();
            auto lab = getLabById(labId);

            lab->simulateLogoff(userID, logFile, activeComputers);
        }
    }

    bool hasAnyActiveComputers()
    {
        return !activeComputers.empty();
    }

    Computer* findUserComputer(int userId)
    {
        return activeComputers.find(userId)->second;
    }

    std::map<int, Computer*>& getActiveComputers()
    {
        return activeComputers;
    }

    int getTotalLabs()
    {
        return totalLabs;
    }

private:
    LogFile& logFile;

    Lab* labs;
    int totalLabs;
    std::map<int, Computer*> activeComputers;
};