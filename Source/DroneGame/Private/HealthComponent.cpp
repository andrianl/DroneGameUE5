// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.
    // You can turn these features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    MaxHealth = 100.0f; // Default max health
    CurrentHealth = MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UHealthComponent::SetHealth(const float NewHealth)
{
    CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);
}

void UHealthComponent::SetMaxHealth(const float NewMaxHealth)
{
    MaxHealth = FMath::Max(NewMaxHealth, 0.0f);
    CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);
}

void UHealthComponent::TakeDamage(const float DamageAmount)
{
    if (DamageAmount > 0.0F && CurrentHealth > 0.0F)
    {
        CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0F, MaxHealth);
        OnHealthChanged.Broadcast(CurrentHealth);
    }
}

void UHealthComponent::Heal(const float HealAmount)
{
    if (HealAmount > 0.0F && CurrentHealth > 0.0F)
    {
        CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
        OnHealthChanged.Broadcast(CurrentHealth);
    }
}

float UHealthComponent::GetHealth() const
{
    return CurrentHealth;
}

float UHealthComponent::GetMaxHealth() const
{
    return MaxHealth;
}
