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
#include "components.h"
#include "screen.h"

using namespace std;

 /**
  * A class for basic logfile handling.
  */

 class Logfile
{

    public:

        /**
         * Constructor
	 * Opens specified logfile & gathers information.
         *
         * @param filename name of file
         */
        Logfile(string filename, Components *details);

        /**
         * Destructor
	 * Does nothing.
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
         * @param bufsize size of buffer for storing read line
         */
        void getLine(char *buf, unsigned long bufsize);

        /**
         * Reads from all Logfile instances.
	 *
	 * @param logfiles linked list of open logfiles
	 *
	 * @return the number of file descriptors ready for reading
         */
        static int readLogfiles(list<Logfile> logfiles,
				int *linesSinceLastStatus,
				time_t *lastStatusTime,
				Screen *screen);

	/**
	 * Returns file descriptor set for reads.
	 *
	 * @return the file descriptor set for reads
	 */
	static fd_set *getDescriptors(); 	// FIXME: Will be
						// private once all file
						// handling is removed
						// from main().


    private:

	/** Filename of logfile */
        string m_logfile;
	/** FILE pointer of open logfile */
        FILE *m_fp;
	/** File descriptor of open logfile */
        int m_fd;
	/** Inode of open logfile */
        ino_t m_inode;

	/** Maximum open logfile descriptor */
        static int m_maxFd;
	/** File-descriptor set used for select() reads */
        static fd_set m_rfds;

	/** Input-line filter */
	Components *m_details;

        /**
         * Open logfile.
         *
         * @param filename name of logfile
         */
        void openLogfile(string filename);

        /**
         * Checks to see if logfile inode has changed, close & reopen if so.
         */
        void checkRefresh();

};

#endif
