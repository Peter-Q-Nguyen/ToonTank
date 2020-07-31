// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(GetRootComponent());
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	//Update TurretMesh rotation to face towards the LookAtTarget passed in from Child Classes.
	// TurretMesh->SetWorldRotation()...

	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);

}

void APawnBase::Fire()
{
	// GetProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location firing towards Rotation.
	if (ProjectileClass)
	{
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass,ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation() );
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	// Universal functionality
	// Play death effects particle, sound and camera shake.

	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());

	// Then do Child overrides---
	// PawnTurret - Inform GameModeTurret died then destroy self.

	// PawnTank - Inform GameMode Player died -> Then Hide all components && stop movement input.
}


