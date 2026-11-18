#include "ratexpr/expression.hpp"
#include <utility>

namespace ratexpr {

std::ostream& operator<<(std::ostream& os, const Expression& e){
    e.print(os);
    return os;
}

std::size_t Add::operationCount() const {
    return 1 + lhs_->operationCount() + rhs_->operationCount();
}

std::size_t Sub::operationCount() const {
    return 1 + lhs_->operationCount() + rhs_->operationCount();
}

std::size_t Mul::operationCount() const {
    return 1 + lhs_->operationCount() + rhs_->operationCount();
}

std::size_t Div::operationCount() const {
    return 1 + lhs_->operationCount() + rhs_->operationCount();
}

Const::Const(const Fraction& value): const_(value){}

Fraction Const::evaluate() const {
    return const_;
}

void Const::print(std::ostream& os) const {
    os<<const_;
}

bool Const::equals(const Expression& o) const {
    const Const* p = dynamic_cast<const Const*>(&o);
    if (p == nullptr) {
        return false;
    }
    return const_ == p->const_;
}

bool Const::canThrow() const {
    return false;
}

std::size_t Const::operationCount() const {
    return 0;
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

bool Negative::equals(const Expression& o) const{
    const Negative* p = dynamic_cast<const Negative*>(&o);

    if (p == nullptr) {
        return false;
    }

    return neg_->equals(*p->neg_);   
}

const Expression& Negative::operand() const {
    return *neg_;
}

bool Negative::canThrow() const {
    return neg_->canThrow();
}

std::size_t Negative::operationCount() const {
    return 1 + neg_->operationCount();
}

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)){}

bool BinaryExpression::equalsChildren(const BinaryExpression& o) const {
    return lhs_->equals(*o.lhs_) && rhs_->equals(*o.rhs_);
}

