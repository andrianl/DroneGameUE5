// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupInterface.h"
#include "PickupBase.generated.h"

UCLASS()
class DRONEGAME_API APickupBase : public AActor, public IPickupInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APickupBase();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Implementation of the interface function
    virtual void ApplyPickupEffects_Implementation(class AActor *ActorToApplyTo) override;

    UFUNCTION()
    class USphereComponent* GetCollisionSphere() const;

    // Function to handle collision events
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void RestoreVisibilityAndCollision();

private:
    // Mesh component for the pickup
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *PickupMesh;

    // Collision component (sphere)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
    class USphereComponent *CollisionSphere;

    FTimerDelegate TimerDelegate;

    FTimerHandle TimerHandle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
    float TimeBeforeRespawn;
};
