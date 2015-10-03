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
	std::cerr << x << " ";
	stack.push(x);
}

int main(int args, char** argv)
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

	// push all arguments to stack
	for(int i=1; i<args; ++i)
	{
		process.stack.push(atoi(argv[i]));
	}

	int i = 0;
	while(!std::cin.eof())
	{
		std::string program;
		std::cerr << "> ";
		std::cin >> program;
		process.program = program.c_str();
		//process.stack = bh::stack();
		vm.jump(0);

		halt = false;
		i = 0;
		while(!halt && i < 10000)
		{
			vm.step();
			std::cerr << "S:"; print_stack(process.stack); std::cerr << std::endl;
			++i;
		}

		if(i == 10000)
			std::cout << "... (didn't end)";
	}
}

