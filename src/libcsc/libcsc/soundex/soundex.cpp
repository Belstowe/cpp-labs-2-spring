#include "soundex.hpp"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <unordered_map>

using libcsc::soundex::soundex_hash;

uint32_t string_to_hash(const std::string& str)
{
    return std::accumulate(str.begin(), str.begin() + 4, 0, [](uint32_t&& hash, char&& c) { return (hash << 8) + c; });
}

void delete_chars(std::string::iterator& begin, std::string::iterator& end, const std::initializer_list<char>& chars_to_delete)
{
    for (const char& char_to_delete : chars_to_delete) {
        std::remove(begin, end, char_to_delete);
    }
}

void replace_chars(std::string::iterator& begin, std::string::iterator& end, const std::initializer_list<char>& chars_to_replace, const char& char_for_replace)
{
    for (const char& char_to_replace : chars_to_replace) {
        std::replace(begin, end, char_to_replace, char_for_replace);
    }
}

void clear_adjacent_numbers(std::string::iterator& begin, std::string::iterator& end)
{
    std::unique(begin, end, [](const char& c1, const char& c2) { return (c1 == c2) && (std::isdigit(c1)); });
}

uint32_t soundex_hash(std::string_view&& str)
{
    std::string hashbase(str);
    delete_chars(std::next(hashbase.begin()), hashbase.end(), {'h', 'w'});

    const std::unordered_map<char, std::initializer_list<char>> values_to_key_map
            = {{'1', {'b', 'f', 'p', 'v'}}, {'2', {'c', 'g', 'j', 'k', 'q', 's', 'x', 'z'}}, {'3', {'d', 't'}}, {'4', {'l'}}, {'5', {'m', 'n'}}, {'6', {'r'}}};
    for (const auto& [char_for_replace, chars_to_replace] : values_to_key_map) {
        replace_chars(hashbase.begin(), hashbase.end(), chars_to_replace, char_for_replace);
    }

    clear_adjacent_numbers(hashbase.begin(), hashbase.end());

    delete_chars(std::next(hashbase.begin()), hashbase.end(), {'a', 'e', 'i', 'o', 'u', 'y'});
    hashbase.resize(4, '0');
    hashbase[0] = std::toupper(str[0]);

    return string_to_hash(hashbase);
}