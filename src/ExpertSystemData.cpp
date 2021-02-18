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
	expression = Find(expression);
	main_expressions_.insert(expression);

//	std::stack<Expression *> stack;
//	stack.push(expression);
//	while (!stack.empty()) {
//	    Expression *cur = stack.top();
//	    stack.pop();
//
//	    unique_expressions_.insert(cur);
//	    switch (cur->GetType()) {
//            case FACT:
//                break;
//            case UNARY: {
//                auto unary = dynamic_cast<UnaryExpression *>(cur);
//                stack.push(unary->GetChild());
//                break;
//            }
//            case BINARY: {
//                auto binary = dynamic_cast<BinaryExpression *>(cur);
//                stack.push(binary->GetLeftChild());
//                stack.push(binary->GetRightChild());
//                break;
//            }
//        }
//	}
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
	    auto fact = new FactExpression(static_cast<char>(i));
		facts_.insert(fact);
		unique_expressions_.insert(fact);
	}
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

const ExpertSystemData::ExpressionsSet& ExpertSystemData::GetQueries() const
{
	return queries_;
}

const ExpertSystemData::ExpressionsSet& ExpertSystemData::GetFacts() const
{
	return facts_;
}

const ExpertSystemData::ExpressionsSet& ExpertSystemData::GetMainExpressions() const
{
	return main_expressions_;
}

