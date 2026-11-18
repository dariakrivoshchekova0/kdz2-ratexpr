#pragma once
#include <cstdint>
#include <iostream>

namespace ratexpr {

class Fraction {
public:
    Fraction();
    Fraction(std::int64_t numerator, std::int64_t denominator = 1);
    
    Fraction& operator+=(const Fraction& o);  
    Fraction& operator+=(std::uint32_t k); 
    
    Fraction& operator-=(const Fraction& o);  
    Fraction& operator-=(std::uint32_t k);

    Fraction& operator*=(const Fraction& o);  
    Fraction& operator*=(std::uint32_t k);

    Fraction& operator/=(const Fraction& o);  
    Fraction& operator/=(std::uint32_t k);
    
    Fraction operator-() const;
    
    friend Fraction operator+(const Fraction& a, const Fraction& b);
    friend Fraction operator+(const Fraction& a, std::uint32_t k);
    friend Fraction operator+(std::uint32_t k, const Fraction& b);

    friend Fraction operator-(const Fraction& a, const Fraction& b);
    friend Fraction operator-(const Fraction& a, std::uint32_t k);
    friend Fraction operator-(std::uint32_t k, const Fraction& b);

    friend Fraction operator*(const Fraction& a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, std::uint32_t k);
    friend Fraction operator*(std::uint32_t k, const Fraction& b);

    friend Fraction operator/(const Fraction& a, const Fraction& b);
    friend Fraction operator/(const Fraction& a, std::uint32_t k);
    friend Fraction operator/(std::uint32_t k, const Fraction& b);
    
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

    bool operator==(const Fraction& o) const;
    bool operator!=(const Fraction& o) const;

private:
    std::int64_t num_;
    std::int64_t den_;
    
    void check();
};

} 
