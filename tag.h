#ifndef TAG_H
#define TAG_H

#include <string>

class Tag
{
public:
    Tag() = default;

    explicit Tag(const std::string &name);

    std::string getName() const;

    void setName(const std::string &name);

    size_t getId() const;

    friend bool operator<(const Tag &tag1, const Tag &tag2);

private:
    std::string m_name;

    static size_t id;

    size_t m_id;
};

#endif