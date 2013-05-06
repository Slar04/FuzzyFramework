#ifndef NARYEXPRESSIONMODEL_H
#define NARYEXPRESSIONMODEL_H

#include "NullExpressionException.h"

namespace core
{
	template <class T>
	class NaryExpressionModel: public NaryExpression<T>, public Expression<T>
	{
	public:
		NaryExpressionModel() {};
		NaryExpressionModel(NaryExpression<T>* operateur, std::vector<const Expression<T>*>* operandes):operateur(operateur), operandes(operandes) {};
		virtual ~NaryExpressionModel() {};

		virtual T Evaluate() const;
		virtual T Evaluate(std::vector<const Expression<T>*>*) const;

	private:
		NaryExpression<T>* operateur;
		std::vector<const Expression<T>*>* operandes;
	};

	template <class T>
	T NaryExpressionModel<T>::Evaluate() const
	{
		if (operandes->empty()) 
			throw new NullExpressionException("operandes vector empty");

		return Evaluate(operandes);
	}

	template <class T>
	T NaryExpressionModel<T>::Evaluate(std::vector<const Expression<T>*>* operands) const
	{
		if (operateur == NULL)
			throw new NullExpressionException("ope null");

		return operateur->Evaluate(operands);
	}
}

#endif