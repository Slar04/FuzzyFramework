#ifndef ANDMIN_H
#define ANDMIN_H

#include "And.h"

namespace fuzzy
{
	template <class T>
	class AndMin: public And<T>
	{
	public:
		AndMin() {};
		virtual ~AndMin() {};
		virtual T Evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T AndMin<T>::Evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lv = l->Evaluate();
		T rv = r->Evaluate();
		return (lv<=rv)? lv : rv;
	}
}

#endif