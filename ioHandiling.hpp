#ifndef IOHANDILING_HPP
#define IOHANDILING_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <map>



namespace ioHandiling
{
    //Pr - Takes a string, a minimum accepted value, and a maximum accepted value
    //Po - Returns an integer within the accepted range.
    int promptInt(std::string question, int minVal, int maxVal);

    //Pr - Takes a string, a minimum accepted value, and a maximum accepted value
    //Po - Returns a string with a length within the accepted range.
    std::string promptString(std::string question, int minLen, int maxLen);

    //Pr - Nothing
    //Po - Returns a string of the time, like the prototype says.
    std::string getTime();

    //Pr - Takes in an int betweeen 0 - 99999, throws an exception if a unexpected number is given.
    //Po - Returns a formatted string for displaying purposes, so 95 returns 00095.
    std::string formatUserID(int userID);
    
    class LogFile
    {
    public:
        LogFile(std::string& fileName_);

        //Pr - Takes a string in
        //Po - Void function, puts it into a file specified at the beginning.
        void writeLine(const std::string& line);

        //Pr - Takes a close flag in case the desired line is pulled.
        //Po - Returns a string of the last line in a file, returns an "eof" if the end of file is reached.
        std::string pullLine(bool close);

        ~LogFile();
        
    private:
        std::string fileName;
        std::fstream outputFile;
    };
}

#endif
