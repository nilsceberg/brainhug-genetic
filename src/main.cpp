#include <iostream>
#include <vector>

#include "context.hpp"
#include "vm.hpp"
#include "instruction_set.hpp"

void print_stack(bh::stack& stack)
{
	if(stack.empty()) return;

	auto x = stack.top();
	stack.pop();
	print_stack(stack);
	std::cout << x << " ";
	stack.push(x);
}

int main()
{
	bh::context process =
	{
		bh::stack(), //std::vector<bh::cell>(256)),
		nullptr
	};

	bool halt = false;

	bh::vm vm;
	vm.register_operation(0, [&halt](bh::vm&) { halt = true; });
	bh::instruction_set::base(vm);

	vm.switch_context(&process);

	while(true)
	{
		std::string program;
		std::cout << "> ";
		std::cin >> program;
		process.program = program.c_str();
		//process.stack = bh::stack();
		vm.jump(0);

		halt = false;
		while(!halt)
		{
			vm.step();
			std::cout << "S:"; print_stack(process.stack); std::cout << std::endl;
		}
	}
}

