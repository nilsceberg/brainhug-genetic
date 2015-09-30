#pragma once

#include "types.hpp"

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

		void register_operation(instruction instr, operation op);
	
	private:
		instruction fetch();

		pointer m_ip;
		context* m_context;
		
		std::map<instruction, operation> m_operations;
	};
}

