/*
 * logfile.cpp
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
 * @file logfile.cpp
 * Contains logfile handling.
 */

#include "logfile.h"

/*
 * Constructor
 * Opens specified logfile & gathers information.
 *
 * @param filename name of file
 */
Logfile::Logfile(string filename)
{
    // Opening the files a+ eliminates the need to touch them to ensure
    // their existence.
    fp = fopen(filename.c_str(), "a+");
    if(fp == NULL)
    {
	// Change to stderr?
	fprintf(stdout," Could not open %s, EXITING.\n", filename.c_str());
    }

    fd = fileno(fp);

    struct stat stbuf;

    if(fstat(fd, &stbuf) == 0)
    {
	inode = stbuf.st_ino;
    }
    else
    {
	inode = -1;
    }
}

/*
 * Destructor
 * Does nothing.
 */
Logfile::~Logfile()
{
}

/*
 * Checks to see if logfile inode has changed; if it has, the most
 * likely reason is that a new logfile has been created--in which case
 * we should switch to reading it.
 */
int Logfile::checkInode()
{
    return 0;
}

/*
 * Returns the logfile's file descriptor.
 *
 * @return the file descriptor
 */
int Logfile::getFd()
{
    return fd;
}

/*
 * Reads a line from logfile, stores in buf.
 *
 * @param buf buffer for storing read line
 * @param bufsize size of read buffer
 */
void Logfile::getLine(char *buf, unsigned long bufsize)
{
    fgets(buf, bufsize, fp);
}
