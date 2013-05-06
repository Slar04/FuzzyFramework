#ifndef SUGENOTHEN_H
#define SUGENOTHEN_H

#include "Then.h"

namespace fuzzy
{
    template <class T>
    class SugenoThen : public Then<T>
    {
    public:
		SugenoThen():premiseValue(0) {};
        virtual ~SugenoThen() {};

        virtual T Evaluate(core::Expression<T>*, core::Expression<T>*) const;
        virtual T getPremiseValue();

    public:
        mutable T premiseValue;
    };

    template <class T>
    T SugenoThen<T>::Evaluate(core::Expression<T>* l, core::Expression<T>* r) const
    {
        premiseValue = l->Evaluate();

		return premiseValue * r->Evaluate();
    }

    template <class T>
    T SugenoThen<T>::getPremiseValue()
    {
        return premiseValue;
    }
}

#endif
