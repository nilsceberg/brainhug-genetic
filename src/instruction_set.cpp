#include "instruction_set.hpp"
#include "vm.hpp"
#include "context.hpp"

#include <iostream>

using namespace bh;

instruction_set bh::operator|(
		instruction_set const& first,
		instruction_set const& second)
{
	instruction_set set(first);
	for(auto it = second.cbegin(); it != second.cend(); ++it)
	{
		set[it->first] = it->second;
	}
	return set;
}

instruction_set instruction_sets::base()
{
	instruction_set set;
	// push and pop
	for(int i='0'; i <= '9'; ++i)
	{
		set[i] = [i](bh::vm& vm) { vm.push(i - '0'); };
	}
	for(int i='A'; i <= 'F'; ++i)
	{
		set[i] = [i](bh::vm& vm) { vm.push(i - 'A' + 10); };
	}

	// combination of stack values
	set[':'] = [](bh::vm& vm) {
			cell b = vm.pop();
			cell a = vm.pop();
			vm.push(b | (a << 4));
		};
	set[';'] = [](bh::vm& vm) {
			cell n = vm.pop();
			cell result = 0;
			for (int i=0; i<n; ++i)
				result = result | (vm.pop() << (i*4));
			vm.push(result);
		};


	// arithmetic
	set['+'] = [](bh::vm& vm) { vm.push(vm.pop() + vm.pop()); };
	set['-'] = [](bh::vm& vm) { vm.push(vm.pop() - vm.pop()); };
	set['*'] = [](bh::vm& vm) { vm.push(vm.pop() * vm.pop()); };
	set['/'] = [](bh::vm& vm) { vm.push(vm.pop() / vm.pop()); };
	set['i'] = [](bh::vm& vm) { vm.push(vm.pop() + 1); };
	set['d'] = [](bh::vm& vm) { vm.push(vm.pop() - 1); };

	// io
	set['P'] = [](bh::vm& vm) { std::cout << vm.pop() << std::endl; };
	set['a'] = [](bh::vm& vm) { std::cout << (char)vm.pop(); };

	// jumps
	set['J'] = [](bh::vm& vm) { vm.jump_relative(vm.pop()); };
	set['j'] = [](bh::vm& vm) { vm.jump(vm.pop()); };
	set['c'] = [](bh::vm& vm) {
			pointer to = vm.pop();
			vm.push(vm.get_ip());
			std::cerr << "jumping to " << to << std::endl;
			vm.jump(to);
		};
	set['R'] = [](bh::vm& vm) {
			cell return_value = vm.pop();
			vm.jump(vm.pop());
			vm.push(return_value);
		};
	set['r'] = [](bh::vm& vm) {
			vm.jump(vm.pop());
		};
	set['?'] = [](bh::vm& vm) { // conditional relative
			pointer to = vm.pop();
			if (vm.pop())
				vm.jump_relative(to);
		};
	set['!'] = [](bh::vm& vm) { // conditional absolute
			pointer to = vm.pop();
			if (vm.pop())
				vm.jump(to);
		};

	// logic
	set['='] = [](bh::vm& vm) {
		   vm.push(vm.pop() == vm.pop() ? bh::treu : bh::fasle); };
	set['<'] = [](bh::vm& vm) {
		   vm.push(vm.pop() < vm.pop() ? bh::treu : bh::fasle); };
	set['>'] = [](bh::vm& vm) {
		   vm.push(vm.pop() > vm.pop() ? bh::treu : bh::fasle); };
	set['&'] = [](bh::vm& vm) { vm.push(vm.pop() & vm.pop()); };
	set['|'] = [](bh::vm& vm) { vm.push(vm.pop() | vm.pop()); };
	set['x'] = [](bh::vm& vm) { vm.push(vm.pop() ^ vm.pop()); };
	set['n'] = [](bh::vm& vm) { vm.push(~vm.pop()); };

	// stack manipulation
	set['@'] = [](bh::vm& vm) {
			int n = vm.pop() - 1;
			cell top = vm.pop();

			stack tmp;
			for (int i=0; i<n; ++i)
				tmp.push(vm.pop());

			vm.push(top);

			for (int i=0; i<n; ++i)
			{
				vm.push(tmp.top());
				tmp.pop();
			}
		};
	set['"'] = [](bh::vm& vm) {
			int n = vm.pop();
			std::vector<cell> tmp;
			tmp.reserve(n);
			for (int i=0; i<n; ++i)
				tmp.push_back(vm.pop());
			
			for (int i=0; i<n; ++i)
				vm.push(tmp[tmp.size() - i - 1]);
			for (int i=0; i<n; ++i)
				vm.push(tmp[tmp.size() - i - 1]);
		};
	set['\''] = [](bh::vm& vm) {
			cell val = vm.pop();
			vm.push(val);
			vm.push(val);
		};
	set['p'] = [](bh::vm& vm) { vm.pop(); };

	return set;
}

