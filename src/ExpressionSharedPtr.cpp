#include <ExpressionSharedPtr.hpp>

ExpressionSharedPtr::ExpressionSharedPtr(Expression* expression)
: expression_(expression), reference_count_(new size_t(1))
{
}

ExpressionSharedPtr::ExpressionSharedPtr()
//: expression_(nullptr), reference_count_(new size_t(0))
{
}

ExpressionSharedPtr::ExpressionSharedPtr(const ExpressionSharedPtr& expressionSharedPtr)
{
	*this = expressionSharedPtr;
}

ExpressionSharedPtr& ExpressionSharedPtr::operator=(const ExpressionSharedPtr& expressionSharedPtr)
{
	if (this == &expressionSharedPtr)
		return *this;
	
	expression_ = expressionSharedPtr.expression_;
	reference_count_ = expressionSharedPtr.reference_count_;
	if (expression_ != nullptr)
		++(*reference_count_);
	
	return *this;
}

Expression* ExpressionSharedPtr::operator->() const
{
	return expression_;
}

Expression& ExpressionSharedPtr::operator*() const
{
	return *expression_;
}

ExpressionSharedPtr::~ExpressionSharedPtr()
{
	Cleanup();
}

void ExpressionSharedPtr::Cleanup()
{
	if (*reference_count_ == 0)
	{
		delete reference_count_;
		return;
	}
	--(*reference_count_);
	if (*reference_count_ == 0)
	{
		if (expression_ != nullptr)
			delete expression_;
		delete reference_count_;
	}
}

