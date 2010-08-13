/*
 * details.cpp
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
 * @file details.cpp
 * Manages status details. This is to be used as a base class.
 */

#include "details.h"

/* Constructor. */
Details::Details()
{
    pthread_mutex_init(&m_mutex,NULL);
    m_details.reserve(1000);
    clear();
}

/* Destructor. */
Details::~Details()
{
    clear();
    pthread_mutex_destroy(&m_mutex);
}

/*
 * Empty the m_details vector.
 */
void Details::clear()
{
    pthread_mutex_lock(&m_mutex);
    m_details.clear();
    pthread_mutex_unlock(&m_mutex);
}

/*
 * Add a detail line to the list.
 * A detail line is comprised of key<space>value.
 *
 * @param line the detail line.
 */
void Details::add(const string line)
{
    string thisLine = line;

    //Remove tabs, replace with a space.
    size_t pos = thisLine.find("\t");
    while(pos != string::npos)
    {
        thisLine.replace(pos, 1, " ");
        pos = thisLine.find("\t");
    }

    pos = thisLine.find("\n");
    while(pos != string::npos)
    {
        thisLine.replace(pos, 1, " ");
        pos = thisLine.find("\n");
    }

    pos = thisLine.find("\r");
    while(pos != string::npos)
    {
        thisLine.replace(pos, 1, " ");
        pos = thisLine.find("\r");
    }

    pos = thisLine.find(" ");
    while(pos == 0)
    {
        thisLine.replace(pos, 1, "");
        pos = thisLine.find(" ");
    }

    //Get the position of the first whitespace.
    pos = thisLine.find_first_of(" ");
    if(pos == string::npos) return; 

    string key = thisLine.substr(0, pos);
    string value = thisLine.substr(pos+1, string::npos);

    //trin the spaces on the left.
    pos = value.find(" ");
    while(pos == 0)
    {
        value.replace(pos, 1, "");
        pos = value.find(" ");
    }

    //Add the key:value pair to the m_details map.
    pthread_mutex_lock(&m_mutex);
    std::pair<string, string> keyval;
    keyval.first = key;
    keyval.second = value;
    m_details.push_back(keyval);
    //m_details[key] = value;
    pthread_mutex_unlock(&m_mutex);


    return;

}

/*
 * Add a detail key::value to the list.
 *
 * @param key the detail key.
 * @param value the detail value.
 */
void Details::add(const string key, const string value)
{

    //Add the key:value pair to the m_details map.
    pthread_mutex_lock(&m_mutex);
    std::pair<string, string> keyval;
    keyval.first = key;
    keyval.second = value;
    m_details.push_back(keyval);
    pthread_mutex_unlock(&m_mutex);

    return;

}

/*
 * Test if a value exists by testing the key.
 *
 * @param key the key.
 * @return true if there is a value for this key.
 */
bool Details::exists(string key)
{
    pthread_mutex_lock(&m_mutex);

    for(int i = 0; i<(int)m_details.size(); i++)
    {
        std::pair<string, string> keyval = m_details[i];
        string key2 = keyval.first;
        if(key2.compare(key) == 0) return true;
    }
    return false;

}

/*
 * Get the number of key:value pairs in the list.
 */
int Details::size()
{
    return (int)m_details.size();
}

/*
 * Get the value for a key.
 *
 * @param key the key.
 * @return the value for the key, or empty string if it
 * does not exist.
 */
string Details::getValue(string key)
{
    pthread_mutex_lock(&m_mutex);

    string value = "";

    for(int i = 0; i<(int)m_details.size(); i++)
    {
        std::pair<string, string> keyval = m_details[i];
        string key2 = keyval.first;
        if(key2.compare(key) == 0) return (string)keyval.second;
    }

    pthread_mutex_unlock(&m_mutex);

    return value;

}

/*
 * Get all values that have a key that starts with a character
 * substring.
 *
 * @param keyStart the substring to match with the keys.
 * @return a Details object filled with the key:value pairs.
 */
Details *Details::getValueFromKeyStartsWith(string keyStart)
{
    Details *retMap = NULL;

    for(int i = 0; i<(int)m_details.size(); i++)
    {
        std::pair<string, string> keyval = m_details[i];
        string key = keyval.first;
        if(key.compare((size_t)0, keyStart.size(), keyStart)  == 0)
        {
            if(retMap == NULL)
            {
                retMap = new Details();
            }
            string value = m_details[i].second;
            retMap->add(key, value);
        }
    }

    return retMap;
}

/*
 * Convert the key:value pairs into one string, keach key value
 * separated by a line ending.
 *
 * @param separator the separator to place between the key and the value.
 * @param lineEnd the character(s) to use as a line ending. Usually \r\n.
 * @param maxLineLength the maximum length of a line.
 * @return the resulting multi line string.
 */
string Details::toString(const string separator, const string lineEnd, int maxLineLength)
{
    string retString = "";
    bool first = true;

    for(int i = 0; i<(int)m_details.size(); i++)
    {
        std::pair<string, string> keyval = m_details[i];
        string key = keyval.first;
        string value = keyval.second;

        if(first == true) first = false;
        else retString += lineEnd;

        string line = key + separator + value;
        line = line.substr((size_t)0, (size_t)maxLineLength);
        retString += line;
    }

    return retString;

}

/*
 * Get a key:value pair from the list base of the index in the list.
 *
 * @param i the index into the list.
 * @return the key:value pair. Will be "null":"null" if the index
 * is invalid.
 */
std::pair<string, string> Details::get(int i)
{
    if(i >= (int)m_details.size())
    {
        std::pair<string, string> keyval = m_details[i];
        keyval.first = "null";
        keyval.second = "null";
        return keyval;
    }
    std::pair<string, string> keyval = m_details[i];
    return keyval;
}

/*
 * Get the character length of the longest key in the list.
 *
 * @return the character length of the longest key in the list.
 */
int Details::getMaxKeyLength()
{
    int len = 0;

    for(int i = 0; i<(int)m_details.size(); i++)
    {
        std::pair<string, string> keyval = m_details[i];
        string key = keyval.first;
        size_t thisSize = key.size();
        if((int)thisSize > len) len = (int)thisSize;
    }

    return len;

}
