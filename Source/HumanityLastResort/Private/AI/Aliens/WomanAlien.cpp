// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Aliens/WomanAlien.h"

AWomanAlien::AWomanAlien()
{
	AlienType = 1;
}

void AWomanAlien::CallSetAlienNeedsValues()
{
	TArray<AlienNeedsValue*> NeedsValues;
	AlienNeedsValue Sleep{ {2, 7}, {50, 100} };
	AlienNeedsValue Eat{ {2, 7}, {50, 100} };
	AlienNeedsValue Dance{ {2, 7}, {50, 100} };
	AlienNeedsValue Workout{ {2, 7}, {50, 100} };
	AlienNeedsValue Drink{ {2, 8}, {60, 100} };
	AlienNeedsValue SweetTooth{ {4, 9}, {70, 100} };

	NeedsValues.Add(&Sleep);
	NeedsValues.Add(&Eat);
	NeedsValues.Add(&Dance);
	NeedsValues.Add(&Workout);
	NeedsValues.Add(&Drink);
	NeedsValues.Add(&SweetTooth);

	SetAlienNeedsValues(NeedsValues);

}

void AWomanAlien::CallSetAlienAttributes()
{
	AlienAttributes AlienAttribs{
		{5, 10}, { 5, 10 }, { 5, 10 }, { 5, 10 }
	};
	SetAlienAttributes(AlienAttribs);

}
