#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

struct Point { double x,y; };
struct MedianFeet {};
double distance(Point p, Point q) {
    return std::hypot(p.x-q.x,p.y-q.y);
}

class Triangle {
protected:
    static void validate(const std::array<double,3>& s) {
        for (double x:s)
            if (!std::isfinite(x) || x<=0)
                throw std::invalid_argument("positive finite side required");
        if (s[0]+s[1]<=s[2] || s[0]+s[2]<=s[1] || s[1]+s[2]<=s[0])
            throw std::invalid_argument("degenerate triangle");
    }
public:
    virtual ~Triangle() = default;
    virtual std::array<double,3> sides() const = 0;
    double perimeter() const {
        auto s=sides(); return s[0]+s[1]+s[2];
    }
    virtual double area() const {
        auto s=sides(); double p=perimeter()/2;
        return std::sqrt(p*(p-s[0])*(p-s[1])*(p-s[2]));
    }
    double median(unsigned i) const {
        if(i>=3) throw std::out_of_range("side index must be 0,1,2");
        auto s=sides(); double a=s[i], b=s[(i+1)%3], c=s[(i+2)%3];
        return std::sqrt(2*b*b+2*c*c-a*a)/2;
    }
    double midline(unsigned i) const {
        if(i>=3) throw std::out_of_range("side index must be 0,1,2");
        return sides()[i]/2;
    }
    virtual double inradius() const { return 2*area()/perimeter(); }
    virtual double circumradius() const {
        auto s=sides(); return s[0]*s[1]*s[2]/(4*area());
    }
};

class TriangleBySides : public Triangle {
    std::array<double,3> s_;
public:
    TriangleBySides(double a,double b,double c) : s_{{a,b,c}} {
        validate(s_);
    }
    std::array<double,3> sides() const override { return s_; }
};

class TriangleByVertices : public Triangle {
    Point a_,b_,c_;
public:
    TriangleByVertices(Point a,Point b,Point c) : a_(a),b_(b),c_(c) {
        validate(sides());
    }
    // ma, mb, mc are the midpoints of BC, CA, AB respectively.
    TriangleByVertices(Point ma,Point mb,Point mc,MedianFeet)
        : TriangleByVertices(
            Point{mb.x+mc.x-ma.x,mb.y+mc.y-ma.y},
            Point{ma.x+mc.x-mb.x,ma.y+mc.y-mb.y},
            Point{ma.x+mb.x-mc.x,ma.y+mb.y-mc.y}) {}
    std::array<double,3> sides() const override {
        return {{distance(b_,c_),distance(c_,a_),distance(a_,b_)}};
    }
    double area() const override {
        return std::fabs((b_.x-a_.x)*(c_.y-a_.y)
                       -(b_.y-a_.y)*(c_.x-a_.x))/2;
    }
};

class RightTriangle : public TriangleBySides {
    double a_,b_;
public:
    RightTriangle(double a,double b)
        : TriangleBySides(a,b,std::hypot(a,b)),a_(a),b_(b) {}
    double area() const override { return a_*b_/2; }
    double inradius() const override {
        return (a_+b_-std::hypot(a_,b_))/2;
    }
    double circumradius() const override { return std::hypot(a_,b_)/2; }
};

void report(const Triangle& t) {
    auto s=t.sides();
    std::cout << "sides=" << s[0] << ',' << s[1] << ',' << s[2]
              << "; area=" << t.area() << "; P=" << t.perimeter()
              << "; r=" << t.inradius() << "; R=" << t.circumradius()
              << '\n';
    for (unsigned i=0;i<3;++i)
        std::cout << "side " << i << ": median=" << t.median(i)
                  << ", midline=" << t.midline(i) << '\n';
}

int main() {
    std::cout << std::fixed << std::setprecision(3);
    TriangleBySides sides(3,4,5);
    TriangleByVertices vertices({0,0},{3,0},{0,4});
    TriangleByVertices feet({1.5,2},{0,2},{1.5,0},MedianFeet{});
    RightTriangle right(3,4);
    const Triangle* figures[]={&sides,&vertices,&feet,&right};
    for (const Triangle* t:figures) report(*t);
    try { TriangleBySides invalid(1,2,3); }
    catch (const std::exception& e) {
        std::cout << "error: " << e.what() << '\n';
    }
    try { right.median(3); }
    catch (const std::exception& e) {
        std::cout << "error: " << e.what() << '\n';
    }
}
