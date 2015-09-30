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

	auto it = m_operations.find(instr);
	if(it != m_operations.end())
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

void vm::register_operation(instruction instr, operation op)
{
	m_operations[instr] = op;
}

