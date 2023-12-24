// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthZeroOrBelowSignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DRONEGAME_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

    // Setters
    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetHealth(const float NewHealth);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetMaxHealth(const float NewMaxHealth);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(const float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Heal(const float HealAmount);

    // Getters
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealth() const;

    UFUNCTION(BlueprintPure, Category = "Health")
    float GetMaxHealth() const;

    // Event
    UPROPERTY(BlueprintAssignable,Category = "Health")
    FOnHealthChangedSignature OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category = "Health")
    FOnHealthZeroOrBelowSignature OnHealthZeroOrBelow;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    float MaxHealth;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    float CurrentHealth;
};
