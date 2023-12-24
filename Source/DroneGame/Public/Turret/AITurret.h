// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AITurret.generated.h"

UCLASS()
class DRONEGAME_API AAITurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAITurret();

	UFUNCTION(BlueprintCallable)
	void Fire(const AActor *Target);

	UFUNCTION()
	void OnHealthZeroOrBelowHandler();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	USceneComponent *SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent *SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATurretProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, Category = Projectile)
	FVector ProjectileSpawnLocation;
};
