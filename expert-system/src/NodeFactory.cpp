#include "NodeFactory.hpp"

std::shared_ptr<INode> NodeFactory::GetNode(BinaryOperation::Type type)
{
	// TODO
	switch (type) {
		case BinaryOperation::And:
		case BinaryOperation::Or:
		case BinaryOperation::Xor:
		case BinaryOperation::Implication:
		case BinaryOperation::Equivalence:
			return std::shared_ptr<INode>(new BinaryOperation(type, nullptr, nullptr));
		default:
			throw std::logic_error("Type is out of range");
	}
}
