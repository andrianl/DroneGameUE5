// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"

UWeaponComponent::UWeaponComponent()
{
    // Set this component to be initialized when the game starts
    PrimaryComponentTick.bCanEverTick = false;

    // Set default values for ammo
    CurrentAmmo = 0;
    MaxAmmo = 30; // Set your desired default maximum ammo value
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    // Set initial ammo to maximum
    CurrentAmmo = MaxAmmo;
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Function to handle shooting
void UWeaponComponent::Shoot()
{
    if (CurrentAmmo > 0)
    {
        // Perform shooting logic here

        // Decrease ammo count
        CurrentAmmo--;

        // Trigger OnAmmoChanged event
        OnAmmoChanged.Broadcast();
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
