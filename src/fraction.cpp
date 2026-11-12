#include "ratexpr/fraction.hpp"
#include <numeric>
#include <stdexcept>

namespace ratexpr {

    Fraction::Fraction(): num_(0),den_(1) {}
    Fraction::Fraction(std::int64_t numerator, std::int64_t denominator)
    : num_(numerator), den_(denominator) {
        if(den_==0){
            throw std::invalid_argument("Деление на ноль!");
        }
        check();
    }

    void Fraction::check(){
        if (num_ == 0) {
        den_ = 1;
        return;
    }
        if(den_<0){
            num_*=-1;
            den_*=-1;
    }
        std::int64_t nod=std::gcd(std::abs((int)num_),(int)den_);
        num_/=nod;
        den_/=nod;
    }
    
    Fraction& Fraction::operator+=(const Fraction& o){
        num_=num_*o.den_+den_*o.num_;
        den_=den_*o.den_;
        check();
        return *this; 
    }
    Fraction& Fraction::operator+=(std::uint32_t k){
        return *this += Fraction(k);
    } 

    Fraction& Fraction::operator-=(const Fraction& o){
        num_=num_*o.den_-den_*o.num_;
        den_=den_*o.den_; 
        check();
        return *this;
    }
    Fraction& Fraction::operator-=(std::uint32_t k){
        return *this -= Fraction(k);
    }

    Fraction& Fraction::operator*=(const Fraction& o){
        num_=num_*o.num_;
        den_=den_*o.den_;
        check();
        return *this; 
    }
    Fraction& Fraction::operator*=(std::uint32_t k){
        return *this *= Fraction(k);
    }

    Fraction& Fraction::operator/=(const Fraction& o){
        if (o.num_ == 0) {
            throw std::invalid_argument("Деление на ноль!");
        }
        num_=num_*o.den_;
        den_=den_*o.num_;
        check();
        return *this; 
    }
    Fraction& Fraction::operator/=(std::uint32_t k){
        return *this /= Fraction(k);
    }
    
    Fraction Fraction::operator-() const{
        return Fraction(-num_,den_);
    }
    
    Fraction operator+(const Fraction& a, const Fraction& b){
        Fraction res=a;
        res+=b;
        return res;
    }
    Fraction operator+(const Fraction& a, std::uint32_t k){
        return a + Fraction(k);
    }
    Fraction operator+(std::uint32_t k, const Fraction& b){
        return Fraction(k) + b;
    }

    Fraction operator-(const Fraction& a, const Fraction& b){
        Fraction res=a;
        res-=b;
        return res;
    }
    Fraction operator-(const Fraction& a, std::uint32_t k){
        return a - Fraction(k);
    }
    Fraction operator-(std::uint32_t k, const Fraction& b){
        return Fraction(k) - b;
    }
    
    Fraction operator*(const Fraction& a, const Fraction& b){
        Fraction res=a;
        res*=b;
        return res;
    }
    Fraction operator*(const Fraction& a, std::uint32_t k){
        return a * Fraction(k);
    }
    Fraction operator*(std::uint32_t k, const Fraction& b){
        return Fraction(k) * b;
    }

    Fraction operator/(const Fraction& a, const Fraction& b){
        Fraction res=a;
        res/=b;
        return res;
    }
    Fraction operator/(const Fraction& a, std::uint32_t k){
        return a / Fraction(k);
    }
    Fraction operator/(std::uint32_t k, const Fraction& b){
        return Fraction(k) / b;
    }

    std::ostream& operator<<(std::ostream& os, const Fraction& f){
        if(f.den_==1){
            os<<f.num_;
        } else{
            os<<f.num_<<"/"<<f.den_;
        }

        return os;
    }

};
