#include "ratexpr/expression.hpp"

using namespace ratexpr; 

void test(const char* name, std::unique_ptr<Expression> expr) {
    std::cout << "\n" << name << '\n';

    std::cout << "Before: " << *expr << '\n';

    simplification(expr);

    std::cout << "After: " << *expr << '\n';
}

int main(){

    auto e = std::make_unique<Mul>(
        std::make_unique<Add>(std::make_unique<Const>(Fraction(1, 2)),
                            std::make_unique<Const>(Fraction(1, 3))),
        std::make_unique<Sub>(std::make_unique<Const>(Fraction(3)),
                            std::make_unique<Const>(Fraction(1, 4)))
                        );
    std::cout << *e << " = " << e->evaluate() << '\n';

    auto d = std::make_unique<Negative>(
        std::make_unique<Div>(std::make_unique<Const>(Fraction(2)),
                            std::make_unique<Const>(Fraction(3)))
                        );
    std::cout << *d << " = " << d->evaluate() << '\n';



    test("1. Constant folding",
        std::make_unique<Add>(
            std::make_unique<Const>(Fraction(2)),
            std::make_unique<Const>(Fraction(3))
        )
    );

    test("2. x + 0",
        std::make_unique<Add>(
            std::make_unique<Const>(Fraction(5)),
            std::make_unique<Const>(Fraction(0))
        )
    );

    test("3. x + (-x)",
        std::make_unique<Add>(
            std::make_unique<Const>(Fraction(5)),
            std::make_unique<Negative>(
                std::make_unique<Const>(Fraction(5))
            )
        )
    );

    test("4. x - x",
        std::make_unique<Sub>(
            std::make_unique<Const>(Fraction(5)),
            std::make_unique<Const>(Fraction(5))
        )
    );

    test("5. x * (-1)",
        std::make_unique<Mul>(
            std::make_unique<Const>(Fraction(5)),
            std::make_unique<Const>(Fraction(-1))
        )
    );

    test("6. 0 / x",
        std::make_unique<Div>(
            std::make_unique<Const>(Fraction(0)),
            std::make_unique<Const>(Fraction(5))
        )
    );

    test("7. Double negative",
        std::make_unique<Negative>(
            std::make_unique<Negative>(
                std::make_unique<Const>(Fraction(5))
            )
        )
    );


    return 0;
}