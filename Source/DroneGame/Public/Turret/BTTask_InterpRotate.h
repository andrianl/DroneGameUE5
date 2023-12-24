// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_RotateToFaceBBEntry.h"
#include "BTTask_InterpRotate.generated.h"

/**
 *
 */
UCLASS()
class DRONEGAME_API UBTTask_InterpRotate : public UBTTask_RotateToFaceBBEntry
{
	GENERATED_BODY()

	virtual void OnGameplayTaskActivated(UGameplayTask &Task) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
