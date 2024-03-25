#include "pattern.h"
#include "terminal.h"
#include <iostream>
#include <fstream>
#include <numeric>

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

void pattern::generate_all_combinations(std::ofstream& output) const
{
    if (!output.is_open() || !output.good())
    {
        std::cout << "Error: could not open output file." << std::endl;
        return;
    }
    
    std::string name = get_metadata("name").value_or("unknown");
    size_t total_combinations = std::accumulate(m_blocks.begin(), m_blocks.end(), 1, [](size_t acc, const block& block) { return acc * block.get_size(); });

    if (total_combinations == 0)
    {
        std::cout << "Error: no combinations to generate." << std::endl;
        return;
    }

    hide_cursor();

    std::vector<int> indices(m_blocks.size(), 0);
    int count = 1;
    while (true)
    {
        std::string combination;
        for (size_t i = 0; i < m_blocks.size(); ++i)
        {
            auto block_char = m_blocks[i].get_char_at(indices[i]);
            if (std::holds_alternative<error_message>(block_char))
            {
                std::cout << "Error: " << std::get<error_message>(block_char) << std::endl;
                return;
            }

            combination += std::get<char>(block_char);
        }

        std::cout << "\r" << count++ << "/" << total_combinations << std::flush;
        output << combination << std::endl;

        bool should_increment_next = true;
        for (int i = m_blocks.size() - 1; i >= 0; --i)
        {
            if (should_increment_next)
            {
                indices[i] = (indices[i] + 1) % m_blocks[i].get_size();
                should_increment_next = indices[i] == 0;
            }
        }

        if (should_increment_next)
        {
            break;
        }
    }

    show_cursor();
    std::cout << "Done! Output saved to " << name << "-output.txt" << std::endl;

    output.close();
}