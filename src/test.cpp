#include "vm.hpp"
#include "types.hpp"
#include "instruction_set.hpp"
#include "mutator.hpp"
#include "optimizer.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

int fibonacci(int i)
{
	int n1 = 1;
	int n2 = 1;
	if(i < 2)
		return 1;
	
	i --;
	while(i--)
	{
		int tmp = n1;
		n1 = n2;
		n2 = n1 + tmp;
	}
	return n2;
}

int main(int args, char** argv)
{
	srand(time(0));

	auto instruction_set = bh::instruction_sets::base();
	instruction_set.erase('a');
	instruction_set.erase('P');
	instruction_set[' '] = [](bh::vm&){}; // nop

	bh::vm vm;
	vm.silence_errors = true;
	vm.set_instruction_set(instruction_set);
	
	// addition
//	bh::optimizer optimizer(vm, bh::uniform_mutator,
//			[](bh::stack& stack)
//			{
//				stack.push(rand());
//				stack.push(rand());
//			},
//			[](bh::stack& in, bh::stack& out)
//			{
//				if(out.empty())
//					return .0f;
//
//				bh::cell a = in.top();
//				in.pop();
//				bh::cell b = in.top();
//				bh::cell result = out.top();
//				
//				return 1.f - ((float)std::abs((a+b) - result)) / std::abs((float)a+b);
//			});

	// fibonacci
	bh::optimizer optimizer(vm, bh::uniform_mutator,
			[](bh::stack& stack)
			{
				stack.push(rand() % 13 + 10);
			},
			[](bh::stack& in, bh::stack& out)
			{
				if(out.empty())
					return .0f;

				bh::cell actual = fibonacci(in.top());
				bh::cell result = out.top();
				
				return 1.f - ((float)std::abs(actual - result)) / (float)std::abs(actual);
			});

	optimizer.optimize(bh::program(), 1000000);
}
