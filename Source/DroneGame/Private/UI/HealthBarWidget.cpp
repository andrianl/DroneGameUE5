// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/HealthComponent.h"

void UHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    HealthProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthProgressBar")));

    if (IsValid(HealthProgressBar))
    {
        HealthProgressBar->SetPercent(1.0f);       
    }


   // UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>()

    Player = GetWorld()->GetFirstPlayerController()->GetPawn();

    UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>(); 
    if (IsValid(HealthComponent))
    {
        HealthComponent->OnHealthChanged.AddDynamic(this, &UHealthBarWidget::UpdateHealthBar);
    }
}

void UHealthBarWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
    float HealthPercentage = 0;
    if (FMath::IsNearlyEqual(CurrentHealth, MaxHealth))
    {
        HealthPercentage = 1.0F;
    }
    else
    {
        HealthPercentage = CurrentHealth / MaxHealth;
    }

    if (IsValid(HealthProgressBar))
    {
        HealthProgressBar->SetPercent(HealthPercentage);
    }
}