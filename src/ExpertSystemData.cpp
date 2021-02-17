#include "ExpertSystemData.hpp"

#include <utility>

Expression *ExpertSystemData::Find(Expression *expression) const {
	for (Expression *item : main_expressions_) {
		auto find_result = item->Find(expression);
		if (find_result != nullptr)
			return find_result;
	}
	return nullptr;
}

void ExpertSystemData::AddMainExpression(Expression *expression) {
	if (Find(expression) != nullptr) //if two identical rules
		return;

	main_expressions_.push_back(expression);
}

const std::vector<Expression *> &ExpertSystemData::GetMainExpressions() const {
	return main_expressions_;
}

const std::vector<Expression *> &ExpertSystemData::GetFacts() const {
	return facts_;
}

const std::vector<Expression *> &ExpertSystemData::GetQuery() const {
	return query_;
}

std::vector<Expression *> ExpertSystemData::FindAllMainKeepers(Expression *expression) const {
	// TODO check
	std::vector<Expression *> result(main_expressions_.size());
	for (auto main_expression : main_expressions_) {
		if (main_expression->Find(expression) != nullptr) {
			result.push_back(expression);
		}
	}
	return result;
}
