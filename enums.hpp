/**
*** This is a set of tools for enum class objects.
*** Provides advancing and converting enums to/from their underlying types.
**/

#pragma once

/// STL
#include <iostream>
#include <type_traits>
#include <cmath>

template <typename E, E first, E head>
void advanceEnum(E& v)
{
  if(v == head)
    v = first;
}

template <typename E, E first, E head, E next, E... tail>
void advanceEnum(E& v)
{
  if(v == head)
    v = next;
  else
    advanceEnum<E, first, next, tail...>(v);
}

template <typename E, E first, E... values>
struct EnumValues
{
  static void advance(E& v)
  {
    advanceEnum<E, first, first, values...>(v);
  }
};

template <typename E>
constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type
{
  return static_cast<typename std::underlying_type<E>::type>(e);
}

template <typename E>
inline E from_underlying(std::istream& in)
{
  static constexpr uint64_t maximum_value = std::pow(2, sizeof(E) * 8) - 1;

  uint32_t tmp;
  in >> tmp;

  return (tmp <= maximum_value ? static_cast<E>(tmp) : E());
}
