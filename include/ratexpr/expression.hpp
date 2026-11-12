#pragma once
#include "ratexpr/fraction.hpp"
#include <memory>

namespace ratexpr {

class Expression {
public:
    virtual ~Expression() = default;
    virtual Fraction evaluate() const = 0;
    virtual void print(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Expression& e);

class Const : public Expression {
public:
    explicit Const(const Fraction& value);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
private:
    Fraction const_;
};

class Negative : public Expression {
public:
    explicit Negative(std::unique_ptr<Expression> operand);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
private:
    std::unique_ptr<Expression> neg_;
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(std::unique_ptr<Expression> lhs,
                     std::unique_ptr<Expression> rhs);
protected:
        std::unique_ptr<Expression> lhs_;
        std::unique_ptr<Expression> rhs_;
};

class Add : public BinaryExpression { 
    Add(std::unique_ptr<Expression> lhs,
        std::unique_ptr<Expression> rhs);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
 }; 

class Sub : public BinaryExpression { 
    Sub(std::unique_ptr<Expression> lhs,
        std::unique_ptr<Expression> rhs);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
 }; 

class Mul : public BinaryExpression { 
    Mul(std::unique_ptr<Expression> lhs,
        std::unique_ptr<Expression> rhs);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
 }; 

class Div : public BinaryExpression { 
    Div(std::unique_ptr<Expression> lhs,
        std::unique_ptr<Expression> rhs);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
 }; 
} 
