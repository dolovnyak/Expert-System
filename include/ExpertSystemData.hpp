#pragma once

#include <vector>
#include <functional>
#include <unordered_set>

#include "Expressions/Expression.hpp"
#include "Expressions/FactExpression.hpp"
#include "Expressions/UnaryExpression.hpp"
#include "Expressions/BinaryExpression.hpp"

class ExpertSystemData {
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
	
public:
	using ExpressionsSet = std::unordered_set<Expression *, ExpressionHasher, ExpressionComparator>;

	ExpertSystemData();

	ExpertSystemData(const ExpertSystemData &expert_system_data);

	ExpertSystemData &operator=(const ExpertSystemData &expert_system_data);

	~ExpertSystemData();

	void AddMainExpression(Expression *expression);

	void AddQueryExpression(Expression *expression);

	Expression *Find(Expression *expression);

	std::vector<Expression *> FindAllImpliesExpressions(Expression *expression) const;
	
	[[nodiscard]] const ExpressionsSet &GetMainExpressions() const;

	[[nodiscard]] const ExpressionsSet &GetFacts() const;

	[[nodiscard]] const ExpressionsSet &GetQueries() const;

private:
	ExpressionsSet main_expressions_;
	ExpressionsSet facts_;
	ExpressionsSet queries_;

	ExpressionsSet unique_expressions_;
	
	void FillDefaultFacts();
	Expression *CreateExpressionFromOldWithUsingUnique(const Expression *old_expression);
	void FillQueriesFromOld(const ExpressionsSet &old_queries_set);
	void FillMainExpressionsFromOld(const ExpressionsSet &old_main_expression_set);
};