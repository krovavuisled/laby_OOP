#include <array>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Triad {
protected:
    double a_, b_, c_;
    static void finite(double a, double b, double c) {
        if (!std::isfinite(a) || !std::isfinite(b) ||
            !std::isfinite(c)) throw std::invalid_argument("nonfinite field");
    }
public:
    Triad(double a=0, double b=0, double c=0) {
        finite(a,b,c); a_=a; b_=b; c_=c;
    }
    virtual ~Triad() = default;
    virtual void set(double a, double b, double c) {
        finite(a,b,c); a_=a; b_=b; c_=c;
    }
    void setFirst(double a) { set(a,b_,c_); }
    void setSecond(double b) { set(a_,b,c_); }
    void setThird(double c) { set(a_,b_,c); }
    double first() const { return a_; }
    double second() const { return b_; }
    double third() const { return c_; }
    double sum() const { return a_+b_+c_; }
    virtual void display() const {
        std::cout << '(' << a_ << ',' << b_ << ',' << c_ << ')';
    }
};

class Triangle : public Triad {
public:
    Triangle(double a, double b, double c) : Triad() { set(a,b,c); }
    void set(double a, double b, double c) override {
        finite(a,b,c);
        if (a<=0 || b<=0 || c<=0 ||
            a+b<=c || a+c<=b || b+c<=a)
            throw std::invalid_argument("invalid triangle sides");
        Triad::set(a,b,c);
    }
    double area() const {
        double p=sum()/2;
        return std::sqrt(p*(p-a_)*(p-b_)*(p-c_));
    }
    std::array<double,3> angles() const {
        auto angle=[](double x,double y,double z) {
            double cosine=(y*y+z*z-x*x)/(2*y*z);
            cosine=std::max(-1.0,std::min(1.0,cosine));
            return std::acos(cosine)*180/std::acos(-1.0);
        };
        return {{angle(a_,b_,c_),angle(b_,a_,c_),angle(c_,a_,b_)}};
    }
    void display() const override {
        std::cout << "Triangle "; Triad::display();
    }
};

// Receives and returns a base-class object by value (intentional slicing).
Triad shifted(Triad value, double delta) {
    value.set(value.first()+delta,value.second()+delta,
              value.third()+delta);
    return value;
}

// A derived object can be substituted for a base reference.
void showSum(const Triad& value) {
    value.display(); std::cout << ": sum=" << value.sum() << '\n';
}

int main() {
    std::cout << std::fixed << std::setprecision(3);
    Triad numbers(1,2,3);
    Triangle triangle(3,4,5);
    showSum(numbers); showSum(triangle);
    auto angles=triangle.angles();
    std::cout << "area=" << triangle.area() << "\nangles="
              << angles[0] << ',' << angles[1] << ',' << angles[2] << '\n';
    Triad changed=shifted(triangle,1);
    showSum(changed);
    Triad& base=triangle;
    base.setFirst(4); // virtual set preserves the triangle invariant
    showSum(base);
    try { base.setThird(20); }
    catch (const std::invalid_argument& e) {
        std::cout << "error: " << e.what() << '\n';
    }
    showSum(triangle); // unchanged after rejected operation
}
