#pragma once

#include <memory>
#include <utility>
#include <vector>

class INode {
public:
	enum State {
		False,
		True,
		Undetermined
	};

	virtual State EvaluateState() = 0;
};

class UnaryOperation final : public INode {
public:
	enum Type {
		Not
	};

	explicit UnaryOperation(std::shared_ptr<INode> child)
			: child_(std::move(child)) {}

	State EvaluateState() override {
		if (child_ == nullptr) {
			throw std::logic_error("Child is null.");
		}

		State s = child_->EvaluateState();
		if (s == Undetermined) {
			return Undetermined;
		}

		switch (type_) {
			case Not:
				return (s == False) ? True : False;
			default:
				throw std::logic_error("Unknown binary operation type.");
		}
	}

private:
	Type type_;
	std::shared_ptr<INode> child_;
};

class BinaryOperation final : public INode {
public:
	enum Type {
		And,
		Or,
		Xor,
		Implication,
		Equivalence
	};

	BinaryOperation(Type type, std::shared_ptr<INode> left_child, std::shared_ptr<INode> right_child)
			: type_(type),
			  left_child_(std::move(left_child)),
			  right_child_(std::move(right_child)) {}

	State EvaluateState() override {
		if (left_child_ == nullptr) {
			throw std::logic_error("Left child is null.");
		} else if (right_child_ == nullptr) {
			throw std::logic_error("Right child is null.");
		}

		State lhs = left_child_->EvaluateState();
		State rhs = right_child_->EvaluateState();
		if (lhs == Undetermined || rhs == Undetermined) {
			return Undetermined;
		}

		switch (type_) {
			case And:
				return (lhs == True && rhs == True) ? True : False;
			case Or:
				return (lhs == True || rhs == True) ? True : False;
			case Xor:
				return (lhs == True ^ rhs == True) ? True : False;
			case Implication:
				return !(lhs == True && rhs == False) ? True : False;
			case Equivalence:
				return !(lhs == True ^ rhs == True) ? True : False;
			default:
				throw std::logic_error("Unknown binary operation type.");
		}
	}

private:
	Type type_;
	std::shared_ptr<INode> left_child_;
	std::shared_ptr<INode> right_child_;
};

class Fact final : public INode {
public:
	explicit Fact(char name)
			: state_(Undetermined),
			  name_(name) {}

	[[nodiscard]] char GetName() const {
		return name_;
	}

	State EvaluateState() override {
		return state_;
	}

private:
	INode::State state_;
	char name_;
};