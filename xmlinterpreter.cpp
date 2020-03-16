#include "xmlinterpreter.h"
#include <regex>
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

XMLInterpreter::XMLInterpreter(const string &fileName)
{
    if (!readFile(fileName))
        throw string("Could not read a file!");

    isGood = validate();

    if (isGood)
        buildData();

    for (const auto &entry : m_data)
    {
        cout << entry.first.getName() << ": " << entry.second << endl;
    }
}

bool XMLInterpreter::readFile(const string &fileName)
{
    ifstream stream(fileName);

    if (!stream.good())
        return false;

    string line;

    while (getline(stream, line))
        m_source += line;

    stream.close();
    return true;
}

bool XMLInterpreter::good()
{
    return isGood;
}

bool XMLInterpreter::checkTagsOrder(const std::list<std::string> &tags)
{
    list<string> openTags;

    for (const auto &tag : tags)
    {
        // We have an enclosing tag
        if (tag[1] != '/')
            openTags.emplace_back(tag);
        else
        {
            // Enclosing tag - let's check if the last opened one matches with it
            string copy = tag;
            // Remove the slash and simply compare them
            copy.erase(copy.begin() + 1);

            if (openTags.back() == copy)
                openTags.pop_back();
            else
                return false;
        }
    }

    return openTags.empty();
}

void XMLInterpreter::buildData()
{
    if (!m_source.empty())
    {
        m_data.clear();
        regex reg("(<\/?[A-Za-z1-9]+>)");
        string source = m_source;
        list<string> tags;
        smatch match;

        while (regex_search(source, match, reg))
        {
            string tag = match.str(0);

            // We have an enclosing tag - time to add new tag to the map
            if (tag[1] == '/')
            {
                string data = match.prefix().str();
                Tag temp(buildKey(tags));
                m_data[temp] = match.prefix().str();
                tags.pop_back();
            }
            else
                // Build new tag
                tags.emplace_back(tag);

            source = match.suffix().str();
        }
    }
}

bool XMLInterpreter::validate()
{
    regex reg("(<\/?[A-Za-z1-9]+>)");
    string source = m_source;
    smatch match;
    list<string> tags;

    while (regex_search(source, match, reg))
    {
        tags.emplace_back(match.str(0));
        source = match.suffix().str();
    }

    if (tags.size() % 2 != 0 || tags.empty())
        return false;

    return checkTagsOrder(tags);
}

std::string XMLInterpreter::buildKey(const std::list<std::string> &tags)
{
    string key;

    for (const auto &tag : tags)
        key += tag;

    return key;
}