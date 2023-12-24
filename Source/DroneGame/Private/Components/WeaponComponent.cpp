// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Projectiles/ProjectileBase.h"
#include "Camera/CameraComponent.h"

UWeaponComponent::UWeaponComponent()
{
    // Set this component to be initialized when the game starts
    PrimaryComponentTick.bCanEverTick = false;

    // Set default values for ammo
    bCanFire = true;
    CurrentAmmo = 0;
    MaxAmmo = 30; // Set your desired default maximum ammo value
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    OwnerActor = GetOwner();
    if (IsValid(OwnerActor))
    {
        OwnerCamera = OwnerActor->FindComponentByClass<UCameraComponent>();
    }
    else
    {
        // ������� �� �� ���������� ������, ������� �������� ������� �� �������
        UE_LOG(LogTemp, Warning, TEXT("Owner actor does not have a camera component."));
    }
    // Set initial ammo to maximum
    CurrentAmmo = MaxAmmo;

    GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UWeaponComponent::EnableFire, FireCooldown, false);
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::Fire()
{
    if (IsValid(ProjectileClass) && CurrentAmmo > 0 && bCanFire)
    {
        if (IsValid(OwnerActor) && IsValid(OwnerCamera))
        {
            FVector CameraLocation = OwnerCamera->GetComponentLocation();
            FRotator CameraRotation = OwnerCamera->GetComponentRotation();

            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = OwnerActor;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            AProjectileBase *Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, CameraLocation, CameraRotation, SpawnParams);

            if (IsValid(Projectile))
            {
                CurrentAmmo--;
                bCanFire = false;
                UE_LOG(LogTemp, Warning, TEXT("Drone Projectile Spawned"));
                GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UWeaponComponent::EnableFire, FireCooldown, false);
                OnAmmoChanged.Broadcast();
            }
        }
    }
}

// Function to add ammo
void UWeaponComponent::AddAmmo(const int32 Amount)
{
    CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, MaxAmmo);

    // Trigger OnAmmoChanged event
    OnAmmoChanged.Broadcast();
}

// Function to set maximum ammo
void UWeaponComponent::SetMaxAmmo(const int32 Max)
{
    MaxAmmo = Max;
    CurrentAmmo = FMath::Clamp(CurrentAmmo, 0, MaxAmmo);

    // Trigger OnAmmoChanged event
    OnAmmoChanged.Broadcast();
}

void UWeaponComponent::EnableFire()
{
    bCanFire = true;
}
