#include "block.h"

#include <algorithm>

block::block()
    : m_is_optional(false)
{}

void block::add_char(char c)
{
    if (std::find(std::cbegin(m_chars), std::cend(m_chars), c) == std::cend(m_chars))
    {
        m_chars.push_back(c);
        return;
    }

    std::cout << "Warning: character '" << c << "' is already in the block\n" << std::endl;
}

void block::add_chars(const std::string& chars)
{
    for (const auto& c : chars)
    {
        add_char(c);
    }
}

size_t block::get_size() const
{
    return m_chars.size();
}

std::variant<char, error_message> block::get_char_at(size_t index) const
{
    if (index >= m_chars.size())
    {
        return error_message("Index out of bounds");
    }

    return m_chars[index];
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