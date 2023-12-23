// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Rotate.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API UBTTask_Rotate : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UBTTask_Rotate(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector EnemyKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	class AAIController* Controller;
	class AAITurret* Turret;

	UPROPERTY(EditInstanceOnly)
	float ProjectileSpeed;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
};
