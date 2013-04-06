#ifndef OR_H
#define OR_H

#include "BinaryExpression.h"

namespace fuzzy
{
	template <class T>
	class Or: public core::BinaryExpression<T>
	{
	public:
		virtual ~Or() {};
	};
}

#endif