#ifndef ISTRIANGLE_H
#define ISTRIANGLE_H

#include "UnaryExpression.h"
#include "Expression.h"
#include "Is.h"

namespace fuzzy
{
	template <class T>
	class IsTriangle: public Is<T>
	{
	public:
		IsTriangle()  {};
		IsTriangle(T _min, T _mid, T _max): min(_min), mid(_mid), max(_max) {};
		virtual ~IsTriangle() {};
		virtual T Evaluate(core::Expression<T>*) const;

	private:
		T min;
		T mid;
		T max;
	};

	template <class T>
	T IsTriangle<T>::Evaluate (core::Expression<T>* o) const
	{
		T v = o->Evaluate();

		if(v > min && v < mid)
			return (v - min) / (mid - min);
		if (v == mid)
			return 1;
		if(v > mid && v < max)
			return (max - v) / (max - mid);
		
		return 0;
	}
}

#endif