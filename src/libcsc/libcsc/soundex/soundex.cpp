#include "soundex.hpp"

#include <algorithm>
#include <cctype>
#include <numeric>

using libcsc::soundex::soundex_hash;

uint32_t string_to_hash(const std::string& str)
{
    return std::accumulate(str.begin(), str.begin() + 4, 0, [](uint32_t&& hash, char&& c) {
        return (hash << 8) + c;
    });
}

void delete_char(std::string& str)
{

}

uint32_t soundex_hash(std::string_view&& str)
{
    std::string hashbase(str);
    hashbase.resize(4, '0');
    hashbase[0] = std::toupper(str[0]);
    return string_to_hash(hashbase);
}