#pragma once

#include <functional>
#include <stack>
#include <vector>

namespace bh
{
	class vm;
	typedef uint16_t cell;
	typedef std::stack<cell, std::vector<cell>> stack;
	typedef char instruction;
	typedef unsigned int pointer;
	typedef std::function<void(vm&)> operation;
	const cell treu = 0xffff;
	const cell fasle = 0x0000;
}

