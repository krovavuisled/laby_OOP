#include "Angle.h"
#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>

long long Angle::total() const {
    return 60LL * degrees_ + minutes_;
}
Angle Angle::fromMinutes(long long value) {
    long long d = value / 60;
    if (d < std::numeric_limits<int>::min() ||
        d > std::numeric_limits<int>::max())
        throw std::overflow_error("Angle is out of range");
    Angle result;
    result.degrees_ = static_cast<int>(d);
    result.minutes_ = static_cast<int>(value % 60);
    return result;
}
Angle::Angle() = default;
Angle::Angle(int d, int m) { Init(d, m); }
Angle::Angle(const Angle& a)
    : degrees_(a.degrees_), minutes_(a.minutes_) {}
Angle::~Angle() = default;
void Angle::Init(int d, int m) {
    if (m < -59 || m > 59)
        throw std::invalid_argument("Minutes must be -59..59");
    long long value = 60LL * d + m;
    degrees_ = static_cast<int>(value / 60);
    minutes_ = static_cast<int>(value % 60);
}
void Angle::Read() {
    int d, m;
    if (!(std::cin >> d >> m))
        throw std::invalid_argument("Expected two integers");
    Init(d, m);
}
std::string Angle::toString() const {
    long long value = total();
    long long magnitude = value < 0 ? -value : value;
    std::ostringstream out;
    if (value < 0) out << '-';
    out << magnitude / 60 << " deg "
        << magnitude % 60 << " min";
    return out.str();
}
void Angle::Display() const {
    std::cout << toString() << '\n';
}
double Angle::radians() const {
    const double pi = std::acos(-1.0);
    return static_cast<double>(total()) * pi / 10800.0;
}
double Angle::sine() const { return std::sin(radians()); }
void Angle::normalize() {
    long long value = total() % 21600;
    if (value < 0) value += 21600;
    *this = fromMinutes(value);
}
void Angle::increase(const Angle& a) {
    *this = fromMinutes(total() + a.total());
}
void Angle::decrease(const Angle& a) {
    *this = fromMinutes(total() - a.total());
}
int Angle::compare(const Angle& a) const {
    return (total() > a.total()) - (total() < a.total());
}
