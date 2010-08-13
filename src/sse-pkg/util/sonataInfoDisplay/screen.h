/*
 * screen.h
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
 * @file screen.h
 * Manages the curses screen.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "details.h"


using namespace std;

/**
 * Manages the curses screen.
 */
class Screen
{
    public:
        
        /** Constructor. */
        Screen();

        /** Destructor. */
        ~Screen();

        /**
         * Initialize the curses screen.
         */
        void init();

        /**
         * Draws the bottom of the screen. The Function keys.
         */
        void drawBottomMenu();

        /**
         * Handles the screen rezise, which comes in as the result
         * of a SIGWINCH signal.
         * Executes the program "resize" to read in the terminal size.
         *
         * @param sig the signal.
         */
        static void screenResize(int sig);

        /**
         * Catch the control-c to quit screen mode then exit.
         *
         * @param sig the signal.
         */
        static void finish(int sig);

        /**
         * paint the screen.
         *
         * @param details the instance of the object containing the 
         * information to display on the screen.
         */
        void paint(Details *details);

        /**
         * Process key presses.
         * 
         * @param details the Details object to redraw of a key affects 
         * the screen.
         */
        void processKey(Details *details);

        /**
         * Define the different type of screen modes. Currently there
         * is only support for the components screen, but more are to
         * be added later.
         */
        enum screen_modes_t
        {
            screen_mode_components,
            screen_mode_signals,
            screen_mode_errors,
            screen_mode_summary,
            screen_mode_last
        };

    private:

        int m_cols;
        int m_rows;
        bool m_isNewMode;
        int m_page;
        int m_curentPage;
        int m_totalPages;
        screen_modes_t m_screenMode;
        static bool m_resizeEventOccurred;
        static int m_newCols;
        static int m_newRows;

};


#endif //SCREEN_H

