#include "Angle.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

long long Angle::total() const {
    return degrees_ * 60 + minutes_;
}

void Angle::assignTotal(long long value) {
    if (value < -60000000 || value > 60000000)
        throw std::out_of_range("Angle is too large");
    degrees_ = value / 60;
    minutes_ = static_cast<int>(value % 60);
}

void Angle::Init(long long degrees, int minutes) {
    if (degrees < -1000000 || degrees > 1000000
        || minutes < -59 || minutes > 59)
        throw std::invalid_argument("Invalid degrees or minutes");
    assignTotal(60 * degrees + minutes);
}

void Angle::Read() {
    long long d;
    int m;
    std::cout << "Enter signed degrees and minutes: ";
    if (!(std::cin >> d >> m))
        throw std::invalid_argument("Input is not numeric");
    Init(d, m);
}

std::string Angle::toString() const {
    const long long t = total();
    const long long a = std::llabs(t);
    std::ostringstream out;
    if (t < 0) out << '-';
    out << a / 60 << " deg " << a % 60 << " min";
    return out.str();
}

void Angle::Display() const { std::cout << toString() << '\n'; }

double Angle::radians() const {
    return total() / 60.0 * std::acos(-1.0) / 180.0;
}

double Angle::sine() const { return std::sin(radians()); }

void Angle::normalize() {
    assignTotal((total() % 21600 + 21600) % 21600);
}

void Angle::increase(const Angle& other) {
    assignTotal(total() + other.total());
}

void Angle::decrease(const Angle& other) {
    assignTotal(total() - other.total());
}

int Angle::compare(const Angle& other) const {
    return (total() > other.total()) - (total() < other.total());
}
