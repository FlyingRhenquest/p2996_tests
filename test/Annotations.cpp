/*
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
#include <string_view>
#include <cstring>
#include <cstdint>

/**
 * An empty structure -- just testing to verify that we can tag and retrieve an
 * empty annotation. You might use something like this for "ignore" or some
 * other boolean-type indicator
 */

struct EmptyAnnotation {};

consteval size_t annotation_count(std::meta::info i, std::meta::info annotation) {
  return std::meta::annotations_of_with_type(i, annotation).size();
}

// Verify EmptyAnnotation is found.  Note we can't call annotations_of_with_type
// in this function because it has to be in a consteval context, and that
// count most be constexpr so the compiler knows it's being set at compile time.
// This requires structuring the code in a way that might look unusual at
// first glance.

TEST(Annotations, EmptyAnnotation) {

  [[=EmptyAnnotation{}]] int i;

  constexpr size_t count = annotation_count(^^i, ^^EmptyAnnotation);
  
  ASSERT_EQ(count, 1);
  
}

/**
 * A structure in which we put an int. We want to extract the int
 * from the structure in the annotation and use it in our code.
 */

struct IntAnnotation {
  int number;
};

// This version doesdn't seem to want to just take a std::meta::info
// as aparameter, even though annotation_count did. If we pass it as
// a template parameter, that works and the test passes.

template <std::meta::info Info>
consteval int int_annotation_value() {

  constexpr auto annotations = std::define_static_array(std::meta::annotations_of_with_type(Info, ^^IntAnnotation));
  constexpr IntAnnotation extracted = std::meta::extract<IntAnnotation>(annotations[0]);
  return extracted.number;
  
}

TEST(Annotations, IntAnnotation) {
  [[=IntAnnotation{42}]] int i;
  i = int_annotation_value<^^i>();
  ASSERT_EQ(i,42);
}

/**
 * Since IntAnnotation works above, can we do that with a const char* character literal?
 * We'll probably get warnings that ISO C++ doesn't allow that.
 */

struct CharStarAnnotation {
  char const* data;  
};

template <std::meta::info Info>
consteval char const* charstar_annotation_value() {

  constexpr auto annotations = std::define_static_array(std::meta::annotations_of_with_type(Info, ^^CharStarAnnotation));
  constexpr auto extracted{std::meta::extract<CharStarAnnotation>(annotations[0])};
  return extracted.data;
  
}

TEST(Annotations, CharStarAnnotation) {
  [[=CharStarAnnotation{std::define_static_string("Hello World!")}]] int i;

  constexpr char const* annotation{charstar_annotation_value<^^i>()};
  std::string data(annotation);
  
  ASSERT_EQ(data, "Hello World!");
}
