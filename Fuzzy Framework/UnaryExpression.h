#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

namespace core
{
	template <class T>
	class UnaryExpression
	{
	public:
		UnaryExpression() {};
		virtual ~UnaryExpression() {};

		virtual T Evaluate(Expression<T>*) const = 0;
	};
}

#endif