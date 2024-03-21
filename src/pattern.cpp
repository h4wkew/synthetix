#include "pattern.h"
#include <iostream>

pattern::pattern(const std::string &name)
{
    m_metadata["name"] = name;
}

void pattern::add_metadata(const std::string &key, const std::string &value)
{
    m_metadata[key] = value;
}

void pattern::add_block()
{
}

void pattern::generate_all_combinations() const
{
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
