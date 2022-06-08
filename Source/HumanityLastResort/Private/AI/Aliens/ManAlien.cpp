// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Aliens/ManAlien.h"

AManAlien::AManAlien()
{
	AlienType = 0;
}

void AManAlien::CallSetAlienNeedsValues()
{
	TArray<AlienNeedsValue*> NeedsValues;
	//AlienNeedsValue Eat{ {2, 7}, {50, 100} };
	//AlienNeedsValue Rest{ {2, 8}, {60, 100} };
	AlienNeedsValue Dance{ {1, 2}, {7, 10} };
	//NeedsValues.Add(&Eat);
	//NeedsValues.Add(&Rest);
	NeedsValues.Add(&Dance);

	SetAlienNeedsValues(NeedsValues);

}

void AManAlien::CallSetAlienAttributes()
{
	AlienAttributes AlienAttribs{
		{5, 10}, { 5, 10 }, { 1, 1 }, { 1, 1 }
	};
	SetAlienAttributes(AlienAttribs);

}
