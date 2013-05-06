#ifndef UNARYEXPRESSIONMODEL_H
#define UNARYEXPRESSIONMODEL_H

#include "NullExpressionException.h"

namespace core
{
	template <class T>
	class UnaryExpressionModel: public UnaryExpression<T>, public Expression<T>
	{
	public:
		UnaryExpressionModel() {};
		UnaryExpressionModel(UnaryExpression<T>* operateur, Expression<T>* operande): operateur(operateur), operande(operande) {};
		virtual ~UnaryExpressionModel() {};

		virtual T Evaluate() const;
		virtual T Evaluate(Expression*) const;

	private:
		UnaryExpression<T>* operateur;
		Expression<T>* operande;
	};

	template <class T>
	T UnaryExpressionModel<T>::Evaluate() const
	{
		if (operande == NULL)
			throw new NullExpressionException("operande null");

		return Evaluate(operande);
	}

	template <class T>
	T UnaryExpressionModel<T>::Evaluate(Expression<T>* o) const
	{
		if (operateur == NULL)
			throw new NullExpressionException("operateur null");

		return operateur->Evaluate(o);
	}
}

#endif