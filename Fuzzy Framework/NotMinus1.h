#ifndef NOTMINUS1_H
#define NOTMINUS1_H

#include "Not.h"

namespace fuzzy
{
	template <class T>
	class NotMinus1: public Not<T>
	{
	public:
		NotMinus1() {};
		virtual ~NotMinus1() {};
		virtual T Evaluate(core::Expression<T>*) const;
	};

	template <class T>
	T NotMinus1<T>::Evaluate (core::Expression<T>* o) const
	{
		T m = -(o->Evaluate());
		return m;
	}
}

#endif