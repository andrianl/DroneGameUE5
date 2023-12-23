// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/ProjectileBase.h"
#include "TurretProjectile.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API ATurretProjectile : public AProjectileBase
{
	GENERATED_BODY()
	

public:
	UFUNCTION()
	void FireInDirection(const FVector& ShootDirection) const;
};
