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
		bh::program()
	};

	bool stop = false;

	bh::vm vm;

	bh::instruction_set extension;
	extension['z'] = [&stop](bh::vm&) { stop = true; };
	extension[0] = [&stop](bh::vm&) { stop = true; };

	vm.set_instruction_set(bh::instruction_sets::base() | extension);

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
		process.program = bh::program(program.begin(), program.end());
		process.program.push_back(0);
		//process.stack = bh::stack();
		vm.jump(0);

		stop = false;
		i = 0;
		while(!stop && i < 10000)
		{
			vm.step();
			std::cerr << "S:"; print_stack(process.stack); std::cerr << std::endl;
			++i;
		}

		if(i == 10000)
			std::cout << "... (didn't end)";
	}
}

