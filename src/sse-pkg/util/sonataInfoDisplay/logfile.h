/*
 * logfile.h
 *
 * Project: OpenSonATA
 * Version: 2.2
 * Author:  Jeff Uphoff (contributor)
 *          The OpenSonATA code is the result of many programmers over many
 *          years.
 *
 * A class for basic logfile handling.
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
 * @file logfile.h
 * A class for basic logfile handling.
 */

#ifndef LOGFILE_H
#define LOGFILE_H

#include <string>
#include <stdio.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <list>

using namespace std;

 /**
  * A class for basic logfile handling.
  */

 class Logfile
{

    public:

        /**
         * The constructor.
         *
         * @param filename name of file
         */
        Logfile(string filename);

        /**
         * The destructor.
         */
        ~Logfile();

        /**
         * Returns the logfile's file descriptor.
         *
         * @return the file descriptor
         */
        int getFd();

        /**
         * Reads a line from logfile.
         *
         * @param buf buffer for storing read line
         * @param bufsize size of read buffer
         */
        void getLine(char *buf, unsigned long bufsize);

        /**
         * Reads from all Logfile instances.
         */
        static int readLogfiles(list<Logfile> logfiles);

    private:

        string logfile;
        FILE *fp;
        int fd;
        ino_t inode;
        static fd_set rfds;     // FIXME: Not yet used.
        static int maxFd;

        /**
         * Open logfile.
         *
         * @param filename name of file
         */
        void openLogfile(string filename);

        /**
         * Checks to see if logfile inode has changed, close & reopen if so.
         */
        void checkRefresh();

};

#endif
