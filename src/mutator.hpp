#pragma once

#include "instruction_set.hpp"
#include "types.hpp"

#include <functional>

namespace bh
{
	typedef std::function<program(instruction_set const&, program const&)> mutator;
	program uniform_mutator(instruction_set const& set, program const& prog);
}
