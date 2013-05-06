#ifndef MAMDANIDEFUZZ_H
#define MAMDANIDEFUZZ_H

#include "BinaryExpression.h"
#include "Evaluator.h"

namespace fuzzy
{
	template <class T>
	class MamdaniDefuzz: public core::BinaryExpression<T>
	{
	public:
		typedef std::pair<std::vector<T>, std::vector<T>> Shape;

		MamdaniDefuzz():min(0), max(0), step(0) {};
		MamdaniDefuzz(const T& min, const T& max, const T& step): min(min), max(max), step(step) {};
		~MamdaniDefuzz() {};

		virtual void SetMin(const T& _min)   { min = _min; }
		virtual void SetMax(const T& _max)   { max = _max; }
		virtual void SetStep(const T& _step) { step = _step; }

		virtual T Evaluate(core::Expression<T>*, core::Expression<T>*) const;

	protected:
		virtual T Defuzz(const Shape&) const = 0;

	private:
		T min, max, step;
	};

	template <class T>
	T MamdaniDefuzz<T>::Evaluate(core::Expression<T>* l, core::Expression<T>* r) const
	{
		Evaluator<T> e;
		Evaluator<T>::Shape s = e.BuildShape(min, max, step, (core::ValueModel<T>*) l, r);

		return Defuzz(s);
	}
}

#endif