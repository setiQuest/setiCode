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

int Logfile::m_maxFd = 0;
fd_set Logfile::m_rfds;

/*
 * Constructor
 * Opens specified logfile & gathers information.
 *
 * @param filename name of file
 */
Logfile::Logfile(string filename)
{
    m_logfile = filename;
    openLogfile(m_logfile);
}

/*
 * Destructor
 * Does nothing.
 */
Logfile::~Logfile()
{
}

/**
 * Open logfile.
 *
 * @param filename name of file
 */
void Logfile::openLogfile(string filename)
{
    // Opening the files a+ eliminates the need to touch them to ensure
    // their existence.
    m_fp = fopen(filename.c_str(), "a+");
    if(m_fp == NULL)
    {
        // Change to stderr?
        fprintf(stdout," Could not open %s, EXITING.\n", filename.c_str());
    }

    m_fd = fileno(m_fp);
    if(m_fd > Logfile::m_maxFd)
    {
        Logfile::m_maxFd = m_fd;
    }

    struct stat stbuf;

    if(fstat(m_fd, &stbuf) == 0)
    {
        m_inode = stbuf.st_ino;
    }
    else
    {
        m_inode = -1;
    }
    
}

/*
 * Checks to see if logfile inode has changed; if it has, the most
 * likely reason is that a new logfile has been created--in which case
 * we should switch to reading the new file.
 */
void Logfile::checkRefresh()
{
    struct stat stbuf;

    if (stat(m_logfile.c_str(), &stbuf) == 0)
    {
        if (m_inode != stbuf.st_ino)
        {
            //FIXME: Need exception handling.
            if(fclose(m_fp) == 0)
            {
                openLogfile(m_logfile);
            }
        }
    }       
}

/*
 * Returns the logfile's file descriptor.
 *
 * @return the file descriptor
 */
int Logfile::getFd()
{
    return m_fd;
}

/*
 * Reads a line from logfile, stores in buf.
 *
 * @param buf buffer for storing read line
 * @param bufsize size of read buffer
 */
void Logfile::getLine(char *buf, unsigned long bufsize)
{
    char *s = fgets(buf, bufsize, m_fp);

    if (s == NULL)
    {
        if (feof(m_fp))
        {
            checkRefresh();
        }
    }
}

/**
 * Reads from all Logfile instances.
 */

int Logfile::readLogfiles(list<Logfile> logfiles)
{
    FD_ZERO(&m_rfds);
    FD_SET(0, &m_rfds);

    list<Logfile>::iterator it;

    for(it=logfiles.begin(); it != logfiles.end(); it++)
    {
        FD_SET(it->getFd(), &m_rfds);
    }
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 200000; //1/5 second

    int retVal = -1;

    // FIXME: This results in rapid polling because select() returns
    // immediately when a descriptor in the set is at EOF.
    //
    // Consider a delay by e.g. opting out of &m_rfds for n passes when at EOF?
    retVal = select(Logfile::m_maxFd + 1, &m_rfds, NULL, NULL, &tv);

    return retVal;
}

/**
 * Returns file descriptor set for reads.
 *
 * @return the file descriptor set for reads
 */
fd_set *Logfile::getDescriptors()
{
    return &Logfile::m_rfds;
}
