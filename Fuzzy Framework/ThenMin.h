#ifndef THENMIN_H
#define THENMIN_H

#include "Expression.h"
#include "Then.h"

namespace fuzzy
{
	template <class T>
	class ThenMin: public Then<T>
	{
	public:
		ThenMin() {};
		virtual ~ThenMin() {};
		virtual T Evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T ThenMin<T>::Evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lv = l->Evaluate();
		T rv = r->Evaluate();
		return (lv<=rv)? lv : rv;
	}
}

#endif