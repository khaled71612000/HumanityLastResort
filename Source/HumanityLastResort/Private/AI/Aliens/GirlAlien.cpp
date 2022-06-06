// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Aliens/GirlAlien.h"

void AGirlAlien::CallSetAlienNeedsValues()
{
	TArray<AlienNeedsValue*> NeedsValues;
	//AlienNeedsValue Eat{ {2, 7}, {50, 100} };
	//AlienNeedsValue Rest{ {2, 8}, {60, 100} };
	AlienNeedsValue Dance{ {4, 9}, {70, 100} };
	//NeedsValues.Add(&Eat);
	//NeedsValues.Add(&Rest);
	NeedsValues.Add(&Dance);

	SetAlienNeedsValues(NeedsValues);

}

void AGirlAlien::CallSetAlienAttributes()
{
	AlienAttributes AlienAttribs{
		{5, 10}, { 5, 10 }, { 5, 10 }, { 5, 10 }
	};
	SetAlienAttributes(AlienAttribs);

}