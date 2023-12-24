// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret/BTTask_Rotate.h"
#include "Drone/DroneBase.h"
#include "Turret/AITurret.h"
#include "Turret/AITurretController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/KismetMathLibrary.h>

UBTTask_Rotate::UBTTask_Rotate(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    NodeName = "Rotate";
    EnemyKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Rotate, EnemyKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_Rotate::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    bNotifyTick = true;

    Controller = Cast<AAIController>(OwnerComp.GetOwner());
    Turret = Cast<AAITurret>(Controller->GetPawn());

    if (IsValid(Controller) && IsValid(Turret))
    {
        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Failed;
}

void UBTTask_Rotate::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    // Get the enemy from the blackboard
    ADroneBase *Enemy = Cast<ADroneBase>(Controller->GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Enemy"))));

    if (IsValid(Enemy))
    {
        // Calculate prediction rotation for the turret
        FVector TurretLocation = Turret->GetActorLocation();
        FVector PredictedEnemyLocation = Enemy->GetActorLocation() + (Enemy->GetVelocity() * DeltaSeconds);
        FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(TurretLocation, PredictedEnemyLocation);

        // Set the turret's rotation without modifying pitch or roll
        Turret->SetActorRotation(FRotator{0.0f, TargetRotation.Yaw, 0.0f});
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    else
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
}

void UBTTask_Rotate::OnGameplayTaskActivated(UGameplayTask &Task)
{
}