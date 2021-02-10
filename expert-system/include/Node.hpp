#pragma once

#include <memory>
#include <utility>
#include <vector>

class IHashable {
public:
	virtual size_t GetHash() = 0;
};

template <typename T>
class IEquatable {
public:
	virtual bool Equals(const std::shared_ptr<T> &v) = 0;
};

class INode : public IHashable, public IEquatable<INode> {
public:
	enum State {
		False,
		True,
		Undetermined
	};

	virtual State EvaluateState() = 0;
};