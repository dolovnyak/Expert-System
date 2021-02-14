#pragma once

#include "Expressions/Expression.hpp"

class ExpressionSharedPtr
{
public:
	ExpressionSharedPtr();
	ExpressionSharedPtr(Expression *expression);
	ExpressionSharedPtr(const ExpressionSharedPtr& expressionSharedPtr);
	ExpressionSharedPtr& operator=(const ExpressionSharedPtr& expressionSharedPtr);
	~ExpressionSharedPtr();
	
	Expression* operator->() const;
	Expression& operator*() const;
	
private:
	Expression *expression_ = nullptr;
	size_t *reference_count_ = new size_t(0);
	
	void Cleanup();
};
