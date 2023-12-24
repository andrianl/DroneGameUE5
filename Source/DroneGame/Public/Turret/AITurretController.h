// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITurretController.generated.h"

/**
 *
 */
UCLASS()
class DRONEGAME_API AAITurretController : public AAIController
{
	GENERATED_BODY()

public:
	AAITurretController();

	UFUNCTION()
	void SetupPerceptionSystem();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent *AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent *BlackboardComponent;
};
