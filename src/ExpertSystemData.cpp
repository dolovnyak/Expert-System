#include "ExpertSystemData.hpp"

Expression *ExpertSystemData::Find(Expression *expression) const {
	for (Expression *item : main_expressions_) {
		Expression *find_result = item->Find(expression);
		if (find_result != nullptr)
			return find_result;
	}
	if (expression->GetType() == ExpressionType::FACT) {
		for (Expression *fact_expression : facts_) {
			if (*fact_expression == *expression)
				return fact_expression;
		}
		throw std::logic_error("there is no fact '" + expression->ToString() + "' in ExpertSystemData.facts_");
	}
	return nullptr;
}

void ExpertSystemData::AddMainExpression(Expression *expression) {
	if (Find(expression) != nullptr) //if two identical rules
		return;

	main_expressions_.push_back(expression);
}

void ExpertSystemData::AddExpression(Expression *expression) {
    unique_expressions_.insert(expression);
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

ExpertSystemData::ExpertSystemData()
{
	for (int i = 'A'; i <= 'Z'; i++) {
		facts_.push_back(new FactExpression(static_cast<char>(i)));
	}
}

ExpertSystemData::~ExpertSystemData() {
    for (auto ue : unique_expressions_) {
        delete ue;
    }
}

