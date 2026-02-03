/**
 * Copyright 2026 Bruce Ide
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <gtest/gtest.h>
#include <meta>
#include <string>

/**
 * Enum to string exmaple (using expansion statements) from P2996 section 3.6
 */

template<typename E, bool Enumerable = std::meta::is_enumerable_type(^^E)>
  requires std::is_enum_v<E>
constexpr std::string_view enum_to_string(E value) {
  if constexpr (Enumerable)
    template for (constexpr auto e :
                  std::define_static_array(std::meta::enumerators_of(^^E)))
      if (value == [:e:])
        return std::meta::identifier_of(e);

  return "<unnamed>";
}

// This is the empty enum version
TEST(P2996, EnumToStringEmptyEnumWithExpansions) {
  enum Color : int;
  ASSERT_EQ(enum_to_string(Color(0)), "<unnamed>");
}

TEST(P2996, EnumToStringWithExpansions) {
  enum Color : int { red, green, blue };
  ASSERT_EQ(enum_to_string(Color::red), "red");
  ASSERT_EQ(enum_to_string(Color(42)), "<unnamed>");
}
