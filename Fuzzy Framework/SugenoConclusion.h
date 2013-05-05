#ifndef SUGENOCONCLUSION_H
#define SUGENOCONCLUSION_H

#include "NaryExpression.h"

namespace fuzzy
{
    template <class T>
    class SugenoConclusion : public NaryExpression<T>
    {
    public:
		SugenoConclusion(std::vector<T>* coeff):coeff(coeff) {};
        virtual ~SugenoConclusion() {};

        virtual T Evaluate(std::vector<const Expression<T>*>* operands) const;

    private:
		std::vector<T> *coeff;
    };

    template <class T>
    T SugenoConclusion<T>::Evaluate(std::vector<const Expression<T>*>* operands) const
    {
		std::vector<T>::const_iterator itcoef = coeff->begin();
		std::vector<const Expression<T>*>::const_iterator itexpr = operands->begin();
		T z = 0;

		// calcul de la somme des Zi
		for (; itexpr != operands->end() && itcoef != coeff->end(); itexpr++, itcoef++)
		{
			// evaluation de la règle courante
			T eval = (*itexpr)->Evaluate();

			// multiplication par le coefficient associé à cette règle
			z += (*itcoef) * eval;
		}

		return z;
    }
}

#endif
