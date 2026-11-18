#pragma once
#include <iostream>
#include <string>

#if defined(_WIN32)
# if defined(ANGLE_EXPORTS)
#  define ANGLE_API __declspec(dllexport)
# else
#  define ANGLE_API __declspec(dllimport)
# endif
#else
# define ANGLE_API
#endif
class ANGLE_API Angle {
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
    Angle operator+(const Angle& other) const;
    Angle operator-(const Angle& other) const;
    bool operator==(const Angle& other) const;
    bool operator<(const Angle& other) const;
};
