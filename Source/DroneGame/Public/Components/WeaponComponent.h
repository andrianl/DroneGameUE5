// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoChangedSignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DRONEGAME_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UWeaponComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    // ������� ��� �������
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void Fire();

    // Function to add ammo
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void AddAmmo(const int32 Amount);

    // Function to set maximum ammo
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void SetMaxAmmo(const int32 Max);

    // Function to get current ammo count
    UFUNCTION(BlueprintPure, Category = "Weapon")
    int32 GetAmmo() const { return CurrentAmmo; }

    // Function to get maximum ammo count
    UFUNCTION(BlueprintPure, Category = "Weapon")
    int32 GetMaxAmmo() const { return MaxAmmo; }

    // Event triggered when ammo changes
    UPROPERTY(BlueprintAssignable, Category = "Weapon")
    FOnAmmoChangedSignature OnAmmoChanged;

private:
    // Current ammo count
    UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    int32 CurrentAmmo;

    // Maximum ammo count
    UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    int32 MaxAmmo;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    float FireCooldown;

    // ����� ��� ���������� ����� ��������
    bool bCanFire;

    FTimerHandle FireTimerHandle;

    // ������� ����� ��� ��������� ����� ������������
    UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class AProjectileBase> ProjectileClass;

    UPROPERTY()
    AActor *OwnerActor;

    UPROPERTY()
    class UCameraComponent *OwnerCamera;

    UFUNCTION()
    void EnableFire();
};
