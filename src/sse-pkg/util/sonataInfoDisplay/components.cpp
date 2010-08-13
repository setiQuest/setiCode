/*
 * components.cpp
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
 * @file components.cpp
 * Manages status details about system components.
 */

#include "components.h"
#include "utils.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
 * Constructor.
 */
Components::Components() : Details()
{
  m_lastRequestedPage = -1;
  m_lastReportedCols = -1;
  m_lastReportedCols = -1;

  m_fullPage[0] = "";
  m_fullPage[1] = "";

  m_fullPageIndex = 0;
  m_currentPageBuffer = "";

  m_thisType = detail_components;

  m_time = "00:00:00 UTC";
  m_date = "0000-00-00";
  m_activity = "None";

  m_screenBuffer.clear();

  m_chanTotalCount = 0;
  m_chanRunningCount = 0;
  m_dxOfflineCount = 0;
  m_dxIdleCount = 0;
  m_dxBaseAccumCount = 0;
  m_dxDataCollCount = 0;
  m_dxSigDetCount = 0;
  m_dxTotalCount = 0;

  m_channelizerSummary = "";

  m_minDxFreqMHz = 9999999.0;
  m_maxDxFreqMHz = -1;

  m_lastFreqRangeStringLen = 0;

  m_detailsCount = 0;
}

/*
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
bool Components::addWithFilter(string line)
{
    if(Utils::startsWith("chan", line))
    {
        size_t pos = line.find("UTC");
        if(pos != string::npos)
        {
            line = line.replace(pos, (size_t)4, "");
            pos = line.find("UTC", pos+1);
        }

        m_chanTotalCount++;

        pos = line.find("Run");
        if(pos != string::npos)
        {
            m_chanRunningCount++;
        }

        add((line));
    }
    else if(Utils::startsWith("dx", line))
    {

        string newLine = line;

        size_t pos = newLine.find("UTC");
        if(pos != string::npos && pos < newLine.size() - 5)
        {
            newLine = newLine.replace(pos, (size_t)4, "");
        }

        m_dxTotalCount++;

        pos = line.find("ffline");
        if(pos != string::npos)
        {
            m_dxOfflineCount++;
        }

        pos = line.find("No Activities");
        if(pos != string::npos)
        {
            m_dxIdleCount++;
        }

        pos = line.find("Base Accum");
        if(pos != string::npos)
        {
            m_dxBaseAccumCount++;
        }

        pos = line.find("Data Coll");
        if(pos != string::npos)
        {
            m_dxDataCollCount++;
        }

        pos = line.find("Sig Det");
        if(pos != string::npos)
        {
            m_dxSigDetCount++;
        }

        //Attempt to read the activity number, if there is one
        //dx1001 (beam1) 2010-08-07 00:19:34 UTC  Act 2735: Init  Sky: 8424.914 MHz Chan: 13
        pos = newLine.find("Act ");
        if(pos != string::npos)
        {
            size_t pos2 = newLine.find(": ");
            if(pos2 != string::npos)
                m_activity = newLine.substr(pos + 4, (pos2-pos-4)); 
        }

        //Determine the min and max freq
        int channel = -1;
        pos = newLine.find("Chan:");
        if(pos != string::npos) channel = Utils::stof(newLine.substr(pos+5));
        if(channel > 0)
        {
            pos = newLine.find("Sky:");
            if(pos != string::npos)
            {
                size_t pos2 = newLine.find("MHz");
                if(pos2 != string::npos)
                {
                    float freq = Utils::stof(newLine.substr((pos+4), (pos2-pos-4)));
                    if(freq < m_minDxFreqMHz) m_minDxFreqMHz = freq;
                    if(freq > m_maxDxFreqMHz) m_maxDxFreqMHz = freq;
                }
            }
        }

        add((newLine));
    }
    else if(Utils::startsWith("arch", line))
    {
        add((line));
    }
    else if(Utils::startsWith("tscope", line))
    {
        add(line);
    }
    else if(Utils::startsWith("beam", line))
    {
        add(line);
    }
    else if(Utils::startsWith("array", line))
    {
        add(line);
    }
    else if(Utils::startsWith("primary", line))
    {
        add(line);
    }
    else if(Utils::startsWith("NSS", line))
    {
        this->clear();
        size_t pos = line.find("UTC");
        if((int)pos >= 9 && pos != string::npos)
            m_time = line.substr(pos - 9, 12); 
        if((int)pos >= 20 && pos != string::npos)
            m_date = line.substr(pos - 20, 10); 

        m_chanTotalCount = 0;
        m_chanRunningCount = 0;
        m_dxOfflineCount = 0;
        m_dxIdleCount = 0;
        m_dxBaseAccumCount = 0;
        m_dxDataCollCount = 0;
        m_dxSigDetCount = 0;
        m_dxTotalCount = 0;
        m_minDxFreqMHz = 9999999.0;
        m_maxDxFreqMHz = -1;

    }
    else if(Utils::startsWith("=========", line))
    {
        m_lastReportedCols  = -1;
        m_lastReportedRows  = -1;

        if(m_fullPageIndex == 0) m_fullPageIndex = 1;
        else m_fullPageIndex = 0;

        //Compose the channelizer summary string
        m_channelizerSummary = "Total Channelizers=" + Utils::itos(m_chanTotalCount);
        if(m_chanRunningCount> 0) m_channelizerSummary += 
            ", Running=" + Utils::itos(m_chanRunningCount);

        //Dx Summary
        m_dxSummary = "Total Dxs=" + Utils::itos(m_dxTotalCount);
        if(m_dxOfflineCount > 0) m_dxSummary += ", Offline=" + Utils::itos(m_dxOfflineCount);
        if(m_dxIdleCount>0) m_dxSummary += ", Idle=" + Utils::itos(m_dxIdleCount);
        if(m_dxBaseAccumCount > 0) m_dxSummary += ", Base Accum=" + Utils::itos(m_dxBaseAccumCount);
        if(m_dxDataCollCount > 0) m_dxSummary += ", Data Coll=" + Utils::itos(m_dxDataCollCount);
        if(m_dxSigDetCount > 0) m_dxSummary += ", Sig Det=" + Utils::itos(m_dxSigDetCount);

        m_detailsCount = Details::size();

        usleep(10000);
        return true;

    }

    return false;

}

/*
 * Display the information on the screen.
 *
 * @param pageNum the page number to display.
 * @param pageCols the number of columns on the screen.
 * @param pageRows the number of rows on the screen.
 * @return true if screen has changed, else false.
 */
