#include "stdafx.h"

#include "NullExpressionException.h"
#include "AndMin.h"
#include "AndMult.h"
#include "OrMax.h"
#include "OrPlus.h"
#include "IsTriangle.h"
#include "NotMinus1.h"
#include "ThenMin.h"
#include "ValueModel.h"
#include "CogDefuzz.h"
#include "AggPlus.h"
#include "AggMax.h"
#include "SugenoThen.h"

#include "FuzzyFactory.h"

using namespace core;
using namespace fuzzy;

void testAndMin()
{
	AndMin<float> op;
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "AndMin(" << v1->Evaluate() << ", " << v2->Evaluate() << "): " << op.Evaluate(v1, v2) << std::endl;
}

void testAndMult()
{
	AndMult<float> op;
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "AndMult(" << v1->Evaluate() << ", " << v2->Evaluate() << "): " << op.Evaluate(v1, v2) << std::endl;
}

void testOrMax()
{
	OrMax<float> op;
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "OrMax(" << v1->Evaluate() << ", " << v2->Evaluate() << "): " << op.Evaluate(v1, v2) << std::endl;
}

void testOrPlus()
{
	OrPlus<float> op;
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "AndMult(" << v1->Evaluate() << ", " << v2->Evaluate() << "): " << op.Evaluate(v1, v2) << std::endl;
}

void testIsTriangle()
{
	IsTriangle<float> op(0.2f, 0.4f, 0.7f);
	ValueModel<float>* v1 = new ValueModel<float>(0.3f);
	ValueModel<float>* v2 = new ValueModel<float>(0.5f);
	std::cout << "IsTriangle(" << v1->Evaluate() << "): " << op.Evaluate(v1) << std::endl;
	std::cout << "IsTriangle(" << v2->Evaluate() << "): " << op.Evaluate(v2) << std::endl;
}

void testProf()
{
	//operators
	NotMinus1<float>        opNot;
	AndMin<float>           opAnd;
	OrMax<float>            opOr;
	ThenMin<float>          opThen;
	AggPlus<float>          opAgg;
	CogDefuzz<float>        opDefuzz;
	SugenoDefuzz<float>     opSugDefuzz;

	std::vector<float> coef;
	coef.push_back(1);
	coef.push_back(1);
	SugenoConclusion<float> opConclusion = SugenoConclusion<float>(&coef);

	//fuzzy expession factory
	FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz,&opSugDefuzz,&opConclusion);

	//membership function
	//service
	IsTriangle<float> poor(-5,0,5);
	IsTriangle<float> good(0,5,10);
	IsTriangle<float> excellent(5,10,15);
	//tips
	IsTriangle<float> cheap(0,5,10);
	IsTriangle<float> average(10,15,20);
	IsTriangle<float> generous(20,25,30);

	//values
	ValueModel<float> service(0);
	ValueModel<float> food(0);
	ValueModel<float> tips(0);

	Expression<float> *r =
		f.NewAgg(
			f.NewAgg(
				f.NewThen(
					f.NewIs(&poor, &service),
					f.NewIs(&cheap, &tips)
				),
				f.NewThen(
					f.NewIs(&good, &service),
					f.NewIs(&average, &tips)
				)
			),
			f.NewThen(
				f.NewIs(&excellent, &service),
				f.NewIs(&generous, &tips)
			)
		);

	//defuzzification
	Expression<float> *system = f.NewDefuzz(&tips, r, 0, 30, 1);

	//apply input
	float s;
	while(true)
	{
		std::cout << "service : ";
		std::cin >> s;
		service.SetValue(s);
		std::cout << "tips -> " << system->Evaluate() << std::endl;
	}
}

