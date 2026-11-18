#include "ratexpr/expression.hpp"
#include <chrono>
#include <string>

using namespace ratexpr;

const int n = 20000;
const int repeates = 5;
const int evaluates = 100;

using Clock = std::chrono::steady_clock;

std::unique_ptr<Expression> exp1() {
    std::unique_ptr<Expression> res = std::make_unique<Const>(Fraction(0));
    for (int i = 0; i < n; ++i) {
        res = std::make_unique<Add>(std::move(res), std::make_unique<Const>(Fraction(1)));
    }
    return res;
}

std::unique_ptr<Expression> exp2() {
    std::unique_ptr<Expression> res =std::make_unique<Const>(Fraction(0));
    for (int i = 0; i < n; ++i) {
        auto x1 = std::make_unique<Add>(std::make_unique<Const>(Fraction(2)),
                                    std::make_unique<Const>(Fraction(3)));

        auto x2 = std::make_unique<Add>(std::make_unique<Const>(Fraction(2)),
                                    std::make_unique<Const>(Fraction(3)));

        auto diff = std::make_unique<Sub>(std::move(x1),std::move(x2));

        res = std::make_unique<Add>(std::move(res),std::move(diff));
    }
    return res;
}

std::unique_ptr<Expression> exp3() {
    std::unique_ptr<Expression> res =std::make_unique<Const>(Fraction(0));
    for (int i = 0; i < n; ++i) {
        auto x = std::make_unique<Mul>(std::make_unique<Const>(Fraction(i + 1)),
                                    std::make_unique<Const>(Fraction(0)));

        res = std::make_unique<Add>(std::move(res),std::move(x));
    }
    return res;
}

std::unique_ptr<Expression> exp4() {
    std::unique_ptr<Expression> res =std::make_unique<Const>(Fraction(0));
    for (int i = 0; i < n; ++i) {
        auto sum = std::make_unique<Add>(std::make_unique<Const>(Fraction(i + 1)),
                                    std::make_unique<Const>(Fraction(0)));
        auto x = std::make_unique<Mul>(std::move(sum),std::make_unique<Const>(Fraction(1)));
        res = std::make_unique<Add>(std::move(res),std::move(x));
    }
    return res;
}

void experiment(const std::string& name,std::unique_ptr<Expression> (*x)()) {
    double originalTime = 0;
    double simplifiedTime = 0;
    double simplificationTime = 0;
    double evaluationTime = 0;

    for (int rep = 0; rep < repeates; ++rep) {
        auto orig = x();
        auto start = Clock::now();
        
        Fraction originalValue = orig->evaluate();
        
        auto end = Clock::now();

        originalTime += std::chrono::duration<double, std::milli>(end - start).count();

        auto simplified = x();
        start = Clock::now();

        simplification(simplified);

        end = Clock::now();

        double timee =std::chrono::duration<double, std::milli>(end - start).count();

        simplificationTime += timee;

        start = Clock::now();

        Fraction simplifiedValue = simplified->evaluate();

        end = Clock::now();

        double evalTime =std::chrono::duration<double, std::milli>(end - start).count();

        evaluationTime += evalTime;

        simplifiedTime += timee + evalTime;

        if (!(originalValue == simplifiedValue)) {
            std::cout << "Значения различаются!";
            return;
        }
    }

    originalTime /= repeates;
    simplifiedTime /= repeates;
    simplificationTime /= repeates;
    evaluationTime /= repeates;

    std::cout <<"\n"<< name << "\n";
    std::cout << "Вычисление без симплификации: "<< originalTime << " ms\n";
    std::cout << "Симплификация: "<< simplificationTime << " ms\n";
    std::cout << "Вычисление после симплификации: "<< evaluationTime << " ms\n";
    std::cout << "Всего симплификация занимает: "<< simplifiedTime << " ms\n";
    std::cout << evaluates << " вычислений без симплификации: "<< originalTime * evaluates << " ms\n";
    std::cout << "симплификация и " << evaluates << " вычислений: " << simplificationTime + evaluationTime * evaluates << " ms\n";

}

int main() {
    experiment("experiment 1", exp1);
    experiment("experiment 2", exp2);
    experiment("experiment 3", exp3);
    experiment("experiment 4", exp4);
    return 0;
}