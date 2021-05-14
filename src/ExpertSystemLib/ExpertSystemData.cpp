#include <stack>

#include "ExpertSystemData.hpp"

Expression *ExpertSystemData::Find(Expression *expression) {
	auto it = unique_expressions_.find(expression);

	if (it != unique_expressions_.end()) {
		delete expression;
		return *it;
	}
	unique_expressions_.insert(expression);
	return expression;
}

void ExpertSystemData::AddMainExpression(Expression *expression) {
	main_expressions_.insert(expression);
}

std::vector<Expression *> ExpertSystemData::FindAllImpliesExpressions(Expression *expression) const {
	std::vector<Expression *> implies_expressions;
	BinaryExpression *binary_main_expr;
	
	for (Expression *main_expression : main_expressions_) {
		binary_main_expr = dynamic_cast<BinaryExpression *>(main_expression);
		
		if (binary_main_expr->GetBinaryOperator() == MUTUAL_IMPLIES) {
			if (binary_main_expr->Find(expression) != nullptr) {
				implies_expressions.push_back(main_expression);
			}
		}
		else if (binary_main_expr->GetBinaryOperator() == IMPLIES) {
			if (binary_main_expr->GetRightChild()->Find(expression) != nullptr) {
				implies_expressions.push_back(main_expression);
			}
		}
	}
	
	return implies_expressions;
}

ExpertSystemData::ExpertSystemData() {
	FillDefaultFacts();
}

ExpertSystemData::ExpertSystemData(const ExpertSystemData &expert_system_data) {
	*this = expert_system_data;
}

ExpertSystemData &ExpertSystemData::operator=(const ExpertSystemData &expert_system_data)
{
	if (this == &expert_system_data) {
		return *this;
	}

	FillDefaultFacts();
	for (Expression *old_fact_expr : expert_system_data.GetFacts()) {
		(*facts_.find(old_fact_expr))->UpdateState(old_fact_expr->GetState());
	}
	FillQueriesFromOld(expert_system_data.GetQueries());
	FillMainExpressionsFromOld(expert_system_data.GetMainExpressions());

	return *this;
}

ExpertSystemData::~ExpertSystemData() {
	for (Expression *e : unique_expressions_) {
		delete e;
	}
	unique_expressions_.clear();
}

void ExpertSystemData::AddQueryExpression(Expression* expression) {
	queries_.insert(expression);
}

const ExpertSystemData::ExpressionsSet& ExpertSystemData::GetQueries() const {
	return queries_;
}

const ExpertSystemData::ExpressionsSet& ExpertSystemData::GetFacts() const {
	return facts_;
}

const ExpertSystemData::ExpressionsSet& ExpertSystemData::GetMainExpressions() const {
	return main_expressions_;
}

Expression *ExpertSystemData::CreateExpressionFromOldWithUsingUnique(const Expression *old_expression) {
	switch (old_expression->GetType()) {
		case FACT:
			return this->Find(new FactExpression(dynamic_cast<const FactExpression *>(old_expression)->GetFact()));
		case UNARY: {
			auto *cur_unary = dynamic_cast<const UnaryExpression *>(old_expression);
			return this->Find(new UnaryExpression(cur_unary->GetUnaryOperator(),
								CreateExpressionFromOldWithUsingUnique(cur_unary->GetChild())));
		}
		case BINARY: {
			auto *cur_binary = dynamic_cast<const BinaryExpression *>(old_expression);
			return this->Find(new BinaryExpression(
					CreateExpressionFromOldWithUsingUnique(cur_binary->GetLeftChild()),
					cur_binary->GetBinaryOperator(),
					CreateExpressionFromOldWithUsingUnique(cur_binary->GetRightChild())));
		}
	}
}

void ExpertSystemData::FillMainExpressionsFromOld(const ExpertSystemData::ExpressionsSet &old_main_expression_set) {
	for (Expression *old_main_expression : old_main_expression_set) {
		Expression *new_main_expression = CreateExpressionFromOldWithUsingUnique(old_main_expression);
		AddMainExpression(new_main_expression);
	}
}

void ExpertSystemData::FillDefaultFacts() {
	for (int i = 'A'; i <= 'Z'; i++) {
		facts_.insert(this->Find(new FactExpression(static_cast<char>(i))));
	}
}

void ExpertSystemData::FillQueriesFromOld(const ExpertSystemData::ExpressionsSet& old_queries_set) {
	for (const Expression *old_query : old_queries_set) {
		AddQueryExpression(this->Find(new FactExpression(dynamic_cast<const FactExpression *>(old_query)->GetFact())));
	}
}
