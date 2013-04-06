#ifndef ANDMULT_H
#define ANDMULT_H

#include "Expression.h"
#include "And.h"

namespace fuzzy
{
	template <class T>
	class AndMult: public And<T>
	{
	public:
		AndMult() {};
		virtual ~AndMult() {};
		virtual T Evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T AndMult<T>::Evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lv = l->Evaluate();
		T rv = r->Evaluate();
		return lv*rv;
	}
}

#endif