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

#include <meta>
#include <iostream>

struct NumAnnotation {
  int number;
};

// Due to compile time requirements, I need to pass the info as a
// template object, and this function needs to be constexpr
template <std::meta::info Info>
consteval int num_annotation_value() {
  constexpr auto annotations = std::define_static_array(std::meta::annotations_of_with_type(Info, ^^NumAnnotation));
  constexpr NumAnnotation extracted = std::meta::extract<NumAnnotation>(annotations[0]);
  return extracted.number;
}

void IntTest1() {
  [[=NumAnnotation{42}]] int i{0};
  i = num_annotation_value<^^i>();
  std::cout << "IntTest1: i == " << i << std::endl;
}

/* */
// Same setup as the int one. String and string view do not work well with
// consteval, [P3394](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p3394r2.html)
// uses char const* data in its section 3.3 serialization example
struct StringAnnotation {
  char const* data;
};

// Exactly copying the consteval function above and changing the type
template <std::meta::info Info>
consteval char const* string_annotation_value() {
  constexpr auto annotations = std::define_static_array(std::meta::annotations_of_with_type(Info, ^^StringAnnotation));
  constexpr StringAnnotation extracted = std::meta::extract<StringAnnotation>(annotations[0]);
  return extracted.data;
}

void StringTest2() {
  [[=StringAnnotation(std::define_static_string("Hello, world!"))]] int i{0};
  char const* data = string_annotation_value<^^i>();
  std::cout << "String annotation: \"" << data << "\"" << " i == " << i << std::endl;
}

/* */

int main(int argc, char *argv[]) {
  IntTest1();
  /* */
  StringTest2();
  /* */
}
