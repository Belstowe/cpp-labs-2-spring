#pragma once

#include <cinttypes>
#include <string_view>

namespace libcsc::soundex {
uint32_t string_to_hash(const std::string& str);
std::string hash_to_string(const uint32_t& hash);
uint32_t soundex_hash(const std::string_view& str);
}