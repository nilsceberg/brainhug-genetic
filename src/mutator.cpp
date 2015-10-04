#include "mutator.hpp"

#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace bh;

instruction random_instruction(instruction_set const& set)
{
	int i = rand() % set.size();
	//return (set.begin() + i)->first;
	for(auto pair: set)
	{
		if(i-- == 0)
		{
			return pair.first;
		}
	}
	assert(false);
	return 0;
}

program bh::uniform_mutator(instruction_set const& set, program const& p_prog)
{
	program prog(p_prog);
	size_t i = std::rand() % (prog.size() + 1);
	if(i == prog.size())
	{
		prog.push_back(random_instruction(set));
	}
	else
	{
		prog[i] = random_instruction(set);
	}
	return prog;
}

