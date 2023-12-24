// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickupSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickups/PickupBase.h"
#include "Components/BoxComponent.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Create the box component for the spawn area
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;

	// Set default values
	PickupClass = nullptr;
	TimeBetweenSpawns = 10.0f; // Default time between spawns (in seconds)
	SpawnedPickup = nullptr;
}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();

	StartSpawning();
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Function to start spawning pickups
// Function to start spawning pickups
void APickupSpawner::StartSpawning()
{
    // Set a timer to spawn the first pickup
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APickupSpawner::SpawnPickup, TimeBetweenSpawns, false);
}

// Function to spawn a pickup
void APickupSpawner::SpawnPickup()
{
    UE_LOG(LogTemp, Warning, TEXT("Start Spawning Pickup"))
    if (PickupClass)
    {
        // If there is no spawned pickup or the previous pickup was destroyed
        if (!IsValid(SpawnedPickup) || SpawnedPickup->IsPendingKill())
        {
            // Get a random location within the spawn area
            FVector SpawnLocation = GetRandomSpawnLocation();

            // Spawn the pickup at the random location
            SpawnedPickup = GetWorld()->SpawnActor<APickupBase>(PickupClass, SpawnLocation, FRotator::ZeroRotator);

            if (SpawnedPickup)
            {
                UE_LOG(LogTemp, Warning, TEXT("Pickup is spawned"))
                // Optionally, you can customize the spawned pickup here

                // Set a timer for the next spawn
                GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APickupSpawner::SpawnPickup, TimeBetweenSpawns, false);
            }
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Failed Spawn"))
}

// Function to get a random location within the spawn area
FVector APickupSpawner::GetRandomSpawnLocation() const
{
    if (IsValid(SpawnArea))
    {
        // Get the bounds of the spawn area
        FVector Origin = GetActorLocation();
        FVector BoxExtent = SpawnArea->GetScaledBoxExtent();

        // Get a random point within the bounds
        return UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
    }

    return FVector::ZeroVector;
}


