#include <cmath>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

// C++14: dynamic exception specifications are removed in C++17.
double sumPlain(double a, double q, int n) {
    if (!std::isfinite(a) || !std::isfinite(q) || n <= 0)
        throw std::invalid_argument("finite a,q and n > 0 required");
    long double term = a, sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += term;
        if (!std::isfinite(sum))
            throw std::overflow_error("sum overflow");
        if (i + 1 < n) {
            term *= q;
            if (!std::isfinite(term))
                throw std::overflow_error("term overflow");
        }
    }
    if (std::fabs(sum) > std::numeric_limits<double>::max())
        throw std::overflow_error("result is outside double range");
    return static_cast<double>(sum);
}

// No exception may escape throw(). Main rethrows the saved exception.
double sumNoThrow(double a, double q, int n,
                  std::exception_ptr& error) throw() {
    error = nullptr;
    try { return sumPlain(a, q, n); }
    catch (...) { error = std::current_exception(); }
    return std::numeric_limits<double>::quiet_NaN();
}

double sumStandard(double a, double q, int n)
    throw(std::invalid_argument, std::overflow_error) {
    return sumPlain(a, q, n);
}

class EmptyError {};
struct ParametersError { double a, q; int n; };
class ProgressionError : public std::exception {
public:
    double a, q; int n;
    ProgressionError(double first, double ratio, int count)
        : a(first), q(ratio), n(count) {}
    const char* what() const noexcept override {
        return "invalid progression parameters or overflow";
    }
};

double sumEmpty(double a, double q, int n) throw(EmptyError) {
    try { return sumPlain(a, q, n); }
    catch (const std::exception&) { throw EmptyError{}; }
}
double sumParameters(double a, double q, int n)
    throw(ParametersError) {
    try { return sumPlain(a, q, n); }
    catch (const std::exception&) { throw ParametersError{a,q,n}; }
}
double sumCustom(double a, double q, int n)
    throw(ProgressionError) {
    try { return sumPlain(a, q, n); }
    catch (const std::exception&) { throw ProgressionError(a,q,n); }
}

int main() {
    std::cout << "S(2,3,4) = " << sumPlain(2,3,4) << '\n';
    std::cout << "S(5,1,3) = " << sumStandard(5,1,3) << '\n';
    std::cout << "S(2,-1,4) = " << sumCustom(2,-1,4) << '\n';
    try { sumPlain(2,3,0); }
    catch (const std::invalid_argument& e) {
        std::cout << "plain: " << e.what() << '\n';
    }
    std::exception_ptr saved;
    sumNoThrow(2,3,0,saved);
    try { if (saved) std::rethrow_exception(saved); }
    catch (const std::invalid_argument& e) {
        std::cout << "throw(): " << e.what() << '\n';
    }
    try { sumStandard(1e308,10,3); }
    catch (const std::overflow_error& e) {
        std::cout << "standard: " << e.what() << '\n';
    }
    try { sumEmpty(2,3,0); }
    catch (const EmptyError&) { std::cout << "empty: error\n"; }
    try { sumParameters(2,3,0); }
    catch (const ParametersError& e) {
        std::cout << "parameters: a=" << e.a << ", q="
                  << e.q << ", n=" << e.n << '\n';
    }
    try { sumCustom(2,3,0); }
    catch (const ProgressionError& e) {
        std::cout << "custom: " << e.what() << "; n=" << e.n << '\n';
    }
}
