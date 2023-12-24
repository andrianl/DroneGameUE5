// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_Search.generated.h"

/**
 *
 */
UCLASS()
class DRONEGAME_API UBTService_Search : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UBTService_Search(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector EnemyKey;

	UPROPERTY(EditInstanceOnly)
	float Radius = 1000;

	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

	virtual void OnGameplayTaskActivated(UGameplayTask &Task) override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask &Task) override;
};
