#include "Angle.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) {
    try {
        Angle a, b;
        if (argc > 1 && std::string(argv[1]) == "--demo") {
            a.Init(30, 30);
            b.Init(45, 0);
        } else {
            a.Read();
            b.Read();
        }
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "a = "; a.Display();
        std::cout << "b = "; b.Display();
        std::cout << "radians(a) = " << a.radians() << '\n';
        std::cout << "sin(a) = " << a.sine() << '\n';
        std::cout << "compare(a,b) = " << a.compare(b) << '\n';
        a.increase(b);
        std::cout << "a + b = "; a.Display();
        a.decrease(b);
        std::cout << "restored a = "; a.Display();
        a.Init(-30, -30);
        a.normalize();
        std::cout << "normalized -30 deg 30 min = "; a.Display();
        try { a.Init(10, 60); }
        catch (const std::exception& e) {
            std::cout << "Invalid input: " << e.what() << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