bool Components::paint(int pageNum, int pageCols, int pageRows)
{

    bool hasChanged = false;
    char tempLine[65];

    //If the page or size has changed, clear the buffer.
    if(pageNum != m_lastRequestedPage || pageRows != m_lastReportedRows)
    {
        m_screenBuffer.clear();  
        m_lastRequestedPage = pageNum;
        m_lastReportedRows = pageRows;
    }

    //Note: 3 lines at the top: time and title, activity, blank
    //Note: 3 lines at the bottom: blank, cahnnelizer summary, dx summary
    int realRows = pageRows -3 -3;
    if(pageNum > getNumPages(pageRows)) pageNum = getNumPages(pageRows);
    int vectorStartIndex = (pageNum-1) * realRows ;
    string line;

    //Define a blank line
    string blank(pageCols, ' ');

    //Draw the header
    string headerString = "SonATA System Status";
    move(0,0);
    addstr(blank.c_str());
    move(0,0);
    line = m_time;
    addstr(line.c_str());
    Utils::drawColorText(0, pageCols/2 - line.size()/2, 3, headerString);

    //Draw the activity number
    move(1,0);
    line = "Activity: " + m_activity;
    line.resize(pageCols, ' ');
    addstr(line.c_str());

    //The starting row is 3 to get past the header and a blank line
    int startRow = 3;

    //Loop through the gathered data displaying the appropriate lines.
    for(int i = 0; i<realRows; i++)
    {
        int vectorIndex = vectorStartIndex + i;

        if(vectorIndex >= Details::size())
        {
            move(startRow+i, 0);
            addstr(blank.c_str());
        }
        else
        {
            std::pair<string, string> keyval = Details::get(vectorIndex);
            line = (string)keyval.first;
            line.resize(9, ' ');
            line += (string)keyval.second;
            line.resize(pageCols, ' ');

            //If not defined yet, add to vector
            if(i >= (int)m_screenBuffer.size())
            {
                m_screenBuffer.push_back(line);
                move(startRow+i, 0);
                addstr(line.c_str());
                hasChanged = true;
            }
            else if(m_screenBuffer[i].compare(line)) //If line changed, redraw.
            {
                m_screenBuffer[i] = line;
                move(startRow+i, 0);
                addstr(line.c_str());
                hasChanged = true;
            }

            //Highlight the second column with state color coding.
            if(line.find("Offline") != string::npos)
                Utils::drawSquare(startRow+i, 7, 8);
            else if(line.find("Run") != string::npos)
                Utils::drawSquare(startRow+i, 7, 10);
            else
                Utils::drawSquare(startRow+i, 7, 9);


        }
    }

    //Draw the channelizer summary
    m_channelizerSummary.resize(pageCols, ' ');
    Utils::drawColorText(pageRows-2, 0, 2, m_channelizerSummary);

    //Draw the Dx summary
    m_dxSummary.resize(pageCols, ' ');
    Utils::drawColorText(pageRows-1, 0, 2, m_dxSummary);

    //Draw the frequency range if currently collecting data.
    if(m_lastFreqRangeStringLen > 0)
        Utils::drawColorText(pageRows-1, 
                pageCols-m_lastFreqRangeStringLen-1, 2, blank);
    if(m_maxDxFreqMHz > 50.0 && m_minDxFreqMHz > -1)
    {
        sprintf(tempLine, "%.04f to %.04f MHz", m_minDxFreqMHz, m_maxDxFreqMHz);
        Utils::drawColorText(pageRows-1, pageCols-strlen(tempLine)-1, 2, tempLine);
        m_lastFreqRangeStringLen = (int)strlen(tempLine);
    }

    //Park the cursor in the lower right corner
    move(pageRows-1, pageCols-1);

    return hasChanged;

}

/*
 * Get the number of pages required to display all the information.
 *
 * @param pageRows the number of rows available on the screen.
 * @return the number of pages required to display all the
 * information.
 */
int Components::getNumPages(int pageRows)
{
    //Note: 3 lines at the top: time and title, activity, blank
    //Note: 3 lines at the bottom: blank, cahnnelizer summary, dx summary
    int realRows = pageRows -3 -3;

    return (int)(m_detailsCount/realRows) + 1;
}

/*
 * Get the type of this object inherited from the Details class.
 *
 * @return the type as a detail_t enum value.
 */
int Components::getType()
{
    return m_thisType;
}

/*
 * Get the current page number displayed.
 *
 * @return the current page number displayed.
 */
int Components::getCurrentPageNumber()
{
    if(m_lastRequestedPage <= 0) return 1;
    return m_lastRequestedPage;
}
