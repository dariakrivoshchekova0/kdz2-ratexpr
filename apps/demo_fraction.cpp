#include "ratexpr/fraction.hpp"

using namespace ratexpr;

int main(){
    std::cout << Fraction(6, -8) << '\n';
    std::cout << Fraction(10, 4) << '\n';

    Fraction a(1, 2);
    Fraction b(1, 3);

    std::cout << a + b << '\n';
    std::cout << a - b << '\n';
    std::cout << a * b << '\n';
    std::cout << a / b << '\n';

    std::cout << a + 2u << '\n';
    std::cout << 2u + a << '\n';

    std::cout << a - 2u << '\n';
    std::cout << 2u - a << '\n';

    std::cout << a / 2u << '\n';
    std::cout << 2u / a << '\n';

    Fraction acc(0);
    acc += Fraction(1, 2);
    acc += Fraction(1, 3);
    acc *= 6u;

    std::cout << acc << '\n';

    try {
        Fraction d(1, 0);
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << '\n';
    }

    try {
        std::cout << a / 0u << '\n';
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}