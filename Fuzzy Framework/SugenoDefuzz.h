#ifndef SUGENODEFUZZ_H
#define SUGENODEFUZZ_H

#include "NaryExpression.h"

namespace fuzzy
{
    template <class T>
    class SugenoDefuzz : public core::NaryExpression<T>
    {
    public:
        SugenoDefuzz() {};
        virtual ~SugenoDefuzz() {};

        virtual T Evaluate(std::vector<const core::Expression<T>*>* operands) const;
    };

    template <class T>
    T SugenoDefuzz<T>::Evaluate(std::vector<const core::Expression<T>*>* operands) const
    {
		std::vector<const core::Expression<T>*>::const_iterator it;

		T num = 0;
		T denum = 0;

		// calcul somme des wi
		for (it = operands->begin(); it != operands->end(); it++)
		{
			core::BinaryExpressionModel<T>*  bem = (core::BinaryExpressionModel<T>*)  (*it);
			core::BinaryShadowExpression<T>* bse = (core::BinaryShadowExpression<T>*) bem->GetOpe();
			SugenoThen<T>*                   sth = (SugenoThen<T>*)                   bse->GetTarget();

			num   += (*it)->Evaluate();
			denum += sth->getPremiseValue();
		}

		if (denum != 0)
			return num/denum;
		else
			return 0;
    }
}

#endif
