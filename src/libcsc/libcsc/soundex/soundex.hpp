#pragma once

#include <cinttypes>
#include <string_view>

namespace libcsc::soundex {
    uint32_t soundex_hash(std::string_view&& str);
}