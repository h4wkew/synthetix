#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class block
{
public:
    block();

private:
    std::vector<char> m_chars;
    bool m_is_optional;
};

#endif