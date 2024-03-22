#include "pattern.h"
#include <iostream>

pattern::pattern(const std::string &name)
{
    m_metadata["name"] = name;
}

void pattern::add_empty_blocks(int count)
{
    for (int i = 0; i < count; ++i)
    {
        m_blocks.emplace_back();
    }
}

std::vector<std::reference_wrapper<block>> pattern::get_last_n_blocks(int count)
{
    if (count < 0 || count > m_blocks.size())
    {
        return {};
    }
    
    std::vector<std::reference_wrapper<block>> last_n_blocks;
    for (int i = m_blocks.size() - count; i < m_blocks.size(); ++i) 
    {
        last_n_blocks.push_back(std::ref(m_blocks[i]));
    }

    return last_n_blocks;
}

void pattern::print_blocks() const
{
    if (m_blocks.empty()) return;

    std::cout << "Blocks:" << std::endl;
    for (const auto& block : m_blocks)
    {
        std::cout << " * " << block << std::endl;
    }
}

void pattern::add_metadata(const std::string &key, const std::string &value)
{
    m_metadata[key] = value;
}

std::optional<std::string> pattern::get_metadata(const std::string &key) const 
{
    if (auto it = m_metadata.find(key); it != m_metadata.end())
    {
        return it->second;
    }

    return std::nullopt;
}

void pattern::print_metadata() const
{
    if (m_metadata.empty()) return;

    std::cout << "Metadata:" << std::endl;
    for (const auto& [key, value] : m_metadata)
    {
        std::cout << " * " << key << ": " << value << std::endl;
    }
}

void pattern::generate_all_combinations() const
{}

