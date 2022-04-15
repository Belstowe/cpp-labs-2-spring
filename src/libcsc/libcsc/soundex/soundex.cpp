#include "soundex.hpp"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <stdexcept>
#include <unordered_map>

namespace libcsc::soundex {
uint32_t string_to_hash(const std::string& str)
{
    return std::accumulate(str.rbegin(), str.rend(), 0, [](uint32_t hash, const char c) { return (hash << 8) + c; });
}

std::string hash_to_string(const uint32_t hash)
{
    return std::string(reinterpret_cast<const char*>(&hash), 4);
}

void delete_chars(
        std::string& str,
        const std::string::iterator& begin,
        const std::string::iterator& end,
        const std::initializer_list<char>& chars_to_delete)
{
    auto new_end = std::remove_if(begin, end, [chars_to_delete](const char c) {
        return (std::find(chars_to_delete.begin(), chars_to_delete.end(), c) != chars_to_delete.end());
    });
    str.erase(new_end, end);
}

void replace_chars(
        const std::string::iterator& begin,
        const std::string::iterator& end,
        const std::initializer_list<char>& chars_to_replace,
        const char char_for_replace)
{
    std::replace_if(
            begin,
            end,
            [chars_to_replace](const char c) {
                return (std::find(chars_to_replace.begin(), chars_to_replace.end(), c) != chars_to_replace.end());
            },
            char_for_replace);
}

void clear_adjacent_numbers(std::string& str, const std::string::iterator& begin, const std::string::iterator& end)
{
    auto new_end
            = std::unique(begin, end, [](const char c1, const char c2) { return (c1 == c2) && (std::isdigit(c1)); });
    str.erase(new_end, end);
}

uint32_t soundex_hash(const std::string_view str)
{
    if (str.empty()) {
        throw std::runtime_error("Empty string given to soundex_hash");
    }

    if (!std::all_of(str.cbegin(), str.cend(), [](const char c) {
            return isdigit(static_cast<int>(c)) || isalpha(static_cast<int>(c));
        })) {
        throw std::runtime_error(
                std::string() + "String '" + str.data()
                + "' includes a character which is neither a letter nor a digit");
    }

    std::string hashbase(str);
    std::transform(hashbase.begin(), hashbase.end(), hashbase.begin(), [](const char c) -> char {
        return static_cast<char>(std::tolower(c));
    });

    delete_chars(hashbase, std::next(hashbase.begin()), hashbase.end(), {'h', 'w'});

    const std::unordered_map<char, std::initializer_list<char>> values_to_key_map
            = {{'1', {'b', 'f', 'p', 'v'}},
               {'2', {'c', 'g', 'j', 'k', 'q', 's', 'x', 'z'}},
               {'3', {'d', 't'}},
               {'4', {'l'}},
               {'5', {'m', 'n'}},
               {'6', {'r'}}};
    for (const auto& [char_for_replace, chars_to_replace] : values_to_key_map) {
        replace_chars(hashbase.begin(), hashbase.end(), chars_to_replace, char_for_replace);
    }

    clear_adjacent_numbers(hashbase, hashbase.begin(), hashbase.end());

    delete_chars(hashbase, std::next(hashbase.begin()), hashbase.end(), {'a', 'e', 'i', 'o', 'u', 'y'});
    hashbase.resize(4, '0');
    hashbase[0] = static_cast<char>(std::toupper(str[0]));

    return string_to_hash(hashbase);
}
}