#ifndef FUZZYFACTORY_H
#define FUZZYFACTORY_H

#include "ExpressionFactory.h"
#include "Is.h"
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

using namespace core;

namespace fuzzy
{
	template <class T>
	class FuzzyFactory: public ExpressionFactory<T>
	{
	public:
		FuzzyFactory() {};
		FuzzyFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, MamdaniDefuzz<T>*);
		FuzzyFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, MamdaniDefuzz<T>*, SugenoDefuzz<T>*, SugenoConclusion<T>*);
		virtual ~FuzzyFactory();
		
		Expression<T>* NewNot(Expression<T>*);
		Expression<T>* NewIs(Is<T>*, Expression<T>*);
		Expression<T>* NewAnd(Expression<T>*, Expression<T>*);
		Expression<T>* NewOr(Expression<T>*, Expression<T>*);
		Expression<T>* NewThen(Expression<T>*, Expression<T>*);
		Expression<T>* NewAgg(Expression<T>*, Expression<T>*);
		Expression<T>* NewDefuzz(Expression<T>*, Expression<T>*, const T&, const T&, const T&);
        Expression<T>* NewSugeno(std::vector<const Expression<T>*>*);
        Expression<T>* NewNConclusion(std::vector<const Expression<T>*>*);

		void ChangeNot(Not<T>*);
		void ChangeAnd(And<T>*);
		void ChangeOr(Or<T>*);
		void ChangeThen(Then<T>*);
		void ChangeAgg(Agg<T>*);
		void ChangeDefuzz(MamdaniDefuzz<T>*);
		void ChangeSugeno(SugenoDefuzz<T>*);
		void ChangeConclusion(SugenoConclusion<T>*);

	private:
		UnaryShadowExpression<T>*  not;
		BinaryShadowExpression<T>* and;
		BinaryShadowExpression<T>* or;
		BinaryShadowExpression<T>* then;
		BinaryShadowExpression<T>* agg;
		BinaryShadowExpression<T>* defuzz;
        NaryShadowExpression<T>*   sugeno;
        NaryShadowExpression<T>*   conclusion;
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
		not        = new UnaryShadowExpression<T>(_not);
		and        = new BinaryShadowExpression<T>(_and);
		or         = new BinaryShadowExpression<T>(_or);
		then       = new BinaryShadowExpression<T>(_then);
		agg        = new BinaryShadowExpression<T>(_agg);
		defuzz     = new BinaryShadowExpression<T>(_defuzz);
	}

	template <class T>
	FuzzyFactory<T>::FuzzyFactory(
		Not<T>* _not,
		And<T>* _and,
		Or<T>* _or,
		Then<T>* _then,
		Agg<T>* _agg,
		MamdaniDefuzz<T>* _defuzz,
		SugenoDefuzz<T>* _sugeno,
		SugenoConclusion<T>* _conclusion
		)
	{
		not        = new UnaryShadowExpression<T>(_not);
		and        = new BinaryShadowExpression<T>(_and);
		or         = new BinaryShadowExpression<T>(_or);
		then       = new BinaryShadowExpression<T>(_then);
		agg        = new BinaryShadowExpression<T>(_agg);
		defuzz     = new BinaryShadowExpression<T>(_defuzz);
		sugeno     = new NaryShadowExpression<T>(_sugeno);
		conclusion = new NaryShadowExpression<T>(_conclusion);
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
	Expression<T>* FuzzyFactory<T>::NewNot(Expression<T>* o)
	{
		return NewUnary(not, o);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::NewIs(Is<T>* s, Expression<T>* o)
	{
		return NewUnary(s, o);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::NewAnd(Expression<T>* l, Expression<T>* r)
	{
		return NewBinary(and, l, r);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::NewOr(Expression<T>* l, Expression<T>* r)
	{
		return NewBinary(or, l, r);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::NewThen(Expression<T>* l, Expression<T>* r)
	{
		return NewBinary(then, l, r);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::NewAgg(Expression<T>* l, Expression<T>* r)
	{
		return NewBinary(agg, l, r);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::NewDefuzz(Expression<T>* l, Expression<T>* r, const T& min, const T& max, const T& step)
	{
		MamdaniDefuzz<T>* target = (MamdaniDefuzz<T>*) defuzz->GetTarget();	
		target->SetMin(min);
		target->SetMax(max);
		target->SetStep(step);

		return NewBinary(defuzz, l, r);
	}

	template <class T>
    Expression<T>* FuzzyFactory<T>::NewSugeno(std::vector<const Expression<T>*>* operands)
    {
        return NewNary(sugeno, operands);
    }

    template <class T>
    Expression<T>* FuzzyFactory<T>::NewNConclusion(std::vector<const Expression<T>*>* operands)
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
