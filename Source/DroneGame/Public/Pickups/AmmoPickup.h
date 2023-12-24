// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API AAmmoPickup : public APickupBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AAmmoPickup();

	// Implementation of the interface function
	virtual void ApplyPickupEffects_Implementation(AActor* ActorToApplyTo) override;

	// Additional property to set the amount of ammo to provide
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	int32 AmmoAmount;
};