Add::Add(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : BinaryExpression(std::move(lhs), std::move(rhs)){}

Fraction Add::evaluate() const {
    return lhs_->evaluate() + rhs_->evaluate();
}

bool Add::equals(const Expression& o) const {
    const Add* p = dynamic_cast<const Add*>(&o);
    return p != nullptr && equalsChildren(*p);
}

void Add::print(std::ostream& os) const {
    os<<"(";
    lhs_->print(os);
    os<<" + ";
    rhs_->print(os);
    os<<")";
}

bool Add::canThrow() const {
    return lhs_->canThrow() || rhs_->canThrow();
}

Sub::Sub(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : BinaryExpression(std::move(lhs), std::move(rhs)){}

Fraction Sub::evaluate() const {
    return lhs_->evaluate() - rhs_->evaluate();
}

bool Sub::equals(const Expression& o) const {
    const Sub* p = dynamic_cast<const Sub*>(&o);
    return p != nullptr && equalsChildren(*p);
}

void Sub::print(std::ostream& os) const {
    os<<"(";
    lhs_->print(os);
    os<<" - ";
    rhs_->print(os);
    os<<")";
}

bool Sub::canThrow() const {
    return lhs_->canThrow() || rhs_->canThrow();
}

Mul::Mul(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : BinaryExpression(std::move(lhs), std::move(rhs)){}

Fraction Mul::evaluate() const {
    return lhs_->evaluate() * rhs_->evaluate();
}

bool Mul::equals(const Expression& o) const {
    const Mul* p = dynamic_cast<const Mul*>(&o);
    return p != nullptr && equalsChildren(*p);
}

void Mul::print(std::ostream& os) const {
    os<<"(";
    lhs_->print(os);
    os<<" * ";
    rhs_->print(os);
    os<<")";
}

bool Mul::canThrow() const {
    return lhs_->canThrow() || rhs_->canThrow();
}

Div::Div(std::unique_ptr<Expression> lhs,std::unique_ptr<Expression> rhs)
    : BinaryExpression(std::move(lhs), std::move(rhs)){}
    
Fraction Div::evaluate() const {
    return lhs_->evaluate() / rhs_->evaluate();
}

bool Div::equals(const Expression& o) const {
    const Div* p = dynamic_cast<const Div*>(&o);
    return p != nullptr && equalsChildren(*p);
}

void Div::print(std::ostream& os) const {
    os<<"(";
    lhs_->print(os);
    os<<" / ";
    rhs_->print(os);
    os<<")";
}

bool Div::canThrow() const {
    if (lhs_->canThrow() || rhs_->canThrow()) {
        return true;
    }

    const Const* denominator = dynamic_cast<const Const*>(rhs_.get());

    if (denominator == nullptr) {
        return true;
    }
    return denominator->evaluate() == Fraction(0);
}

void simplification(std::unique_ptr<Expression>& expr) {
    if (expr == nullptr) {
        return;
    }

    Negative* neg = dynamic_cast<Negative*>(expr.get());

    if (neg != nullptr) {
        simplification(neg->neg_);

        Const* constt = dynamic_cast<Const*>(neg->neg_.get());

        if (constt != nullptr) {
            expr = std::make_unique<Const>(-constt->evaluate());
            return;
        }

        Negative* double_neg = dynamic_cast<Negative*>(neg->neg_.get());

        if (double_neg != nullptr) {
            expr = std::move(double_neg->neg_);
            return;
        }
        return;
    }

BinaryExpression* x = dynamic_cast<BinaryExpression*>(expr.get());
    if (x == nullptr) {
        return;
    }

    simplification(x->lhs_);
    simplification(x->rhs_);

    Const* left = dynamic_cast<Const*>(x->lhs_.get());
    Const* right = dynamic_cast<Const*>(x->rhs_.get());

    if (left != nullptr && right != nullptr) {
        Fraction a = left->evaluate();
        Fraction b = right->evaluate();

        if (dynamic_cast<Add*>(x) != nullptr) {
            expr = std::make_unique<Const>(a + b);
            return;
        }

        if (dynamic_cast<Sub*>(x) != nullptr) {
            expr = std::make_unique<Const>(a - b);
            return;
        }

        if (dynamic_cast<Mul*>(x) != nullptr) {
            expr = std::make_unique<Const>(a * b);
            return;
        }

        if (dynamic_cast<Div*>(x) != nullptr && b != Fraction(0)) {
            expr = std::make_unique<Const>(a / b);
            return;
        }
    }

    if (dynamic_cast<Add*>(x) != nullptr) {
        if (right != nullptr && right->evaluate() == Fraction(0)) {
            expr = std::move(x->lhs_);
            return;
        }

        if (left != nullptr && left->evaluate() == Fraction(0)) {
            expr = std::move(x->rhs_);
            return;
        }

        Negative* neg_right =dynamic_cast<Negative*>(x->rhs_.get());

        if (neg_right != nullptr && x->lhs_->equals(neg_right->operand())) {
            expr = std::make_unique<Const>(Fraction(0));
            return;
        }

        Negative* neg_left =dynamic_cast<Negative*>(x->lhs_.get());

        if (neg_left != nullptr && neg_left->operand().equals(*x->rhs_)) {
            expr = std::make_unique<Const>(Fraction(0));
            return;
        }
    }
    
    if (dynamic_cast<Sub*>(x) != nullptr) {
        if (right != nullptr && right->evaluate() == Fraction(0)) {
            expr = std::move(x->lhs_);
            return;
        }

        if (left != nullptr && left->evaluate() == Fraction(0)) {
            expr = std::make_unique<Negative>(
                std::move(x->rhs_)
            );
            simplification(expr);
            return;
        }

        if (x->lhs_->equals(*x->rhs_)) {
            expr = std::make_unique<Const>(Fraction(0));
            return;
        }   
    }

    if (dynamic_cast<Mul*>(x) != nullptr) {
        if (left != nullptr && left->evaluate() == Fraction(1)) {
            expr = std::move(x->rhs_);
            return;
        }

        if (right != nullptr && right->evaluate() == Fraction(1)) {
            expr = std::move(x->lhs_);
            return;
        }

        if (right != nullptr && right->evaluate() == Fraction(-1)) {
            expr = std::make_unique<Negative>(std::move(x->lhs_));
            simplification(expr);
            return;
        }

        if (left != nullptr && left->evaluate() == Fraction(-1)) {
            expr = std::make_unique<Negative>(std::move(x->rhs_));
            simplification(expr);
            return;
        }

        if (left != nullptr && left->evaluate() == Fraction(0) && !x->rhs_->canThrow()) {
            expr = std::make_unique<Const>(Fraction(0));
            return;
        }

        if (right != nullptr && right->evaluate() == Fraction(0) && !x->lhs_->canThrow()) {
            expr = std::make_unique<Const>(Fraction(0));
            return;
        }
    }

    if (dynamic_cast<Div*>(x) != nullptr) {
        if (right != nullptr && right->evaluate() == Fraction(1)) {
            expr = std::move(x->lhs_);
            return;
        }

        if (left != nullptr && left->evaluate() == Fraction(0) && right != nullptr && right->evaluate() != Fraction(0)) {
            expr = std::make_unique<Const>(Fraction(0));
            return;
        }
    }
}

}
