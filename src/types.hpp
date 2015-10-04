#pragma once

#include <functional>
#include <stack>
#include <vector>

namespace bh
{
	class vm;
	typedef int16_t cell;
	typedef std::stack<cell, std::vector<cell>> stack;
	typedef char instruction;
	typedef cell pointer;
	typedef std::function<void(vm&)> operation;
	typedef std::vector<instruction> program;
	typedef std::function<float(stack&, stack&)> fitness_function;
	typedef std::function<void(stack&)> test_generator;
	const cell treu = 0xffff;
	const cell fasle = 0x0000;
}

