#include <array>
#include <iostream>
#include <memory>

class Base {
public:
    virtual ~Base() = default;
    virtual void myname() { std::cout << "This is class Base\n"; }
};
class DerA : virtual public Base {
public:
    void myname() override { std::cout << "This is class DerA\n"; }
};
class DerB : virtual public Base {
public:
    void myname() override { std::cout << "This is class DerB\n"; }
};
class DerAB : public DerA, public DerB {
public:
    void myname() override { std::cout << "This is class DerAB\n"; }
};

int main() {
    Base base; DerA a; DerB b; DerAB ab;
    std::cout << "Automatic objects:\n";
    base.myname(); a.myname(); b.myname(); ab.myname();

    std::array<std::unique_ptr<Base>,4> objects;
    objects[0]=std::make_unique<Base>();
    objects[1]=std::make_unique<DerA>();
    objects[2]=std::make_unique<DerB>();
    objects[3]=std::make_unique<DerAB>();
    std::cout << "Dynamic objects via Base pointers:\n";
    for (const auto& object:objects) object->myname();
}
