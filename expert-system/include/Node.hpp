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