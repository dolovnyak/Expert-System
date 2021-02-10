#include <gtest/gtest.h>

#include "Fact.hpp"
#include "UnaryOperation.hpp"
#include "BinaryOperation.hpp"

class NodeEqualityTests : public ::testing::Test {
public:
	static void CheckEquality(INode *a, INode *b, bool is_equals) {
		std::shared_ptr<INode> ln(a);
		std::shared_ptr<INode> rn(b);
		ASSERT_EQ(a->Equals(rn), is_equals);
	}

	[[nodiscard]] static INode *GetMockFact() {
		return new Fact('A');
	}

	[[nodiscard]] static INode *GetMockUnaryOperation() {
		auto child = std::shared_ptr<INode>(new Fact('A'));
		return new UnaryOperation(UnaryOperation::Not, child);
	}

	[[nodiscard]] static INode *GetMockBinaryOperation() {
		auto left_child = std::shared_ptr<INode>(new Fact('A'));
		auto right_child = std::shared_ptr<INode>(new Fact('A'));
		return new BinaryOperation(BinaryOperation::Or, left_child, right_child);
	}
};

//TEST_F(NodeEqualityTests, NullptrEqualNullptr_True) {
//	CheckEquality(nullptr, nullptr, true);
//}
//
//TEST_F(NodeEqualityTests, NullptrEqualFact_False) {
//	CheckEquality(nullptr, new Fact('A'), false);
//}
//
//TEST_F(NodeEqualityTests, NullptrEqualUnaryOperation_False) {
//	auto child = std::shared_ptr<INode>(new Fact('A'));
//	CheckEquality(nullptr, new UnaryOperation(UnaryOperation::Not, child), false);
//}
//
//TEST_F(NodeEqualityTests, NullptrEqualBinaryOperation_False) {
//	auto left_child = std::shared_ptr<INode>(new Fact('A'));
//	auto right_child = std::shared_ptr<INode>(new Fact('A'));
//	CheckEquality(nullptr, new BinaryOperation(BinaryOperation::And, left_child, right_child), false);
//}

// nullptr
TEST_F(NodeEqualityTests, FactEqualNullptr_False) {
	CheckEquality(GetMockFact(), nullptr, false);
}

TEST_F(NodeEqualityTests, UnaryOperationEqualNullptr_False) {
	CheckEquality(GetMockUnaryOperation(), nullptr, false);
}

TEST_F(NodeEqualityTests, BinaryOperationEqualNullptr_False) {
	CheckEquality(GetMockBinaryOperation(), nullptr, false);
}

// Fact
TEST_F(NodeEqualityTests, FactEqualFact_True) {
	CheckEquality(GetMockFact(), GetMockFact(), true);
}

TEST_F(NodeEqualityTests, FactEqualFact_False) {
	CheckEquality(new Fact('A'), new Fact('B'), false);
}

TEST_F(NodeEqualityTests, FactEqualUnaryOperation_False) {
	CheckEquality(GetMockFact(), GetMockUnaryOperation(), false);
}

TEST_F(NodeEqualityTests, FactEqualBinaryOperation_False) {
	CheckEquality(GetMockFact(), GetMockBinaryOperation(), false);
}

// UnaryOperation
TEST_F(NodeEqualityTests, UnaryOperationEqualUnaryOperation_True) {
	CheckEquality(GetMockUnaryOperation(), GetMockUnaryOperation(), true);
}

TEST_F(NodeEqualityTests, UnaryOperationEqualUnaryOperation_False) {
	auto f1 = std::shared_ptr<INode>(new Fact('A'));
	auto f2 = std::shared_ptr<INode>(new Fact('B'));

	auto uo1 = new UnaryOperation(UnaryOperation::Not, f1);
	auto uo2 = new UnaryOperation(UnaryOperation::Not, f2);

	CheckEquality(uo1, uo2, false);
}

TEST_F(NodeEqualityTests, UnaryOperationEqualFact_False) {
	CheckEquality(GetMockUnaryOperation(), GetMockFact(), false);
}

TEST_F(NodeEqualityTests, UnaryOperationEqualBinaryOperation_False) {
	CheckEquality(GetMockUnaryOperation(), GetMockBinaryOperation(), false);
}

// BinaryOperation
TEST_F(NodeEqualityTests, BinaryOperationEqualBinaryOperation_True) {
	CheckEquality(GetMockBinaryOperation(), GetMockBinaryOperation(), true);
}

TEST_F(NodeEqualityTests, BinaryOperationEqualBinaryOperation_False) {
	auto f1 = std::shared_ptr<INode>(new Fact('A'));
	auto f2 = std::shared_ptr<INode>(new Fact('B'));

	auto bo1 = new BinaryOperation(BinaryOperation::Or, f1, f2);
	auto bo2 = new BinaryOperation(BinaryOperation::Or, f1, f1);

	CheckEquality(bo1, bo2, false);
}

TEST_F(NodeEqualityTests, BinaryOperationEqualFact_False) {
	CheckEquality(GetMockBinaryOperation(), GetMockFact(), false);
}

TEST_F(NodeEqualityTests, BinaryOperationEqualUnaryOperation_False) {
	CheckEquality(GetMockBinaryOperation(), GetMockUnaryOperation(), false);
}