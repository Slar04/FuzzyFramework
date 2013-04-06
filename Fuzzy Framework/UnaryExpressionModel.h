#ifndef UNARYEXPRESSIONMODEL_H
#define UNARYEXPRESSIONMODEL_H

namespace core
{
	template <class T>
	class UnaryExpressionModel: public UnaryExpression<T>, public Expression<T>
	{
	public:
		UnaryExpressionModel() {};
		UnaryExpressionModel(UnaryExpression<T>* ope, Expression<T>* operand): ope(ope), operand(operand) {};
		virtual ~UnaryExpressionModel() {};

		virtual T Evaluate() const;
		virtual T Evaluate(Expression*) const;

	private:
		UnaryExpression<T>* ope;
		Expression<T>* operand;
	};

	template <class T>
	T UnaryExpressionModel<T>::Evaluate() const
	{
		if (operand == NULL)
			throw new NullExpressionException("operand null");

		return Evaluate(operand);
	}

	template <class T>
	T UnaryExpressionModel<T>::Evaluate(Expression<T>* o) const
	{
		if (ope == NULL)
			throw new NullExpressionException("ope null");

		return ope->Evaluate(o);
	}
}

#endif