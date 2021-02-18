#pragma once

#include <vector>
#include <functional>
#include <unordered_set>

#include "Expressions/Expression.hpp"
#include "Expressions/FactExpression.hpp"
#include "Expressions/UnaryExpression.hpp"
#include "Expressions/BinaryExpression.hpp"

class ExpertSystemData {
public:
	ExpertSystemData();
    ~ExpertSystemData();

    void AddMainExpression(Expression *expression);
	
	Expression *Find(Expression *expression) const;
	
	std::vector<Expression *> FindAllImpliesExpressions(Expression *expression) const;

	[[nodiscard]] const std::vector<Expression *> &GetMainExpressions() const;

	[[nodiscard]] const std::vector<Expression *> &GetFacts() const;

	[[nodiscard]] const std::vector<Expression *> &GetQuery() const;

private:
	std::vector<Expression *> main_expressions_;
	std::vector<Expression *> facts_;
	std::vector<Expression *> query_;

private:
    struct ExpressionHasher {
    public:
        size_t operator()(const Expression *e) const {
            return std::hash<std::string>{}(e->ToString());
        }
    };

    struct ExpressionComparator {
    public:
        size_t operator()(const Expression *lhs, const Expression *rhs) const {
            return lhs->ToString() == rhs->ToString();
        }
    };

	std::unordered_set<Expression *, ExpressionHasher, ExpressionComparator> unique_expressions_;
};