#ifndef AGGMAX_H
#define AGGMAX_H

#include "Agg.h"

namespace fuzzy
{
	template <class T>
	class AggMax: public Agg<T>
	{
	public:
		AggMax() {};
		virtual ~AggMax() {};
		virtual T Evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T AggMax<T>::Evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lv = l->Evaluate();
		T rv = r->Evaluate();
		return (lv>=rv)? lv : rv;
	}
}

#endif