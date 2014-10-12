/*
 * sonataInfoDisplay
 *
 * Project: OpenSonATA
 * Version: 1.0
 * Author:  Jon Richards (current maintainer)
 *          The OpenSonATA code is the result of many programmers over many
 *          years.
 *
 * Displays information in a curses screen while SonATA is running.
 *
 * Copyright 2010 The SETI Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0 Unless required by
 * applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * Attribution must be: “Licensed through SETI” in all published
 * uses of the software including analytics based on the software,
 * combined and merged software, papers, articles, books, reports,
 * web pages, etc.
 */

/**
 * @file main.cpp
 *
 * Displays information in a curses screen while SonATA is running.
 *
 * Project: OpenSonATA
 * <BR>
 * Version: 1.0
 * <BR>
 * Authors:
 * - Jon Richards (current maintainer)
 * - The OpenSonATA code is the result of many programmers over many
 * years.
 */

#include "details.h"
#include "utils.h"
#include "logfile.h"
#include <list>

/**
 * Main entry point of the program.
 *
 * This application requires 3 arguments:
 *  - The system status file that is created in real time when SonATA
 *    is running. This is usually "sse-system-status.txt".
 *  - The system log file that is created in real time when SonATA
 *    is running. This is usually "systemlog-YYYY-MM-DD.txt".
 *  - The error log  file that is created in real time when SonATA
 *    is running. This is usually "errorlog-YYYY-MM-DD.txt".
 *
 * Note: This version does not actually process "systemlog-YYYY-MM-DD.txt" and
 * "errorlog-YYYY-MM-DD.txt". Future development will involve implementing 
 * the reading and displaying of the information in these files.
 */
int main(int argc, char **argv)
{
    string systemStatusFileName = "";
    string systemLogFileName = "";
    string systemErrorFileName = "";
    Screen screen;
    list<Logfile> logfiles;

    Components componentDetails;

    // Print help if not enough arguments on the command line
    if (argc < 3)
    {
        fprintf(stderr, "\nsonataInfoDisplay - curses display for SonATA information\n\n");
        fprintf(stderr, "  USAGE: sonataInfoDisplay <sse-system-status.txt> \\\n");
        fprintf(stderr, "         <systemlog-YYYY-MM-DD.txt> <errorlog-YYYY-MM-DD.txt>\n");
        fprintf(stderr, "  NOTE:  The arguments need to be the file prefixed with the path.\n\n");
        return(1);
    }

    // Read in the arguments.
    systemStatusFileName = argv[1]; 
    systemLogFileName    = argv[2]; 
    systemErrorFileName  = argv[3]; 

    Logfile systemStatusFile = Logfile(systemStatusFileName, &componentDetails);
    Logfile systemLogFile = Logfile(systemLogFileName, NULL);
    Logfile systemErrorFile = Logfile(systemErrorFileName, NULL);

    logfiles.push_back(systemStatusFile);
    logfiles.push_back(systemLogFile);
    logfiles.push_back(systemErrorFile);

    // Initialize the curses screen.
    screen.init();
    screen.screenResize(0);

    // Loop foever
    while(1)
    {
        Logfile::readLogfiles(logfiles, &screen);
        screen.processKey(&componentDetails);
    }
    return 0;
}
