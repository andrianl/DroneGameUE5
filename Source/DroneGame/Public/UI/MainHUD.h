// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:	
	AMainHUD();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEndGame();

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UHealthBarWidget> HealthBarWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> EndGameWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UCrosshairWidget> CrosshairWidgetClass;

private:
	UPROPERTY()
	class UHealthBarWidget* HealthBar;

	UPROPERTY()
	class UUserWidget* EndGameWidget;

	UPROPERTY()
	class UCrosshairWidget* CrosshairWidget;
};
