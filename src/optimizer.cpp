#include "optimizer.hpp"
#include "types.hpp"
#include "context.hpp"

#include <iostream>

using namespace bh;

optimizer::optimizer(
		vm& vm,
		mutator mut,
		test_generator generator,
		fitness_function func)
	: m_vm(vm),
	  m_mutator(mut),
	  m_test_generator(generator),
	  m_fitness_function(func)
{
}

program optimizer::optimize(program seed, int generations)
{
	program best_program = seed;
	float best_score = evaluate_program(seed);
	std::cout << "initial score: " << best_score << std::endl;

	for(int gen = 0; gen<generations; ++gen)
	{
		auto program = m_mutator(m_vm.get_instruction_set(), best_program);
		float score = evaluate_program(program);
		//std::cout << std::string(program.begin(), program.end()) << ":" << score << std::endl;
		if(score > best_score)
		{
			best_program = program;
			best_score = score;
		}

		if(gen % 1000 == 0)
			std::cout << "gen " << gen << ", best score: " << best_score << std::endl;
	}

	std::cout << "best score: " << best_score << std::endl;
	std::string program_string(best_program.begin(), best_program.end());
	std::cout << "best program: " << program_string << std::endl;
	return best_program;
}

float optimizer::evaluate_program(program const& prog)
{
	float average = 0;
	
	for(int i=0; i<10; ++i)
	{
		stack start_stack;
		m_test_generator(start_stack);

		context ctx = {
			start_stack,
			prog
		};
		
		m_vm.switch_context(&ctx);
		m_vm.run();
		
		average += m_fitness_function(start_stack, ctx.stack);
	}
	return average / 10.f;
}

