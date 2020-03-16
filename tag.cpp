#include "tag.h"

using namespace std;

size_t Tag::id = 0;

Tag::Tag(const std::string &name)
    : m_name(name)
{
    m_id = id;
    id++;
}

std::string Tag::getName() const
{
    return m_name;
}

void Tag::setName(const std::string &name)
{
    m_name = name;
}

bool operator<(const Tag &tag1, const Tag &tag2)
{
    return tag1.getId() < tag2.getId();
}

size_t Tag::getId() const
{
    return m_id;
}