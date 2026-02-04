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

/**
 * Tests suggested by Reddit's /u/_bstaletic
 */

void f(){}

struct s {
    int get_z(this s) { return 4; }
    static int get_y() { return 4; }
    int get_x() { return 3; }
    auto operator-(this s self, int) { return self; }
    static auto operator()(int) { return 21; }
    auto operator+(int) { return *this; }
    int xx;
    static int xxx;
};

int s::xxx;

/**
 * See if we can get addresses of various things
 *
 * Suggested test was templatized, to fit it into gtest I think
 * I can just use a "using"
 *
 * This ICEs in gcc16 currently so pass cmake -DBUILD_REF_MEMBERS
 * if you want to try to build it.
 */

#ifdef BUILD_REF_MEMBERS

TEST(P2996, RefMembers) {
  constexpr auto ctx = std::meta::access_context::current();
  using T = s;
  
  constexpr auto get_z = members_of(^^T, ctx)[0];
  constexpr auto get_y = members_of(^^T, ctx)[1];
  constexpr auto get_x = members_of(^^T, ctx)[2];
  constexpr auto op_minus = members_of(^^T, ctx)[3];
  constexpr auto op_call = members_of(^^T, ctx)[4];
  constexpr auto op_plus = members_of(^^T, ctx)[5];
  constexpr auto xx = members_of(^^T, ctx)[6];
  constexpr auto xxx = members_of(^^T, ctx)[7];
  ASSERT_NE(nullptr, &[:get_x:]);
  ASSERT_NE(nullptr, &[:get_y:]); // ICEs on this line currently
  ASSERT_NE(nullptr, &[:get_z:]);
  ASSERT_NE(nullptr, &[:op_minus:]);
  ASSERT_NE(nullptr, &[:op_call:]);
  ASSERT_NE(nullptr, &[:op_plus:]);
  ASSERT_NE(nullptr, &[:xx:]);
  ASSERT_NE(nullptr, &[:xxx:]);
}

#endif

/**
 * This looks like it's getting a copy of an object and getting
 * a pointer to one of its methods passed via template
 */

template<auto getter>
void RefTemplateGetter(s obj) {
  ASSERT_NE(nullptr, &[:getter:]);
}

TEST(P2996, RefTemplateGetterTests) {
  // This doesn't work due to multiple template earguments
  // RefTemplateGetter<^^s::get_x, ^^s::operator+>(s{});
  // This works (with s::xxx defined outside the struct.
  RefTemplateGetter<^^s::xxx>(s{});
  // This doesn't work due to multiple template arguments
  // RefTemplateGetter<^^s::get_z, ^^s::operator- >(s{});
}

/**
 * Get a ref to a getter with an explicit std::meta::info template
 */

template<std::meta::info getter>
void RefTemplateGetterExplicit() {
  ASSERT_NE(nullptr, &[:getter:]);
}

TEST(P2996, RefTemplateGetterExplicitTest) {
  RefTemplateGetterExplicit<^^f>();
}
