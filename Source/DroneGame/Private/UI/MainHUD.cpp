// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "UI/HealthBarWidget.h"
#include "Components/HealthComponent.h"
#include "UI/CrosshairWidget.h"

AMainHUD::AMainHUD()
{
}

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(HealthBarWidgetClass))
	{
		HealthBar = CreateWidget<UHealthBarWidget>(GetWorld(), HealthBarWidgetClass);

		if (IsValid(HealthBar))
		{
			HealthBar->AddToViewport();
		}
	}

	if (IsValid(CrosshairWidgetClass))
	{
		CrosshairWidget = CreateWidget<UCrosshairWidget>(GetWorld(), CrosshairWidgetClass);

		if (IsValid(CrosshairWidget))
		{
			CrosshairWidget->AddToViewport();
		}
	}

	APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
	if (IsValid(HealthComponent))
	{
		HealthComponent->OnHealthZeroOrBelow.AddDynamic(this, &AMainHUD::OnEndGame);
	}
}

void AMainHUD::OnEndGame()
{
	if (IsValid(EndGameWidgetClass))
	{
		EndGameWidget = CreateWidget<UUserWidget>(GetWorld(), EndGameWidgetClass);

		if (IsValid(EndGameWidget))
		{
			EndGameWidget->AddToViewport();
		}
	}
}
