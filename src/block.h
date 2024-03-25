#ifndef BLOCK_H
#define BLOCK_H

#include "common.h"

#include <iostream>
#include <vector>
#include <variant>

class block
{
public:
    void add_char(char c);
    void add_chars(const std::string& chars);

    void remove_char(char c);
    void remove_chars(const std::string& chars);

    std::variant<char, error_message> get_char_at(size_t index) const;
    size_t get_size() const;

    friend std::ostream& operator<<(std::ostream& os, const block& block);

private:
    std::vector<char> m_chars;
};

#endif