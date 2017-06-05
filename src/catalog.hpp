/***
 * Data structure that holds the flash cards
 */

#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace flash {

using spair = std::pair<std::string, std::string>;
using catalog = std::vector<spair>;

// Parse a catalog from a stream
template <typename S>
catalog parse_catalog(S & stream) {
  catalog result;
  std::string key;
  std::string value;
  std::string temp;
  
  int lineno = 0;

  while (stream) {
    std::getline(stream, key);
    ++lineno;

    if (!key.size()) { std::cerr << "Empty key at line " << lineno << std::endl; }

    std::getline(stream, value);
    ++lineno;

    if (!value.size()) { std::cerr << "Empty value at line " << lineno << std::endl; }

    result.emplace_back(std::move(key), std::move(value));
    
    if (stream) {

      std::getline(stream, temp);
      ++lineno;

      if (temp.size()) { std::cerr << "Expected empty line at line " << lineno << std::endl; }
    }
  }

  return result;
}

} // end namespace flash
