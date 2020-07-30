// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	// get and store game win/lose conditions

}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	//check what actor died, if turret, tally, if player-> go to lose condition
}


void ATankGameModeBase::HandleGameStart()
{
	//initialise start countdown, turret activation, pawn check
	//call blueprint game start

}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// see if player killed all turrets and show win result
	// otherwise show lose
	// call blueprint game over.
}


