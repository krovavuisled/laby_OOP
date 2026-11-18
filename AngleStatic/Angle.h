#pragma once
#include <iostream>
#include <string>


class  Angle {
    int degrees_ = 0;
    int minutes_ = 0;
    long long total() const;
    static Angle fromMinutes(long long value);
public:
    Angle();
    Angle(int degrees, int minutes);
    Angle(const Angle& other);
    ~Angle();
    void Init(int degrees, int minutes);
    void Read();
    void Display() const;
    std::string toString() const;
    double radians() const;
    double sine() const;
    void normalize();
    void increase(const Angle& value);
    void decrease(const Angle& value);
    int compare(const Angle& other) const;
};
