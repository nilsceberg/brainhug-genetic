#include "vm.hpp"
#include "context.hpp"

#include <iostream>

using namespace bh;

vm::vm()
	: m_ip(0),
	  m_context(nullptr)
{
}

context* vm::switch_context(context* new_context)
{
	context* old_context = m_context;
	m_context = new_context;
	return old_context;
}

void vm::jump(pointer to)
{
	m_ip = to;
}

void vm::jump_relative(pointer offset)
{
	m_ip += offset;
}

pointer vm::get_ip()
{
	return m_ip;
}

void vm::step()
{
	instruction instr = fetch();
	std::cerr << "I:" << instr << std::endl;

	auto it = m_instruction_set.find(instr);
	if(it != m_instruction_set.end())
	{
		it->second(*this);
	}
}

instruction vm::fetch()
{
	return m_context->program[m_ip++];
}

void vm::push(cell c)
{
	m_context->stack.push(c);
}

cell vm::pop()
{
	cell c = m_context->stack.top();
	m_context->stack.pop();
	return c;
}

void vm::set_instruction_set(instruction_set const& set)
{
	m_instruction_set = set;
}

instruction_set const& vm::get_instruction_set() const
{
	return m_instruction_set;
}

