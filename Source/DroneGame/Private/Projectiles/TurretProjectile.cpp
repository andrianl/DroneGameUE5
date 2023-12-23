// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/TurretProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ATurretProjectile::FireInDirection(const FVector& ShootDirection) const
{
	UProjectileMovementComponent* Projectile = GetProjectileComponent();
	Projectile->Velocity = ShootDirection * Projectile->InitialSpeed;
}
