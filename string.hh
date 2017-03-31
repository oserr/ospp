/**
 * @file string.hh
 * @author Omar A Serrano
 * @date 2017-03-28
 */

#pragma once

#include <algorithm>
#include <bitset>
#include <limits>
#include <string>
#include <unordered_map>

namespace ospp {

template<typename TChar>
bool
hasUniqueCharacters(const std::basic_string<TChar> &value)
{
  std::bitset<std::numeric_limits<TChar>::max()> charSet;
  for (auto c : value) {
    if (charSet.test(value))
      return false;
    charSet.set(value);
  }
  return true;
}

template<typename TChar>
bool
arePermutations(
  const std::basic_string<TChar> &lhs,
  const std::basic_string<TChar> &rhs)
{
  if (lhs.size() != rhs.size())
    return false;

  std::unordered_map<TChar, int> charMap;
  for (auto c : lhs)
    ++charMap[c];

  for (auto c : rhs) {
    auto val = --charMap[c];
    if (val < 0)
      return false;
  }

  for (auto values : charMap) {
    if (values.second)
      return false;
  }

  return true;
}

void
encodeSpaces(std::string &value)
{
  constexpr auto space = ' ';
  auto numSpaces = std::count(value.cbegin(), value.cend(), space);
  if (not numSpaces)
    return;
  auto sizeAdjust = numSpaces*2 + 1;
  value.resize(value.size() + sizeAdjust);
  auto from = value.end()-1;
  auto to = from + sizeAdjust;
  *to-- = '\0';
  while (to != from) {
    if (*from != space)
      *to-- = *from;
    else {
      *to-- = '0';
      *to-- = '2';
      *to-- = '%';
    }
    --from;
  }
}

} // namespace ospp
