#pragma once

// Variant 6: calories per 100 g and product mass in kg.
struct Product {
    int first = 1;
    double second = 0.1;

    bool Init(int kcal, double kg);
    bool Read();
    double power() const;
    void Display() const;
};
