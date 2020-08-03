// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	APawnTank* PlayerTank;
	int32 TargetTurrets = 0;
	int32 PlayerScore = 0;
	APlayerControllerBase* PlayerControllerRef;

	int32 GetTargetTurretCount();
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);



public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateScore();
	UFUNCTION(BlueprintImplementableEvent)
	void SetScore(int32 Score);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;
};
