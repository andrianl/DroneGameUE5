// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret/AITurret.h"
#include "Projectiles/TurretProjectile.h"
#include "Components/BoxComponent.h"
#include "Components/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AAITurret::AAITurret()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);

    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    SkeletalMeshComponent->SetupAttachment(RootComponent);

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(SceneComponent);

    CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AAITurret::Fire(const AActor *Target)
{
    if (IsValid(ProjectileClass) && IsValid(Target))
    {
        // Calculate the direction to the target.
        FVector StartLocation = ProjectileSpawnLocation;
        FVector TargetLocation = Target->GetActorLocation();

        FVector LaunchDirection = (TargetLocation - StartLocation).GetSafeNormal();;
     
        //const FVector SpawnLocation = GetActorLocation() + GetActorRotation().RotateVector(RandomMuzzleOffset);
        const FVector SpawnLocation = ProjectileSpawnLocation;

        FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

        // Configure parameters for spawning the projectile.
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        // Spawn the projectile and set its initial trajectory.
        ATurretProjectile *SpawnedProjectile = GetWorld()->SpawnActor<ATurretProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (IsValid(SpawnedProjectile))
        {
            UProjectileMovementComponent* ProjectileMovement = SpawnedProjectile->FindComponentByClass<UProjectileMovementComponent>();
            CollisionBox->IgnoreActorWhenMoving(SpawnedProjectile, true);
            // Set the projectile's initial direction.
            SpawnedProjectile->FireInDirection(LaunchDirection);
        }
    }
}

// Called when the game starts or when spawned
void AAITurret::BeginPlay()
{
    Super::BeginPlay();
    HealthComponent->OnHealthZeroOrBelow.AddDynamic(this, &AAITurret::OnHealthZeroOrBelowHandler);
}

// Called every frame
void AAITurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAITurret::OnHealthZeroOrBelowHandler()
{
    Destroy();
}
