#ifndef FUZZYFACTORY_H
#define FUZZYFACTORY_H

#include "ExpressionFactory.h"
#include "Not.h"
#include "And.h"
#include "Or.h"
#include "Then.h"
#include "Agg.h"
#include "MamdaniDefuzz.h"
#include "SugenoDefuzz.h"
#include "SugenoConclusion.h"
#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "NaryShadowExpression.h"

namespace fuzzy
{
	template <class T>
	class FuzzyFactory: public core::ExpressionFactory<T>
	{
	public:
		FuzzyFactory() {};
		FuzzyFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, MamdaniDefuzz<T>*);
		FuzzyFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, SugenoDefuzz<T>*, SugenoConclusion<T>*);
		virtual ~FuzzyFactory();
		
		core::Expression<T>* NewNot(core::Expression<T>*);
		core::Expression<T>* NewIs(Is<T>*, core::Expression<T>*);
		core::Expression<T>* NewAnd(core::Expression<T>*, core::Expression<T>*);
		core::Expression<T>* NewOr(core::Expression<T>*, core::Expression<T>*);
		core::Expression<T>* NewThen(core::Expression<T>*, core::Expression<T>*);
		core::Expression<T>* NewAgg(core::Expression<T>*, core::Expression<T>*);
		core::Expression<T>* NewDefuzz(core::Expression<T>*, core::Expression<T>*, const T&, const T&, const T&);
        core::Expression<T>* NewSugeno(std::vector<const core::Expression<T>*>*);
        core::Expression<T>* NewNConclusion(std::vector<const core::Expression<T>*>*);

		void ChangeNot(Not<T>*);
		void ChangeAnd(And<T>*);
		void ChangeOr(Or<T>*);
		void ChangeThen(Then<T>*);
		void ChangeAgg(Agg<T>*);
		void ChangeDefuzz(MamdaniDefuzz<T>*);
		void ChangeSugeno(SugenoDefuzz<T>*);
		void ChangeConclusion(SugenoConclusion<T>*);

	private:
		core::UnaryShadowExpression<T>*  not;
		core::BinaryShadowExpression<T>* and;
		core::BinaryShadowExpression<T>* or;
		core::BinaryShadowExpression<T>* then;
		core::BinaryShadowExpression<T>* agg;
		core::BinaryShadowExpression<T>* defuzz;
        core::NaryShadowExpression<T>*   sugeno;
        core::NaryShadowExpression<T>*   conclusion;
	};

	template <class T>
	FuzzyFactory<T>::FuzzyFactory(
		Not<T>* _not,
		And<T>* _and,
		Or<T>* _or,
		Then<T>* _then,
		Agg<T>* _agg,
		MamdaniDefuzz<T>* _defuzz
		)
	{
		not        = new core::UnaryShadowExpression<T>(_not);
		and        = new core::BinaryShadowExpression<T>(_and);
		or         = new core::BinaryShadowExpression<T>(_or);
		then       = new core::BinaryShadowExpression<T>(_then);
		agg        = new core::BinaryShadowExpression<T>(_agg);
		defuzz     = new core::BinaryShadowExpression<T>(_defuzz);
	}

	template <class T>
	FuzzyFactory<T>::FuzzyFactory(
		Not<T>* _not,
		And<T>* _and,
		Or<T>* _or,
		Then<T>* _then,
		Agg<T>* _agg,
		SugenoDefuzz<T>* _sugeno,
		SugenoConclusion<T>* _conclusion
		)
	{
		not        = new core::UnaryShadowExpression<T>(_not);
		and        = new core::BinaryShadowExpression<T>(_and);
		or         = new core::BinaryShadowExpression<T>(_or);
		then       = new core::BinaryShadowExpression<T>(_then);
		agg        = new core::BinaryShadowExpression<T>(_agg);
		sugeno     = new core::NaryShadowExpression<T>(_sugeno);
		conclusion = new core::NaryShadowExpression<T>(_conclusion);
	}

	template <class T>
	FuzzyFactory<T>::~FuzzyFactory()
	{
		delete not;
		delete and;
		delete or;
		delete then;
		delete agg;
		delete defuzz;
		delete sugeno;
		delete conclusion;
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::NewNot(core::Expression<T>* o)
	{
		return NewUnary(not, o);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::NewIs(Is<T>* s, core::Expression<T>* o)
	{
		return NewUnary(s, o);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::NewAnd(core::Expression<T>* l, core::Expression<T>* r)
	{
		return NewBinary(and, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::NewOr(core::Expression<T>* l, core::Expression<T>* r)
	{
		return NewBinary(or, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::NewThen(core::Expression<T>* l, core::Expression<T>* r)
	{
		return NewBinary(then, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::NewAgg(core::Expression<T>* l, core::Expression<T>* r)
	{
		return NewBinary(agg, l, r);
	}

	template <class T>
	core::Expression<T>* FuzzyFactory<T>::NewDefuzz(core::Expression<T>* l, core::Expression<T>* r, const T& min, const T& max, const T& step)
	{
		MamdaniDefuzz<T>* target = (MamdaniDefuzz<T>*) defuzz->GetTarget();	
		target->SetMin(min);
		target->SetMax(max);
		target->SetStep(step);

		return NewBinary(defuzz, l, r);
	}

	template <class T>
    core::Expression<T>* FuzzyFactory<T>::NewSugeno(std::vector<const core::Expression<T>*>* operands)
    {
        return NewNary(sugeno, operands);
    }

    template <class T>
    core::Expression<T>* FuzzyFactory<T>::NewNConclusion(std::vector<const core::Expression<T>*>* operands)
    {
        return NewNary(conclusion, operands);
    }

	template <class T>
	void FuzzyFactory<T>::ChangeNot(Not<T>* o)
	{
		not->SetTarget(o);
	}

	template <class T>
	void FuzzyFactory<T>::ChangeAnd(And<T>* o)
	{
		and->SetTarget(o);
	}

	template <class T>
	void ChangeOr(Or<T>* o)
	{
		or->SetTarget(o);
	}

	template <class T>
	void FuzzyFactory<T>::ChangeThen(Then<T>* o)
	{
		then->SetTarget(o);
	}

	template <class T>
	void FuzzyFactory<T>::ChangeAgg(Agg<T>* o)
	{
		agg->SetTarget(o);
	}

	template <class T>
	void FuzzyFactory<T>::ChangeDefuzz(MamdaniDefuzz<T>* o)
	{
		defuzz->SetTarget(o);
	}

	template <class T>
	void FuzzyFactory<T>::ChangeSugeno(SugenoDefuzz<T>* o)
	{
		sugeno->SetTarget(o);
	}

	template <class T>
	void FuzzyFactory<T>::ChangeConclusion(SugenoConclusion<T>* o)
	{
		conclusion->SetTarget(o);
	}
}

#endif
