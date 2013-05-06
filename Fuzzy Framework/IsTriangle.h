#ifndef ISTRIANGLE_H
#define ISTRIANGLE_H

#include "Is.h"

namespace fuzzy
{
	template <class T>
	class IsTriangle: public Is<T>
	{
	public:
		IsTriangle()  {};
		IsTriangle(T min, T mid, T max): min(min), mid(mid), max(max) {};
		virtual ~IsTriangle() {};
		virtual T Evaluate(core::Expression<T>*) const;

	private:
		T min, mid, max;
	};

	template <class T>
	T IsTriangle<T>::Evaluate (core::Expression<T>* value) const
	{
		T v = value->Evaluate();

		if (v <= min || v >= max)
			return 0;

		return v <= mid ? (v - min) / (mid - min) : (max - v) / (max - mid);
	}
}

#endif