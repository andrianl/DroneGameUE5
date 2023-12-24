// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/AmmoPickup.h"
#include <Drone/DroneBase.h>
#include "Components/WeaponComponent.h"

// Sets default values
AAmmoPickup::AAmmoPickup()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Set a default ammo amount
	AmmoAmount = 10; // You can adjust this value
}

// Implementation of the interface function
void AAmmoPickup::ApplyPickupEffects_Implementation(AActor* ActorToApplyTo)
{
	Super::ApplyPickupEffects_Implementation(ActorToApplyTo);

	// Check if the actor is a drone (or a subclass of drone)
	if (IsValid(ActorToApplyTo) && ActorToApplyTo->IsA(ADroneBase::StaticClass()))
	{
		// Cast to drone and add ammo
		ADroneBase* Drone = Cast<ADroneBase>(ActorToApplyTo);
		if (IsValid(Drone))
		{
			// Add ammo to the drone
			if (IsValid(Drone->GetWeaponComponent()))
			{
				Drone->GetWeaponComponent()->AddAmmo(AmmoAmount);
			}
		}
	}
}