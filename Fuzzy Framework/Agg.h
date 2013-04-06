#ifndef AGG_H
#define AGG_H

#include "BinaryExpression.h"

namespace fuzzy
{
	template <class T>
	class Agg: public core::BinaryExpression<T>
	{
	public:
		virtual ~Agg() {};
	};
}

#endif