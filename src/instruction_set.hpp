#pragma once

#include "types.hpp"

#include <map>

namespace bh
{
	class vm;
	typedef std::map<instruction, operation> instruction_set;
	instruction_set operator|(
			instruction_set const&,
			instruction_set const&);

	namespace instruction_sets
	{
		instruction_set base();
	};
}
