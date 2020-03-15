#include "xmlinterpreter.h"
#include <regex>
#include <fstream>

using namespace std;

XMLInterpreter::XMLInterpreter(const string &fileName)
{
    if (!readFile(fileName))
        throw string("Could not read a file!");
}

bool XMLInterpreter::readFile(const string &fileName)
{
    ifstream stream(fileName);

    if (!stream.good())
        return false;

    string line;

    while (getline(stream, line))
        m_source += line;

    return true;
}

bool XMLInterpreter::good()
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

bool XMLInterpreter::checkTagsOrder(const std::list<std::string> &tags)
{
    list<string> openTags;

    for (const auto &tag : tags)
    {
        if (tag[1] != '/')
            openTags.emplace_back(tag);
        else
        {
            // Closing tag - let's check if the last opened one matches with it
            string copy = tag;
            // Remove the slash and simply compare them
            copy.erase(copy.begin() + 1);

            if (openTags.back() == copy)
                openTags.pop_back();
            else
                return false;
        }
    }

    return true;
}