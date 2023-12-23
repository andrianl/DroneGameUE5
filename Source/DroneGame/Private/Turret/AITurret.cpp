// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret/AITurret.h"
#include "Projectiles/TurretProjectile.h"

// Sets default values
AAITurret::AAITurret()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);

    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    SkeletalMeshComponent->SetupAttachment(RootComponent);
}

void AAITurret::Fire(const AActor* Target)
{
    if (IsValid(ProjectileClass) && IsValid(Target))
    {
        // Calculate the direction to the target.
        FVector LaunchDirection = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();

        // Define the spawn location for the projectile with a randomized offset.
        const FVector RandomMuzzleOffset = FMath::VRand() * 100.0F; // Adjust the multiplier as needed
        const FVector SpawnLocation = GetActorLocation() + GetActorRotation().RotateVector(RandomMuzzleOffset);

        // Define the spawn rotation for the projectile.
        FRotator SpawnRotation = LaunchDirection.Rotation();
        SpawnRotation.Pitch += 10.0F;

        // Configure parameters for spawning the projectile.
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        // Spawn the projectile and set its initial trajectory.
        ATurretProjectile* SpawnedProjectile = GetWorld()->SpawnActor<ATurretProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (IsValid(SpawnedProjectile))
        {
            // Set the projectile's initial direction.
            SpawnedProjectile->FireInDirection(LaunchDirection);
        }
    }
}

// Called when the game starts or when spawned
void AAITurret::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AAITurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

