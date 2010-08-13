/*
 * details.h
 *
 * Project: OpenSonATA
 * Version: 1.0
 * Author:  Jon Richards (current maintainer)
 *          The OpenSonATA code is the result of many programmers over many
 *          years.
 *
 * Manages status details. This is to be used as a base class.
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
 * @file details.h
 * Manages status details. This is to be used as a base class.
 */

#ifndef DETAILS_H
#define DETAILS_H

#include <pthread.h> //Needed for pthread_mutex_t m_mutex
#include <string> //Needed for std::string
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Manages status details. This is to be used as a base class.
 */
class Details
{
    public:
        /** Constructor. */
        Details();

        /** Destructor. */
        ~Details();

        /**
         * Empty the m_details vector.
         */
        void clear();

        /**
         * Add a detail line to the list.
         * A detail line is comprised of key<space>value.
         *
         * @param line the detail line.
         */
        void add(const string line);

        /**
         * Add a detail key::value to the list.
         *
         * @param key the detail key.
         * @param value the detail value.
         */
        void add(const string key, const string value);

        /**
         * Test if a value exists by testing the key.
         *
         * @param key the key.
         * @return true if there is a value for this key.
         */
        bool exists(string key);

        /**
         * Get the value for a key.
         *
         * @param key the key.
         * @return the value for the key, or empty string if it
         * does not exist.
         */
        string getValue(string key);

        /**
         * Get a key:value pair from the list base of the index in the list.
         *
         * @param i the index into the list.
         * @return the key:value pair. Will be "null":"null" if the index
         * is invalid.
         */
        std::pair<string, string> get(int i);

        /**
         * Get all values that have a key that starts with a character
         * substring.
         * 
         * @param keyStart the substring to match with the keys.
         * @return a Details object filled with the key:value pairs.
         */
        Details *getValueFromKeyStartsWith(string keyStart);

        /**
         * Convert the key:value pairs into one string, keach key value
         * separated by a line ending.
         *
         * @param separator the separator to place between the key and the value.
         * @param lineEnd the character(s) to use as a line ending. Usually \r\n.
         * @param maxLineLength the maximum length of a line.
         * @return the resulting multi line string.
         */
        string toString(const string separator, const string lineEnd, int maxLineLength);

        /**
         * Get the character length of the longest key in the list.
         *
         * @return the character length of the longest key in the list.
         */
        int getMaxKeyLength();

        /**
         * Get the number of key:value pairs in the list.
         */
        int size();

        /**
         * Add a line of information about a component to the list.
         *
         * @param line The line of text parse and add to the details list.
         * @return true if an entire record has been read in and is ready for
         * display on the screen.
         */
        virtual bool addWithFilter(string line) { return false; };

        /**
         * Get the number of pages required to display all the information.
         *
         * @param pageRows the number of rows available on the screen.
         * @return the number of pages required to display all the
         * information.
         */
        virtual int getNumPages(int pageRows) { return 0; };

        /**
         * Get the type of this object inherited from the Details class.
         *
         * @return the type as a detail_t enum value.
         */
        virtual int getType() { return detail_type_unknown; };

        /**
         * Get the current page number displayed.
         *
         * @return the current page number displayed.
         */
        virtual int getCurrentPageNumber() { return 1; };

        /**
         * Display the information on the screen.
         *
         * @param pageNum the page number to display.
         * @param pageCols the number of columns on the screen.
         * @param pageRows the number of rows on the screen.
         * @return true if screen has changed, else false.
         */
        virtual bool paint(int pageNum, int pageCols, int pageRows){ return false;};


        enum detail_t
        {
            detail_components,
            detail_signals,
            detail_errors,
            detail_summary,
            detail_top,
            detail_bottom,
            detail_type_unknown
        };

        detail_t m_thisType;

    private:
        /**
         * The std::vector that holds the key:value pairs.
         * The key is the component such as "chan1x" or "dx1000",
         * The value is the full status line.
         */
        std::vector<std::pair<string, string> > m_details;

        /** The mutex that makes this class thread safe.  */
        pthread_mutex_t m_mutex;


};


#endif //DETAILS_H

