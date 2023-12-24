// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret/BTTask_InterpRotate.h"
#include <Turret/AITurret.h>
#include "AIController.h"

void UBTTask_InterpRotate::OnGameplayTaskActivated(UGameplayTask &Task)
{
}

EBTNodeResult::Type UBTTask_InterpRotate::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    AAITurret *Character = Cast<AAITurret>(OwnerComp.GetAIOwner()->GetPawn());
    if (IsValid(Character))
    {
        FRotator CurrentRotation = Character->GetActorRotation();
        FRotator NewRotation = FRotator{0.0f, CurrentRotation.Yaw + 90.0F, 0.0F};

        Character->SetActorRotation(FMath::Lerp(CurrentRotation, NewRotation, 0.005F));
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}