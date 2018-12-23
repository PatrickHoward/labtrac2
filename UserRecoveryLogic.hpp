#pragma once

#include <string>

#include "ioHandiling.hpp"
#include "LabGroup.hpp"

using ioHandiling::LogFile;

struct UserRecoveryRecord
{
    UserRecoveryRecord(bool wasFound_, std::string logLine_)
        : wasFound(wasFound_),
        logLine(logLine_)
    {

    }

    bool wasFound;
    std::string logLine;
};

class UserRecoveryLogic
{
public:
    UserRecoveryLogic(LogFile& logFile_, LabGroup& labGroup_)
        : logFile(logFile_),
        labGroup(labGroup_)
    {

    }

    UserRecoveryRecord findUserRecoveryRecord(int userID)
    {
        int recoveredID = -1;
        std::string currentLine;

        while (recoveredID != userID)
        {
            currentLine = logFile.pullLine(0);

            if(currentLine == "eof")
            {
                break;
            }
            if(currentLine.length() > 27)
            {
                recoveredID = stoi(currentLine.substr(27, 5));
            }
        }

        return UserRecoveryRecord(
            recoveredID == userID,
            currentLine);
    }

    void recoverUser(UserRecoveryRecord& record, int universityId)
    {
        auto lab = labGroup.getLabById(universityId);
        lab->assignToFirstAvailable(
            record.logLine,
            logFile,
            labGroup.getActiveComputers());
    }

private:
    LogFile& logFile;
    LabGroup& labGroup;
};

