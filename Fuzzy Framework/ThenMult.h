#ifndef THENMULT_H
#define THENMULT_H

#include "Expression.h"
#include "Then.h"

namespace fuzzy
{
	template <class T>
	class ThenMult: public Then<T>
	{
	public:
		ThenMult() {};
		virtual ~ThenMult() {};
		virtual T Evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T ThenMult<T>::Evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lv = l->Evaluate();
		T rv = r->Evaluate();
		return lv*rv;
	}
}

#endif