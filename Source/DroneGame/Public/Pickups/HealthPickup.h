// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API AHealthPickup : public APickupBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHealthPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Implementation of the interface function
	virtual void ApplyPickupEffects_Implementation(AActor* ActorToApplyTo) override;

	// Health amount to heal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealingAmount;
};
