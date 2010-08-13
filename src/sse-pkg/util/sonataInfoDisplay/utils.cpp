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
 * @file utils.cpp
 * Contains general utilities.
 **/

#include "utils.h"

/*
 * Constructor
 * Does nothing.
 */
Utils::Utils()
{
}

/*
 * The destructor.
 * Does nothing.
 */
Utils::~Utils()
{
}

/*
 * Convert an unsigned long integer to a string.
 *
 * @param num the number to convert
 * @return the resulting string
 */
string Utils::itos(unsigned long int num)
{
    stringstream s;
    s << num;
    return s.str();
}

/*
 * Convert an unsigned integer to a string.
 *
 * @param num the number to convert
 * @return the resulting string
 */
string Utils::itos(unsigned int num)
{
    stringstream s;
    s << num;
    return s.str();
}

/*
 * Convert an integer to a string.
 *
 * @param num the number to convert
 * @return the resulting string
 */
string Utils::itos(int num)
{
    stringstream s;
    s << num;
    return s.str();
}

/*
 * Convert a float to a string.
 *
 * @param num the number to convert
 * @return the resulting string
 */
string Utils::ftos(float num)
{
    stringstream s;
    s << num;
    return s.str();
}

/*
 * Convert a string to a float.
 *
 * @param num the number string to convert.
 * @return the resulting float
 */
float Utils::stof(string num)
{
    istringstream s(num);
    float f;
    s >> f;
    return f;
}


/*
 * Test to see if a string starts with a string.
 *
 * @param substring the sting to test for.
 * @param fullstring the string to search from the beginning.
 * @return bool true if fullsting starts with substring.
 */
bool Utils::startsWith(string substring, string fullstring)
{
    if(fullstring.compare((size_t)0, substring.size(), substring))
        return false;
    else
        return true;
}

/*
 * Draw text on the curses screen with a color.
 *
 * @param y the y position on the screen.
 * @param x the x position on the screen.
 * @param color the color number. Depends on the screen setup.
 * @param text the text to display.
 */
void Utils::drawColorText(int y, int x, int color, string text)
{
    move(y, x);
    attrset(COLOR_PAIR(color));
    addstr(text.c_str());
    attrset(COLOR_PAIR(0));
}

/*
 * Draw one space in a color.
 *
 * @param y the y position on the screen.
 * @param x the x position on the screen.
 * @param color the color number. Depends on the screen setup.
 */
void Utils::drawSquare(int y, int x, int color)
{
    move(y, x-1);
    attrset(COLOR_PAIR(color));
    addstr("   ");
    attrset(COLOR_PAIR(0));
}


