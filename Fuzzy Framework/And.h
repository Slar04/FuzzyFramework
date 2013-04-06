#ifndef AND_H
#define AND_H

#include "BinaryExpression.h"

namespace fuzzy
{
	template <class T>
	class And: public core::BinaryExpression<T>
	{
	public:
		virtual ~And() {};
	};
}

#endif