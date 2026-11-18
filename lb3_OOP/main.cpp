#include "Angle.h"
#include <iomanip>
#include <stdexcept>

int main(int argc, char**) {
    try {
        Angle zero;
        Angle a(30, 30);
        Angle copy(a);
        std::cout << "Default: "; zero.Display();
        std::cout << "Parameters: "; a.Display();
        std::cout << "Copy: "; copy.Display();
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Radians: " << a.radians() << '\n';
        std::cout << "Sine: " << a.sine() << '\n';
        a.increase(Angle(5, 15));
        std::cout << "Increase: "; a.Display();
        a.decrease(Angle(10, 45));
        std::cout << "Decrease: "; a.Display();
        std::cout << "Copy unchanged: "; copy.Display();
        std::cout << "Compare: " << a.compare(copy) << '\n';
        Angle negative(-30, -30);
        negative.normalize();
        std::cout << "Normalized: "; negative.Display();
        try { a.Init(10, 60); }
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
