#ifndef XMLINTERPRETER_H
#define XMLINTERPRETER_H

#include <string>
#include <list>
#include <map>
#include "tag.h"

class XMLInterpreter
{
public:
    explicit XMLInterpreter(const std::string &fileName);

    bool good();

private:
    bool readFile(const std::string &fileName);

    bool checkTagsOrder(const std::list<std::string> &tags);

    bool validate();

    void buildData();

    std::string buildKey(const std::list<std::string> &tags);

    std::string m_source;

    std::map<Tag, std::string> m_data;

    bool isGood;
};

#endif
