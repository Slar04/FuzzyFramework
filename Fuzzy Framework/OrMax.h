#ifndef ORMAX_H
#define ORMAX_H

#include "Or.h"

namespace fuzzy
{
	template <class T>
	class OrMax: public Or<T>
	{
	public:
		OrMax() {};
		virtual ~OrMax() {};
		virtual T Evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T OrMax<T>::Evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		T lv = l->Evaluate();
		T rv = r->Evaluate();
		return (lv>=rv)? lv : rv;
	}
}

#endif