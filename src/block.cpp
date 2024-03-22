#include "block.h"

block::block()
    : m_is_optional(false)
{}

void block::add_char(char c)
{
    m_chars.push_back(c);
}

void block::add_chars(const std::string& chars)
{
    for (const auto& c : chars)
    {
        m_chars.push_back(c);
    }
}

std::ostream& operator<<(std::ostream& os, const block& block)
{
    if (block.m_chars.empty())
    {
        os <<  "empty";
    }
    else
    {
        for (const auto& c : block.m_chars)
        {
            os << c;
        }
    }

    return os;
}