#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "libcsc/libcsc/soundex/soundex.hpp"
#include "nlohmann/json.hpp"
#include "rapidcsv.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using libcsc::soundex::hash_to_string;
using libcsc::soundex::soundex_hash;
using libcsc::soundex::string_to_hash;

namespace {
class soundex_map : public std::map<uint32_t, std::vector<std::string_view>>
{
public:
    std::vector<std::string_view>& operator[](const std::string& key) {
        return std::map<uint32_t, std::vector<std::string_view>>::operator[](soundex_hash(key));
    }

    void insert(const std::string& key) {
        this->operator[](key).push_back(key);
    }
};

void to_json(nlohmann::json& j, const soundex_map& map) {
    for (const auto& [hash, name] : map) {
        j[hash_to_string(hash)] = name;
    }
}
} // namespace


int main(int argc, char* argv[])
{
    CLI::App app("Soundex Groupby Utility");

    std::string input_file;
    std::string output_file;

    std::ofstream output_file_stream;

    CLI::Option* opt_i = app.add_option<std::string>("-i,--input", input_file, "Input CSV File");
    opt_i->required();

    CLI::Option* opt_o = app.add_option<std::string>("-o,--output", output_file, "Output JSON File");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    std::ostream* output_stream = &std::cout;
    if (*opt_o) {
        output_file_stream.open(output_file, std::ofstream::out);
        output_stream = &output_file_stream;
    }

    rapidcsv::Document doc(input_file, rapidcsv::LabelParams(-1, -1));

    std::vector<std::string> names = doc.GetColumn<std::string>(0);

    soundex_map hash_map;

    try {
        std::for_each(names.begin(), names.end(), [&hash_map](const std::string& name) {
            hash_map.insert(name);
        });
    } catch (const std::runtime_error& e) {
        std::clog << e.what();
    }

    for (auto& [key, name_list] : hash_map) {
        std::sort(name_list.begin(), name_list.end());
    }

    nlohmann::json j(hash_map);

    (*output_stream) << j.dump(4) << std::endl;

    return 0;
}