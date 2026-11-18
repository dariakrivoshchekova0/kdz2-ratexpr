#pragma once
#include "ratexpr/fraction.hpp"
#include <memory>
#include <ostream>
#include <cstddef>

namespace ratexpr {

class Expression;
void simplification(std::unique_ptr<Expression>& expr);

class Expression {
public:
    virtual ~Expression() = default;
    virtual Fraction evaluate() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual bool equals(const Expression& o) const = 0;
    virtual bool canThrow() const = 0;
    virtual std::size_t operationCount() const = 0;
};

std::ostream& operator<<(std::ostream& os, const Expression& e);

class Const : public Expression {
public:
    explicit Const(const Fraction& value);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
    bool equals(const Expression& o) const override;
    bool canThrow() const override;
    std::size_t operationCount() const override;

private:
    Fraction const_;
};

class Negative : public Expression {
public:
    explicit Negative(std::unique_ptr<Expression> operand);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
    bool equals(const Expression& o) const override;
    const Expression& operand() const;
    bool canThrow() const override;
    std::size_t operationCount() const override;

private:
    friend void simplification(std::unique_ptr<Expression>& expr);
    std::unique_ptr<Expression> neg_;
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs);

protected:
    std::unique_ptr<Expression> lhs_;
    std::unique_ptr<Expression> rhs_;
    bool equalsChildren(const BinaryExpression& o) const;
    friend void simplification(std::unique_ptr<Expression>& expr);
};

class Add : public BinaryExpression {
public:
    Add(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
    bool equals(const Expression& o) const override;
    bool canThrow() const override;
    std::size_t operationCount() const override;
};

class Sub : public BinaryExpression {
public:
    Sub(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
    bool equals(const Expression& o) const override;
    bool canThrow() const override;
    std::size_t operationCount() const override;
};

class Mul : public BinaryExpression {
public:
    Mul(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
    bool equals(const Expression& o) const override;
    bool canThrow() const override;
    std::size_t operationCount() const override;
};

class Div : public BinaryExpression {
public:
    Div(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
    bool equals(const Expression& o) const override;
    bool canThrow() const override;
    std::size_t operationCount() const override;
};
}


