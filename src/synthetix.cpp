#include <iostream>
#include <string>
#include <exception>

#include "argparse.h"
#include "parser.h"
#include "common.h"

int main(int argc, char **argv)
{
    argparse::ArgumentParser program("synthetix", "1.0", argparse::default_arguments::help);
    program.add_argument("--pattern")
        .required()
        .help("specifies the input pattern file.")
        .action([](const std::string &value) { return value; });
    program.add_argument("--presets")
        .required()
        .help("specifies the input presets file.")
        .action([](const std::string &value) { return value; });

    try 
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) 
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(EXIT_FAILURE);
    }

    auto pattern_file_path = program.get<std::string>("--pattern");
    auto presets_file_path = program.get<std::string>("--presets");
    
// ====================================================================

    struct parser_settings parser_settings = 
    {
        .pattern_file_path = pattern_file_path,
        .presets_settings = 
        {
            .presets_file_path = presets_file_path,
            .delimiter = ": ",
            .delimiter_length = 2
        }
    };

    // Initialize the parser
    parser parser(parser_settings);

    // Parse the file (return a Pattern object)
    auto result_parse_file = parser.try_parse_file();
    if (std::holds_alternative<error_message>(result_parse_file))
    {
        std::cerr << "Unable to parse the pattern file." << std::endl;
        std::cerr << std::get<error_message>(result_parse_file) << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Successfully parsed, proceed with pattern generation
    pattern current_pattern = std::get<pattern>(result_parse_file);
    current_pattern.generate_all_combinations();

    return EXIT_SUCCESS;
}