#pragma once

#include <string>
#include <string_view>

namespace bilol_abdilxayev {

enum class UserType { kFirstTime, kKnown };

std::string SayHelloTo(std::string_view name, UserType type);

}  // namespace bilol_abdilxayev