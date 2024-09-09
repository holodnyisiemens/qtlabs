#include "primelist_library.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

int main(int argc, char * argv[]) {
    try {
        if(argc < 3) {
            throw std::length_error("Missing parameters");
        }
        std::istringstream astr(argv[1]), bstr(argv[2]);
        int a, b;
        astr >> a;
        bstr >> b;
        if(astr.fail() || !astr.eof()) {
            throw std::invalid_argument("A must be an integer");
        }
        if(bstr.fail() || !bstr.eof()) {
            throw std::invalid_argument("B must be an integer");
        }
        if(a <= 0) {
            throw std::out_of_range("A must be positive");
        }
        if(b <= 0) {
            throw std::out_of_range("B must be positive");
        }
        if(b <= a) {
            throw std::domain_error("A must be less than B");
        }
        auto r = primelist(a, b);
        for(auto n : r) {
            std::cout << n << std::endl;
        }
    } catch(std::exception const & e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
