#pragma once

#include <exception>

namespace bh
{
	class stack_error : public std::runtime_error
	{
	public:
		stack_error()
			: std::runtime_error("stack is empty")
		{}
	};
}
