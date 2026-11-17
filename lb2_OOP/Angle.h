#pragma once

#include <string>

class Angle {
    long long degrees_ = 0;
    int minutes_ = 0;
    long long total() const;
    void assignTotal(long long value);
public:
    void Init(long long degrees, int minutes);
    void Read();
    std::string toString() const;
    void Display() const;
    double radians() const;
    double sine() const;
    void normalize();
    void increase(const Angle& other);
    void decrease(const Angle& other);
    int compare(const Angle& other) const;
};
