#ifndef NOTMINUS_H
#define NOTMINUS_H

#include "Not.h"

namespace fuzzy
{
	template <class T>
	class NotMinus: public Not<T>
	{
	public:
		NotMinus() {};
		virtual ~NotMinus() {};
		virtual T Evaluate(core::Expression<T>*) const;
	};

	template <class T>
	T NotMinus<T>::Evaluate (core::Expression<T>* o) const
	{
		T m = -(o->Evaluate());
		return m;
	}
}

#endif