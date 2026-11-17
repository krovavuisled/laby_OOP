#include "Product.h"

#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    Product p;
    std::cout << std::fixed << std::setprecision(2);
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        p.Init(250, 0.3);
        p.Display();
        p.Init(100, 1.0);
        p.Display();
        std::cout << std::boolalpha;
        std::cout << "Init(0, 1): " << p.Init(0, 1) << '\n';
        std::cout << "Init(100, -1): " << p.Init(100, -1) << '\n';
        std::cout << "State after invalid input: ";
        p.Display();
        return 0;
    }
    if (!p.Read()) {
        std::cerr << "Error: positive finite values required.\n";
        return 1;
    }
    p.Display();
}
