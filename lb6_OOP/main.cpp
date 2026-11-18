#include "Angle.h"
#include <iomanip>
#include <stdexcept>

int main(int argc, char**) {
    try {
        Angle a(30, 30), b(45, 0);
        Angle copy(a);
        std::cout << "a: "; a.Display();
        std::cout << "b: "; b.Display();
        std::cout << "a + b: "; (a + b).Display();
        std::cout << "a - b: "; (a - b).Display();
        std::cout << std::boolalpha;
        std::cout << "a == b: " << (a == b) << '\n';
        std::cout << "a == copy: " << (a == copy) << '\n';
        std::cout << "a < b: " << (a < b) << '\n';
        Angle negative = a - b;
        negative.normalize();
        std::cout << "Normalized difference: ";
        negative.Display();
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Radians: " << a.radians() << '\n';
        std::cout << "Sine: " << a.sine() << '\n';
        a.increase(Angle(5, 15));
        a.decrease(Angle(10, 45));
        std::cout << "After changes: "; a.Display();
        std::cout << "Compare: " << a.compare(b) << '\n';
        try { Angle invalid(10, 60); }
        catch (const std::invalid_argument& e) {
            std::cout << "Rejected: " << e.what() << '\n';
        }
        if (argc > 1) {
            Angle entered;
            std::cout << "Enter degrees and minutes: ";
            entered.Read();
            entered.Display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
