#pragma once

#include "types.hpp"
#include "instruction_set.hpp"

#include <map>

namespace bh
{
	class context;
	class vm final
	{
	public:
		vm();

		context* switch_context(context* new_context);

		void jump(pointer to);
		void jump_relative(pointer offset);
		pointer get_ip();

		void push(cell c);
		cell pop();

		void step();

		void set_instruction_set(instruction_set const& set);
		instruction_set const& get_instruction_set() const;
	
	private:
		instruction fetch();

		pointer m_ip;
		context* m_context;
		
		instruction_set m_instruction_set;
	};
}

