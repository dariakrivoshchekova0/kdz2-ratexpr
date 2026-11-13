#include "ratexpr/expression.hpp"
#include <utility>

namespace ratexpr {

std::ostream& operator<<(std::ostream& os, const Expression& e){
    e.print(os);
    return os;
}

Const::Const(const Fraction& value): const_(value){}
Fraction Const::evaluate() const {
    return const_;
}
void Const::print(std::ostream& os) const {
    os<<const_;
}

Negative::Negative(std::unique_ptr<Expression> operand): neg_(std::move(operand)){}
Fraction Negative::evaluate() const {
    return -neg_ -> evaluate();
}
void Negative::print(std::ostream& os) const {
    os << "(-";
    neg_->print(os);
    os << ")";
}

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)){}

Add::Add(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : BinaryExpression(std::move(lhs), std::move(rhs)){}
Fraction Add::evaluate() const {
    return lhs_->evaluate() + rhs_->evaluate();
}
void Add::print(std::ostream& os) const {
    os<<"(";
    lhs_->print(os);
    os<<" + ";
    rhs_->print(os);
    os<<")";
}

Sub::Sub(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : BinaryExpression(std::move(lhs), std::move(rhs)){}
Fraction Sub::evaluate() const {
    return lhs_->evaluate() - rhs_->evaluate();
}
void Sub::print(std::ostream& os) const {
    os<<"(";
    lhs_->print(os);
    os<<" - ";
    rhs_->print(os);
    os<<")";
}

Mul::Mul(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : BinaryExpression(std::move(lhs), std::move(rhs)){}
Fraction Mul::evaluate() const {
    return lhs_->evaluate() * rhs_->evaluate();
}
void Mul::print(std::ostream& os) const {
    os<<"(";
    lhs_->print(os);
    os<<" * ";
    rhs_->print(os);
    os<<")";
}

Div::Div(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : BinaryExpression(std::move(lhs), std::move(rhs)){}
Fraction Div::evaluate() const {
    return lhs_->evaluate() / rhs_->evaluate();
}
void Div::print(std::ostream& os) const {
    os<<"(";
    lhs_->print(os);
    os<<" / ";
    rhs_->print(os);
    os<<")";
}

}