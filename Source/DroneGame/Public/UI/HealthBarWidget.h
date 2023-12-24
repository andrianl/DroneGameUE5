// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Health")
    void UpdateHealthBar(float CurrentHealth, float MaxHealth);

protected:
    // Called when the widget is constructed
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthProgressBar;

    UPROPERTY()
    APawn* Player;
};
