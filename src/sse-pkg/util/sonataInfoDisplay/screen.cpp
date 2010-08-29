/*
 * screen.cpp
 *
 * Project: OpenSonATA
 * Version: 1.0
 * Author:  Jon Richards (current maintainer)
 *          The OpenSonATA code is the result of many programmers over many
 *          years.
 *
 * Manages the curses screen.
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
 * @file screen.cpp
 * Manages the curses screen.
 */

#include "screen.h"
#include "utils.h"


bool Screen::m_resizeEventOccurred = false;
int Screen::m_newRows = -1;
int Screen::m_newCols = -1;

/** Define the bottom menu area to have no height. In future
 * versions we will add a bottom menu, increase this to "1".
 */
#define BOTTOM_MENU_HEIGHT 0

/* Constructor. */
Screen::Screen()
{
    Screen::m_resizeEventOccurred = false;
    Screen::m_newRows = -1;
    Screen::m_newCols = -1;
    m_screenMode = screen_mode_components;
    m_page = 1;
    m_isNewMode = false;
    m_rows = m_newRows;
    m_cols = m_newCols;
    (void) signal(SIGINT, Screen::finish);         /* arrange interrupts to terminate */
    (void) signal(SIGWINCH, Screen::screenResize); /* Catch the resize signal */
    m_rows = m_newRows;
    m_cols = m_newCols;

}


/* Destructor. */
Screen::~Screen()
{
}

/*
 * Initialize the curses screen.
 */
void Screen::init()
{
    initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) noecho();
    timeout(1);

    if (has_colors())
    {
        start_color();

        /*
         * Simple color assignment, often all we need.  Color pair 0 cannot
         * be redefined.  This example uses the same value for the color
         * pair as for the foreground color, though of course that is not
         * necessary:
         */
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
        init_pair(8, COLOR_RED,   COLOR_RED);
        init_pair(9, COLOR_CYAN,   COLOR_CYAN);
        init_pair(10, COLOR_GREEN,   COLOR_GREEN);
        init_pair(11, COLOR_BLACK,   COLOR_BLACK);
        init_pair(12, COLOR_BLACK,   COLOR_YELLOW);
    }

    drawBottomMenu();

}

/*
 * Handles the screen rezise, which comes in as the result
 * of a SIGWINCH signal.
 * Uses ioctl(TIOCGWINSZ) to obtain the terminal size.
 *
 * @param sig the signal.
 */
void Screen::screenResize(int sig)
{
    struct winsize size;
    Screen::m_resizeEventOccurred = true;

    if (ioctl(fileno(stdout), TIOCGWINSZ, &size) == 0)
    {
        Screen::m_newCols = size.ws_col;
        Screen::m_newRows = size.ws_row;
    }
}

/*
 * Catch the control-c to quit screen mode then exit.
 *
 * @param sig the signal.
 */
void Screen::finish(int sig)
{
    endwin();
    exit(0);
}

/*
 * Draws the bottom of the screen. The Function keys.
 */
void Screen::drawBottomMenu()
{

    /** @todo Multiple report screens need to be implemented. Until this is working
     * the bottom menu should not be displayed.
     */

    /*
       int centerPos = 0;
       int width = (m_cols/(screen_mode_last - screen_mode_components +1));

       for(int i = screen_mode_components; i<screen_mode_last; i++)
       {
       centerPos = (i+1)*width;
       if(m_screenMode == i) attrset(COLOR_PAIR(6)); //magenta
       else attrset(COLOR_PAIR(5)); //cyan

       if(i == screen_mode_components)
       {
       move(m_rows-1, centerPos - (int)strlen("1-Status")/2);
       addstr("F1 - Status");
       }
       if(i == screen_mode_signals)
       {
       move(m_rows-1, centerPos - (int)strlen("2-Signals")/2);
       addstr("F2 - Signals");
       }
       if(i == screen_mode_errors)
       {
       move(m_rows-1, centerPos - (int)strlen("2-Errors")/2);
       addstr("F3 - Errors");
       }
       if(i == screen_mode_summary)
       {
       move(m_rows-1, centerPos - (int)strlen("4-Summary")/2);
       addstr("F4 - Summary");
       }

       attrset(COLOR_PAIR(0));
       }
     */
    return;

}

/*
 * paint the screen.
 *
 * @param details the instance of the object containing the
 * information to display on the screen.
 */
void Screen::paint(Details *details)
{
    bool shouldRefresh = false;
    string line;

    if(Screen::m_resizeEventOccurred == true)
    {
        Screen::m_resizeEventOccurred = false;
        m_rows = m_newRows;
        m_cols = m_newCols;
        shouldRefresh = true; 
        endwin();
        init();
        clear();
        drawBottomMenu();
    }

    if(m_screenMode == details->getType())
    {
        if(m_page > details->getNumPages(m_rows-BOTTOM_MENU_HEIGHT))
            m_page = details->getNumPages(m_rows-BOTTOM_MENU_HEIGHT);

        if(m_isNewMode == true)
        {
            m_page = details->getCurrentPageNumber();
            m_isNewMode = false;
            clear();
            shouldRefresh = true;
        }
        if(details->paint(m_page, m_cols, m_rows-BOTTOM_MENU_HEIGHT))
        {
            shouldRefresh = true;
        }
    }

    //Print the page
    line = "Page " + Utils::itos(m_page) + " of " + 
        Utils::itos(details->getNumPages(m_rows-BOTTOM_MENU_HEIGHT));
    move(0, m_cols-line.size());
    addstr(line.c_str());

    if(details->getNumPages(m_rows-BOTTOM_MENU_HEIGHT) == m_page)
        line = "8=PgDn";
    else if(m_page == 1)
        line = "9=PgUp";
    else
        line = "8=PgDn, 9=PgUp";
    move(1, m_cols-line.size());
    line += "     ";
    addstr(line.c_str() );

    //Park cursor
    move(m_rows-1, m_cols-1);

    if(shouldRefresh == true)
    {
        refresh();
    }

}

/*
 * Process key presses.
 *
 * @param details the Details object to redraw of a key affects
 * the screen.
 */
void Screen::processKey(Details *details)
{
    char key[5];

    int ch = getch();

    //Print the keypress in the lower left corner
    //For debugging keypresses
    /*
       if(ch != -1)
       {
       sprintf(key, "%d", ch);
       move(m_rows-BOTTOM_MENU_HEIGHT, m_cols-4 );
       addstr("    ");
       move(m_rows-BOTTOM_MENU_HEIGHT, m_cols-4 );
       addstr(key);
       }
     */

    /** @todo Add multiple screens that change based on key presses. */
    /*
    if(ch == 49)
    {
    m_screenMode = screen_mode_components;
    m_isNewMode = true;
    drawBottomMenu();
    refresh();
    }
    if(ch == 50)
    {
    m_screenMode = screen_mode_signals;
    m_isNewMode = true;
    drawBottomMenu();
    refresh();
    }
    if(ch == 51)
    {
    m_screenMode = screen_mode_errors;
    m_isNewMode = true;
    drawBottomMenu();
    refresh();
    }
    if(ch == 52)
    {
    m_screenMode = screen_mode_summary;
    m_isNewMode = true;
    drawBottomMenu();
    refresh();
    }
     */

    //Decrement the page if the '8' key is pressed.
    if(ch == 56)
    {
        m_page--;
        if(m_page <1 ) m_page = 1;        
        drawBottomMenu();
        paint(details);
        refresh();
    }

    //Increment the page if the '9' key is pressed.
    if(ch == 57)
    {
        m_page++;
        drawBottomMenu();
        paint(details);
        refresh();
    }


}
