#pragma once

#include "types.hpp"
#include "mutator.hpp"
#include "vm.hpp"

namespace bh
{
	class optimizer final
	{
	public:
		optimizer(
				vm& vm,
				mutator mut,
				test_generator generator,
				fitness_function func);

		program optimize(program seed, int generations);
		
	private:
		float evaluate_program(program const& prog);

		vm& m_vm;
		mutator m_mutator;
		test_generator m_test_generator;
		fitness_function m_fitness_function;
	};
}
