#include "Product.h"

#include <cmath>
#include <iostream>
#include <limits>

bool Product::Init(int kcal, double kg) {
    if (kcal <= 0 || !std::isfinite(kg) || kg <= 0)
        return false;
    if (kg > std::numeric_limits<double>::max() / (10.0 * kcal))
        return false;
    first = kcal;
    second = kg;
    return true;
}

bool Product::Read() {
    int kcal;
    double kg;
    std::cout << "Enter kcal per 100 g and mass in kg: ";
    return bool(std::cin >> kcal >> kg) && Init(kcal, kg);
}

double Product::power() const {
    return (10.0 * first) * second;
}

void Product::Display() const {
    std::cout << first << " kcal/100g; " << second << " kg\n"
              << "Total: " << power() << " kcal\n";
}
