#include "Expressions.hpp"

FactExpression::FactExpression(char fact)
		: fact_(fact)
{
}

BinaryExpression::BinaryExpression(Expression* left, BinaryOperator binaryOperator, Expression* right)
		: leftExpr(left), binaryOperator(binaryOperator), rightExpr(right)
{
}
