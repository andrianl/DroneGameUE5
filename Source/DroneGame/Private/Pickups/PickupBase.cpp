// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickupBase.h"
#include "Components/SphereComponent.h"

// Sets default values
APickupBase::APickupBase()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create and set up a static mesh component for the pickup
    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    RootComponent = PickupMesh;

    // Create a collision sphere component and attach it to the root component
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
    Super::BeginPlay();

    // Bind the overlap event function
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnOverlapBegin);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Implementation of the interface function
void APickupBase::ApplyPickupEffects_Implementation(AActor* ActorToApplyTo)
{
    // Default implementation does nothing
    // Subclasses can override this function to provide specific pickup effects
}

// Function to handle collision events
void APickupBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapped actor is a pawn (or a subclass of pawn)
    if (IsValid(OtherActor) && OtherActor->IsA(APawn::StaticClass()))
    {
        // Apply pickup effects when overlapping with a pawn
        ApplyPickupEffects(OtherActor);

        // Destroy the pickup item after being picked up
        Destroy();
    }
}

