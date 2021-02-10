#pragma once

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
			: type_(type) {
		if (left_child == nullptr) {
			throw std::logic_error("Left child is null.");
		} else if (right_child == nullptr) {
			throw std::logic_error("Right child is null.");
		}

		left_child_ = std::move(left_child);
		right_child_ = std::move(right_child);
	}

	State EvaluateState() override {
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

	[[nodiscard]] Type GetType() const {
		return type_;
	}

	[[nodiscard]] const std::shared_ptr<INode> &GetLeftChild() const {
		return left_child_;
	}

	[[nodiscard]] const std::shared_ptr<INode> &GetRightChild() const {
		return right_child_;
	}

private:
	Type type_;
	std::shared_ptr<INode> left_child_;
	std::shared_ptr<INode> right_child_;
};