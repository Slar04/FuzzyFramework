#ifndef EVALUATOR_H
#define EVALUATOR_H

namespace fuzzy
{
	template <class T>
	class Evaluator
	{
	public:
		typedef std::pair<std::vector<T>, std::vector<T>> Shape;

		Shape BuildShape(const T&, const T&, const T&, core::ValueModel<T>*, core::Expression<T>*) const;
		std::ostream& PrintShape(const Shape&) const;
	};

	template <class T>
	typename Evaluator<T>::Shape Evaluator<T>::BuildShape(const T& min, const T& max, const T& step, core::ValueModel<T>* v, core::Expression<T>* e) const
	{
		std::vector<T> x, y;
		T mem = v->Evaluate();

		for (T i = min; i <= max; i += step)
		{
			v->SetValue(i);
			x.push_back(i);
			y.push_back(e->Evaluate());
		}

		v->SetValue(mem);

		return Shape(x, y);
	}

	template <class T>
	typename std::ostream& Evaluator<T>::PrintShape(const Shape& s) const
	{
		std::ostream os;
		return os;
	}
}

#endif