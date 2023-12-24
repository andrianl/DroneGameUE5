// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HealthPickup.h"
#include "Components/SphereComponent.h"
#include "Drone/DroneBase.h"
#include "Components/HealthComponent.h"

// Sets default values
AHealthPickup::AHealthPickup()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Set default healing amount
	HealingAmount = 50.0f;
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();

	// Bind the overlap event function
	GetCollisionSphere()->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnOverlapBegin);
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Implementation of the interface function
void AHealthPickup::ApplyPickupEffects_Implementation(AActor* ActorToApplyTo)
{
	// Check if the overlapped actor is a drone
	ADroneBase* Drone = Cast<ADroneBase>(ActorToApplyTo);
	if (IsValid(Drone))
	{
		// Heal the drone
		if (IsValid(Drone->GetHealthComponent()))
		{
			Drone->GetHealthComponent()->Heal(HealingAmount);
		}
	}
}
