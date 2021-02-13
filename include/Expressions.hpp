#pragma once

#include <vector>

enum BinaryOperator
{
	AND = 0,
	OR,
	XOR,
	IMPLIES,
	MUTUAL_IMPLIES
};

enum UnaryOperator
{
	NOT = 0
};

class Expression
{
public:
	Expression() = default;
};

class UnaryExpression : public Expression
{
	Expression *expr;
	UnaryOperator unaryOperator;
};

class BinaryExpression : public Expression
{
public:
	BinaryExpression(Expression *left, BinaryOperator binaryOperator, Expression *right);

private:
	Expression *leftExpr;
	BinaryOperator binaryOperator;
	Expression *rightExpr;
};

class FactExpression : public Expression
{
public:
	FactExpression(char fact);

private:
	char fact_;
};
