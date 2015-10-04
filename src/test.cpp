#include "vm.hpp"
#include "types.hpp"
#include "instruction_set.hpp"
#include "mutator.hpp"
#include "optimizer.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

int main(int args, char** argv)
{
	srand(0);//time(0));

	auto instruction_set = bh::instruction_sets::base();
	instruction_set.erase('a');
	instruction_set.erase('P');
	instruction_set[' '] = [](bh::vm&){}; // nop

	bh::vm vm;
	vm.silence_errors = true;
	vm.set_instruction_set(instruction_set);
	
	bh::optimizer optimizer(vm, bh::uniform_mutator,
			[](bh::stack& stack)
			{
				stack.push(rand());
				stack.push(rand());
			},
			[](bh::stack& in, bh::stack& out)
			{
				if(out.empty())
					return .0f;

				bh::cell a = in.top();
				in.pop();
				bh::cell b = in.top();
				bh::cell result = out.top();
				
				return 1.f - ((float)std::abs((a+b) - result)) / std::abs((float)a+b);
			});

	optimizer.optimize(bh::program(), 10000);
}
