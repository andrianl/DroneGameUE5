// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

UCLASS()
class DRONEGAME_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to start spawning pickups
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void StartSpawning();

private:
	// Function to spawn a pickup
	void SpawnPickup();

	// Timer handle for pickup spawning
	FTimerHandle SpawnTimerHandle;

	// Class of the pickup to spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APickupBase> PickupClass;

	// Time between pickups
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	float TimeBetweenSpawns;

	// Box component to define the spawning area
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpawnArea;

	// Pointer to the spawned pickup
	UPROPERTY()
	class APickupBase* SpawnedPickup;

	// Function to get a random location within the spawn area
	FVector GetRandomSpawnLocation() const;
};
