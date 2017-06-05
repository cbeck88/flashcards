#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "catalog.hpp"

namespace flash {

struct controller {
  catalog cards;
  std::mt19937 rng;

  static void prompt_impl(const std::string & query, const std::string & answer) {
    std::cout << '"' << query << "\":" << std::endl;
    std::string result;
    std::getline(std::cin, result);

    std::cout << answer << std::endl << std::endl;
  }

  static void prompt_forward(const spair & card) {
    prompt_impl(card.first, card.second);
  }
  
  static void prompt_backward(const spair & card) {
    prompt_impl(card.second, card.first);
  }

  std::vector<int> get_cards_permutation() {
    std::vector<int> result(cards.size());
    for (unsigned int i = 0; i < result.size(); ++i) {
      result[i] = i;
    }

    std::shuffle(result.begin(), result.end(), rng);
    
    return result;
  }

  template <typename V>
  void for_each_card(V && v) {
    std::vector<int> perm{ this->get_cards_permutation() };
    
    for (int idx : perm) {
      v(cards[idx]);
    }
  } 

  // Main interface

  void do_each_forward() {
    this->for_each_card(controller::prompt_forward);
  }

  void do_each_backward() {
    this->for_each_card(controller::prompt_backward);
  }

  // ctor

  controller(catalog && cat)
    : cards(std::move(cat))
    , rng()
  {
    std::random_device rdev;
    rng = std::mt19937(rdev());
  }
};

} // end namespace flash



int main(int argc, char * argv[]) {
  if (argc != 2) { std::cerr << "Expected: [catalog file]\n"; return 1; }
  
  std::string fname{argv[1]};
  std::ifstream ifs{fname};
  if (!ifs) { std::cerr << "Could not read file: " << fname << std::endl; return 1; }
  
  flash::catalog cat{ flash::parse_catalog(ifs) };

  std::cout << "Read: " << cat.size() << " flash cards." << std::endl;
  if (!cat.size()) { return 0; }
  else {
    std::cout << std::endl;
    for (const auto & card : cat) {
      std::cout << card.first << " -- " << card.second << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }



  // Load cards into the controller

  flash::controller ctrl{std::move(cat)};


  // Main loop

  int option = 0;

  do {
    std::cout << "\nOptions:\n"
              << "[1] Read flash cards forwards\n"
              << "[2] Read flash cards backwards\n"
              << "[0] Exit\n"
              << std::endl;


    option = 0;
    if (std::cin >> option) {
      std::string temp;
      std::getline(std::cin, temp);

      switch (option) {
        case 1:
          ctrl.do_each_forward();
          break;
        case 2:
          ctrl.do_each_backward();
          break;
        default:
          option = 0;
          break;
      }
    }

  } while(option);
  
  std::cout << "Goodbye!" << std::endl;
}
