// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret/BTTask_Fire.h"
#include <Turret/BTTask_Rotate.h>
#include "AIController.h"
#include <Turret/AITurret.h>

UBTTask_Fire::UBTTask_Fire(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Fire";
}

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
	AAIController *Controller = Cast<AAIController>(OwnerComp.GetOwner());

	if (IsValid(Controller))
	{
		AAITurret *Turret = Cast<AAITurret>(Controller->GetPawn());

		if (IsValid(Turret))
		{
			APawn *Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			;

			Turret->Fire(Pawn);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

void UBTTask_Fire::OnGameplayTaskActivated(UGameplayTask &Task)
{
}