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
 * Verify reflection can reflect the private members of a class. Note that this does
 * not imply that you can access those members -- normal friendship rules apply.
 * It'd be nice if they set it up so you could just friend class an access context in
 * std::meta in order for reflection to actually access those members. If you're
 * generating code for another class or function to access those members, I think
 * the usual friend statements in your class will work.
 */

TEST(P2996, PrivateMemberReflection) {

  class TestClass {
    int foo;
    int bar;
  public:
    int baz;
    int quux;
  };
  
  constexpr static auto ctx = std::meta::access_context::unchecked();
  static constexpr size_t memberCount = std::meta::nonstatic_data_members_of(^^TestClass, ctx).size();
  ASSERT_EQ(memberCount, 4);
}
