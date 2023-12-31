// ProjectileBase.cpp

#include "Projectiles/ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>

#include "Drone/DroneBase.h"
#include "Components/HealthComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Set default values for projectile properties
    ProjectileSpeed = 1000.0f;
    Damage = 10;

    // Create and set up a box component for collision detection
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    // Create and set up a static mesh component for the projectile
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMesh->SetupAttachment(CollisionBox);

    // Create a projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = CollisionBox;
    ProjectileMovement->InitialSpeed = ProjectileSpeed;
    ProjectileMovement->MaxSpeed = ProjectileSpeed;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    // Bind the hit event
    CollisionBox->OnComponentHit.AddDynamic(this, &AProjectileBase::OnProjectileHit);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to initialize the projectile properties
void AProjectileBase::InitializeProjectile(float Speed, int32 DamageAmount, TSubclassOf<class UDamageType> DamageType)
{
    // Set the projectile properties based on the initialization parameters
    ProjectileSpeed = Speed;
    Damage = DamageAmount;
    DamageTypeClass = DamageType;

    // Update the projectile movement component with the new speed
    if (ProjectileMovement)
    {
        ProjectileMovement->InitialSpeed = ProjectileSpeed;
        ProjectileMovement->MaxSpeed = ProjectileSpeed;
    }
}

// Event called when the projectile hits something
void AProjectileBase::OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                                      FVector NormalImpulse, const FHitResult &Hit)
{
      // Check if OtherActor has a HealthComponent
        UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
        if (IsValid(HealthComponent))
        {
            // Add your specific logic here
            float DealedDamage = DealDamage(OtherActor);
            HealthComponent->TakeDamage(DealedDamage);
        }
        else
        {
            // Handle the case where HealthComponent is not present in OtherActor
            // Add alternative logic here if needed
        }

        Destroy();
}

UProjectileMovementComponent *AProjectileBase::GetProjectileComponent() const
{
    return ProjectileMovement;
}

float AProjectileBase::DealDamage(AActor *ActorToDealDamage)
{
    float DealedDamage = UGameplayStatics::ApplyDamage(ActorToDealDamage, Damage, nullptr, this, DamageTypeClass);

    return DealedDamage;
}
