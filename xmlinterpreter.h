#ifndef XMLINTERPRETER_H
#define XMLINTERPRETER_H

#include <string>
#include <list>

class XMLInterpreter
{
public:
    explicit XMLInterpreter(const std::string &fileName);

    bool good();

private:
    bool readFile(const std::string &fileName);

    bool checkTagsOrder(const std::list<std::string> &tags);

    std::string m_source;
};

#endif
