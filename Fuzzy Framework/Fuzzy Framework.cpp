#include "stdafx.h"

#include "NullExpressionException.h"
#include "AndMin.h"
#include "AndMult.h"
#include "OrMax.h"
#include "OrPlus.h"
#include "IsTriangle.h"
#include "NotMinus.h"
#include "ThenMin.h"
#include "ValueModel.h"
#include "CogDefuzz.h"
#include "AggPlus.h"
#include "AggMax.h"
#include "SugenoThen.h"

#include "FuzzyFactory.h"

void testProf()
{
	//operators
	fuzzy::NotMinus<float>        opNot;
	fuzzy::AndMin<float>           opAnd;
	fuzzy::OrMax<float>            opOr;
	fuzzy::ThenMin<float>          opThen;
	fuzzy::AggPlus<float>          opAgg;
	fuzzy::CogDefuzz<float>        opDefuzz;
	fuzzy::SugenoDefuzz<float>     opSugDefuzz;

	std::vector<float> coef;
	coef.push_back(1);
	coef.push_back(1);
	fuzzy::SugenoConclusion<float> opConclusion(&coef);

	//fuzzy expession factory
	fuzzy::FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz,&opSugDefuzz,&opConclusion);

	//membership function
	//service
	fuzzy::IsTriangle<float> poor(-5,0,5);
	fuzzy::IsTriangle<float> good(0,5,10);
	fuzzy::IsTriangle<float> excellent(5,10,15);
	//tips
	fuzzy::IsTriangle<float> cheap(0,5,10);
	fuzzy::IsTriangle<float> average(10,15,20);
	fuzzy::IsTriangle<float> generous(20,25,30);

	//values
	core::ValueModel<float> service(0);
	core::ValueModel<float> food(0);
	core::ValueModel<float> tips(0);

	core::Expression<float> *r =
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
	core::Expression<float> *system = f.NewDefuzz(&tips, r, 0, 30, 1);

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
	fuzzy::NotMinus<float>        opNot;
	fuzzy::AndMin<float>           opAnd;
	fuzzy::OrMax<float>            opOr;
	fuzzy::ThenMin<float>          opThen;
	fuzzy::AggPlus<float>          opAgg;
	fuzzy::CogDefuzz<float>        opDefuzz;

	//fuzzy expession factory
	fuzzy::FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz);

	//membership function
	//service
	fuzzy::IsTriangle<float> poor(-5,0,5);
	fuzzy::IsTriangle<float> good(0,5,10);
	fuzzy::IsTriangle<float> excellent(5,10,15);
	//food
	fuzzy::IsTriangle<float> rancid(-5,0,5);
	fuzzy::IsTriangle<float> delicious(5,10,15);
	//tips
	fuzzy::IsTriangle<float> cheap(0,5,10);
	fuzzy::IsTriangle<float> average(10,15,20);
	fuzzy::IsTriangle<float> generous(20,25,30);

	//values
	core::ValueModel<float> service(0);
	core::ValueModel<float> food(0);
	core::ValueModel<float> tips(0);

	core::Expression<float> *r =
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
	core::Expression<float> *system = f.NewDefuzz(&tips, r, 0, 25, 1);

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
	fuzzy::NotMinus<float>     opNot;
	fuzzy::AndMin<float>       opAnd;
	fuzzy::OrMax<float>        opOr;
	fuzzy::SugenoThen<float>   opThen;
	fuzzy::AggMax<float>       opAgg;
	fuzzy::CogDefuzz<float>    opDefuzz;
	fuzzy::SugenoDefuzz<float> opSugDefuzz;

	std::vector<float> coef;
	coef.push_back(1);
	coef.push_back(1);
	coef.push_back(1);
	fuzzy::SugenoConclusion<float> opConclusion(&coef);

	//fuzzy expession factory
	fuzzy::FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz,&opSugDefuzz,&opConclusion);

	//membership function
	// service
	fuzzy::IsTriangle<float> poor(-5,0,5);
	fuzzy::IsTriangle<float> good(0,5,10);
	fuzzy::IsTriangle<float> excellent(5,10,15);
	// food
	fuzzy::IsTriangle<float> rancid(-5,0,5);
	fuzzy::IsTriangle<float> delicious(5,10,15);
	//values
	core::ValueModel<float> service(0);
	core::ValueModel<float> food(0);

	//output : ces variables vont stocker le résultat de SujenoConclusion (zi)
	std::vector<const core::Expression<float>*> SC_service_food;
	SC_service_food.push_back(&service);
	SC_service_food.push_back(&food);

	std::vector<const core::Expression<float>*> SC_service;
	SC_service.push_back(&service);

	//rules
	std::vector<const core::Expression<float>*> rules;

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
	core::Expression<float> *system = f.NewSugeno(&rules);

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
	//testProf();
	testMamdani();
	//testSugenoDefuzz();

	return 0;
}

