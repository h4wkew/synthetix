#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>

class block
{
public:
    block();
    
    void add_char(char c);
    void add_chars(const std::string& chars);

    friend std::ostream& operator<<(std::ostream& os, const block& block);

private:
    std::vector<char> m_chars;
    bool m_is_optional;
};

#endif