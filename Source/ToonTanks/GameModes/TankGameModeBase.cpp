// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawn/PawnTank.h"
#include "ToonTanks/Pawn/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	// get and store game win/lose conditions
	Super::BeginPlay();


	HandleGameStart();

}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret * DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		PlayerScore += DestroyedTurret->GetPoints();
		SetScore(PlayerScore);

		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}


int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}

void ATankGameModeBase::HandleGameStart()
{
	//initialise start countdown, turret activation, pawn check
	//call blueprint game start

	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();
	CreateScore();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
			&APlayerControllerBase::SetPlayerEnabledState,
			true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle,
			PlayerEnableDelegate,
			StartDelay,
			false
		);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{

	GameOver(PlayerWon);
}


