#ifndef THEN_H
#define THEN_H

#include "BinaryExpression.h"

namespace fuzzy
{
	template <class T>
	class Then: public core::BinaryExpression<T>
	{
	public:
		virtual ~Then() {};
	};
}

#endif