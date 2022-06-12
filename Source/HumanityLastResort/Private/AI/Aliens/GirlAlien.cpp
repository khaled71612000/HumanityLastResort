// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Aliens/GirlAlien.h"

AGirlAlien::AGirlAlien()
{
	AlienType = 3;
}
void AGirlAlien::CallSetAlienNeedsValues()
{
	TArray<AlienNeedsValue*> NeedsValues;
	AlienNeedsValue Sleep{ {2, 7}, {50, 100} };
	AlienNeedsValue Eat{ {2, 7}, {50, 100} };
	AlienNeedsValue Dance{ {2, 7}, {50, 100} };
	AlienNeedsValue Workout{ {2, 7}, {50, 100} };
	AlienNeedsValue Drink{ {2, 8}, {60, 100} };
	AlienNeedsValue SweetTooth{ {4, 9}, {70, 100} };
	AlienNeedsValue Play{ {2, 7}, {50, 100} };

	NeedsValues.Add(&Sleep);
	NeedsValues.Add(&Eat);
	NeedsValues.Add(&Dance);
	NeedsValues.Add(&Workout);
	NeedsValues.Add(&Drink);
	NeedsValues.Add(&SweetTooth);
	NeedsValues.Add(&Play);

	SetAlienNeedsValues(NeedsValues);

}

void AGirlAlien::CallSetAlienAttributes()
{
	AlienAttributes AlienAttribs{
		{5, 10}, { 2, 2 }, { 5, 5 }, { 5, 5 }
	};
	SetAlienAttributes(AlienAttribs);

}