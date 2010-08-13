/*
 * components.h
 *
 * Project: OpenSonATA
 * Version: 1.0
 * Author:  Jon Richards (current maintainer)
 *          The OpenSonATA code is the result of many programmers over many
 *          years.
 *
 * Manages status details about system components.
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
 * @file components.h
 * Manages status details about system components.
 */

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "details.h" 

using namespace std;

/**
 * Manages status details about system components such as dx's, 
 * channelizers, etc..
 * Inherits from the Details class.
 */
class Components: public Details
{
    public:

        /** Constructor. */
        Components();

        /**
         * Add a line of information about a component to the list.
         * The information is filtered to accept only lines that start with
         * channelizer, dx, arch, tscope, beam, array, primary, and NSS.
         * 
         * @param line The line of text read in from the 
         * "sse-system-status.txt" file.
         * @return true if an entire record of system statuses have been read
         * int. The end of a record is marked in "sse-system-status.txt" by a
         * line starting with "=============". Else, false.
         */
        bool addWithFilter(string line);

        /**
         * Get the number of pages required to display all the information.
         *
         * @param pageRows the number of rows available on the screen.
         * @return the number of pages required to display all the
         * information.
         */
        int getNumPages(int pageRows);

        /**
         * Get the type of this object inherited from the Details class.
         *
         * @return the type as a detail_t enum value.
         */
        int getType();

        /**
         * Get the current page number displayed.
         *
         * @return the current page number displayed.
         */
        int getCurrentPageNumber();

        /**
         * Display the information on the screen.
         *
         * @param pageNum the page number to display.
         * @param pageCols the number of columns on the screen.
         * @param pageRows the number of rows on the screen.
         * @return true if screen has changed, else false.
         */
        bool paint(int pageNum, int pageCols, int pageRows);


    private:
        int m_lastRequestedPage;
        int m_lastReportedCols;
        int m_lastReportedRows;
        string m_time;
        string m_date;
        string m_activity;

        string m_fullPage[2];

        int m_fullPageIndex;
        string  m_currentPageBuffer;
        int m_pageCount;

        std::vector<string> m_screenBuffer;

        int m_chanTotalCount;
        int m_chanRunningCount;
        int m_dxOfflineCount;
        int m_dxIdleCount;
        int m_dxBaseAccumCount;
        int m_dxDataCollCount;
        int m_dxSigDetCount;
        int m_dxTotalCount;
        float m_minDxFreqMHz;
        float m_maxDxFreqMHz;
        int m_detailsCount;

        string m_channelizerSummary;
        string m_dxSummary;

        int m_lastFreqRangeStringLen;

};


#endif //COMPONENTS_H