void testMamdani()
{
	//operators
	NotMinus1<float>        opNot;
	AndMin<float>           opAnd;
	OrMax<float>            opOr;
	ThenMin<float>          opThen;
	AggPlus<float>          opAgg;
	CogDefuzz<float>        opDefuzz;

	//fuzzy expession factory
	FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz);

	//membership function
	//service
	IsTriangle<float> poor(-5,0,5);
	IsTriangle<float> good(0,5,10);
	IsTriangle<float> excellent(5,10,15);
	//food
	IsTriangle<float> rancid(-5,0,5);
	IsTriangle<float> delicious(5,10,15);
	//tips
	IsTriangle<float> cheap(0,5,10);
	IsTriangle<float> average(10,15,20);
	IsTriangle<float> generous(20,25,30);

	//values
	ValueModel<float> service(0);
	ValueModel<float> food(0);
	ValueModel<float> tips(0);

	Expression<float> *r =
		f.NewAgg(
			f.NewAgg(
				f.NewThen(
					f.NewOr(
						f.NewIs(&poor, &service),
						f.NewIs(&rancid, &food)
					),
					f.NewIs(&cheap, &tips)
				),
				f.NewThen(
					f.NewIs(&good, &service),
					f.NewIs(&average, &tips)
				)
			),
			f.NewThen(
				f.NewOr(
					f.NewIs(&excellent, &service),
					f.NewIs(&delicious, &food)
				),
				f.NewIs(&generous, &tips)
			)
		);

	//defuzzification
	Expression<float> *system = f.NewDefuzz(&tips, r, 0, 25, 1);

	//apply input
	float s, fo;

	while(true)
	{
		std::cout << "service : ";
		std::cin >> s;
		service.SetValue(s);
		std::cout << "food : ";
		std::cin >> fo;
		food.SetValue(fo);
		std::cout << "tips -> " << system->Evaluate() << std::endl;
	}
}

void testSugenoDefuzz()
{
	//operators
	NotMinus1<float>    opNot;
	AndMin<float>       opAnd;
	OrMax<float>        opOr;
	SugenoThen<float>   opThen;
	AggMax<float>       opAgg;
	CogDefuzz<float>    opDefuzz;
	SugenoDefuzz<float> opSugDefuzz;

	std::vector<float> coef;
	coef.push_back(1);
	coef.push_back(1);
	coef.push_back(1);
	SugenoConclusion<float> opConclusion = SugenoConclusion<float>(&coef);

	//fuzzy expession factory
	FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz,&opSugDefuzz,&opConclusion);

	//membership function
	// service
	IsTriangle<float> poor(-5,0,5);
	IsTriangle<float> good(0,5,10);
	IsTriangle<float> excellent(5,10,15);
	// food
	IsTriangle<float> rancid(-5,0,5);
	IsTriangle<float> delicious(5,10,15);
	//values
	ValueModel<float> service(0);
	ValueModel<float> food(0);

	//output : ces variables vont stocker le résultat de SujenoConclusion (zi)
	std::vector<const Expression<float>*> SC_service_food;
	SC_service_food.push_back(&service);
	SC_service_food.push_back(&food);

	std::vector<const Expression<float>*> SC_service;
	SC_service.push_back(&service);

	//rules
	std::vector<const Expression<float>*> rules;

	rules.push_back(
		f.NewThen(
			f.NewOr(
				f.NewIs(&poor, &service),
				f.NewIs(&rancid, &food)
			),
			f.NewNConclusion(&SC_service_food)
		));

	rules.push_back(
		f.NewThen(
			f.NewIs(&good, &service),
			f.NewNConclusion(&SC_service)
		));

	rules.push_back(
		f.NewThen(
			f.NewOr(
				f.NewIs(&excellent, &service),
				f.NewIs(&delicious, &food)
			),
			f.NewNConclusion(&SC_service_food)
		));

	//defuzzification
	Expression<float> *system = f.NewSugeno(&rules);

	//apply input
	float s, foo;
	while(true)
	{
		std::cout << "service : ";
		std::cin >> s;
		service.SetValue(s);
		std::cout << "food : ";
		std::cin >> foo;
		food.SetValue(foo);
		std::cout << "tips -> " << system->Evaluate() << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//testAndMin();
	//testAndMult();
	//testOrMax();
	//testOrPlus();
	//testIsTriangle();

	//testProf();
	//testMamdani();
	testSugenoDefuzz();

	return 0;
}

