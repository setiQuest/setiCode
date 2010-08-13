/*
 * utils.h
 *
 * Project: OpenSonATA
 * Version: 1.0
 * Author:  Jon Richards (current maintainer)
 *          The OpenSonATA code is the result of many programmers over many
 *          years.
 *
 * A class of general utilities.
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
 * @file utils.h
 * A class of general utilities.
 */

#ifndef UTILS_H
#define UTILS_H

#include <string> //Needed for std::string
#include <iostream>
#include <fstream>
#include <sstream>
#include <ncurses.h>

using namespace std;


 /**
  * A class of general utilities.
  */
 class Utils
{

    public:

        /**
         * The constructor.
         */
        Utils();

        /**
         * The destructor.
         */
        ~Utils();
        /**
         * Convert an unsigned long integer to a string.
         *
         * @param num the number to convert
         * @return the resulting string
         */
        static string itos(unsigned long int num);

        /**
         * Convert an unsigned integer to a string.
         *
         * @param num the number to convert
         * @return the resulting string
         */
        static string itos(unsigned int num);

        /**
         * Convert an integer to a string.
         *
         * @param num the number to convert
         * @return the resulting string
         */
        static string itos(int num);

        /**
         * Convert a float to a string.
         *
         * @param num the number to convert
         * @return the resulting string
         */
        static string ftos(float num);

        /**
         * Convert a string to a float.
         *
         * @param num the number string to convert.
         * @return the resulting float
         */
        static float stof(string num);

        /**
         * Test to see if a string starts with a string.
         *
         * @param substring the sting to test for.
         * @param fullstring the string to search from the beginning.
         * @return bool true if fullsting starts with substring.
         */
        static bool startsWith(string substring, string fullstring);

        /**
         * Draw text on the curses screen with a color.
         *
         * @param y the y position on the screen.
         * @param x the x position on the screen.
         * @param color the color number. Depends on the screen setup.
         * @param text the text to display.
         */
        static void drawColorText(int y, int x, int color, string text);

        /**
         * Draw one space in a color.
         *
         * @param y the y position on the screen.
         * @param x the x position on the screen.
         * @param color the color number. Depends on the screen setup.
         */
        static void drawSquare(int y, int x, int color);

};

#endif

