// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class DRONEGAME_API AProjectileBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AProjectileBase();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to initialize the projectile properties
    UFUNCTION(BlueprintCallable, Category = "Projectile")
    void InitializeProjectile(float Speed, int32 Damage, TSubclassOf<class UDamageType> DamageTypeClass);

    // Event called when the projectile hits something
    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                         FVector NormalImpulse, const FHitResult &Hit);

    // Getter function for the damage type
    UFUNCTION(BlueprintPure, Category = "Projectile")
    TSubclassOf<class UDamageType> GetDamageType() const { return DamageTypeClass; }

    // Getter function for the damage amount
    UFUNCTION(BlueprintPure, Category = "Projectile")
    int32 GetDamage() const { return Damage; }

    UFUNCTION(BlueprintPure, Category = "Projectile")
    float DealDamage(AActor *ActorToDealDamage);

private:
    // Speed of the projectile
    UPROPERTY(EditAnywhere, Category = "Projectile")
    float ProjectileSpeed;

    // Amount of damage the projectile deals
    UPROPERTY(EditAnywhere, Category = "Projectile")
    int32 Damage;

    // Damage type of the projectile
    UPROPERTY(EditAnywhere, Category = "Projectile")
    TSubclassOf<class UDamageType> DamageTypeClass;

    // Box component for collision detection
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent *CollisionBox;

    // Mesh component for the projectile
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *ProjectileMesh;

    // Projectile movement component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
    class UProjectileMovementComponent *ProjectileMovement;
};
