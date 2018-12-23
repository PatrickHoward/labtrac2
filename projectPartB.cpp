/*
  PROJECT PART B - Patrick M. Howard (pmh41) - LabTrac
  Copyright 2018, all rights reserved. 
  pmh41@zips.uakron.edu
  ver 0.34 9.28.2018
  Purpose: This program manages computer labs for several different universities. It can sign on, sign off users and keep track of 
           where they are in the system. 
*/

#include "Program.hpp"

using namespace ioHandiling;
using namespace std;

Config buildConfig()
{
    const int TOTAL_LABS = 8;

    static const LabProperties labProperties[TOTAL_LABS] = 
    {
        { 19, "The University of Michigan" },
        { 15, "The University of Pittsburgh" },
        { 24, "Stanford University" },
        { 33, "Arizona State University" },
        { 4,  "North Texas State University" },
        { 17, "The University of Alabama, Huntsville" },
        { 55, "Princeton University" },
        { 37, "Duquesne University" }
    };

    Config config;
    config.logFileName = "labTrac_log.txt";
    config.totalLabs = TOTAL_LABS;
    config.labProperties = labProperties;

    return config;
}

int main()
{
    auto config = buildConfig();

    Program program(config);
    program.run();
}
