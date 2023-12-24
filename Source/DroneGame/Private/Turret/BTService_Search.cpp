// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret/BTService_Search.h"
#include "Drone/DroneBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/KismetSystemLibrary.h>

UBTService_Search::UBTService_Search(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    NodeName = "Search For Enemy";
    EnemyKey.AddObjectFilter(this, EnemyKey.SelectedKeyName, AActor::StaticClass());
}

void UBTService_Search::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    AAIController *Controller = Cast<AAIController>(OwnerComp.GetOwner());
    if (IsValid(Controller))
    {
        APawn *Turret = Controller->GetPawn();
        if (IsValid(Turret))
        {
            FVector Start = Turret->GetActorLocation();
            FHitResult Hit;

            if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, Start, Radius,
                                                                  {UEngineTypes::ConvertToObjectType(ECC_Pawn)}, false, {}, EDrawDebugTrace::ForDuration, Hit, true))
            {

                ADroneBase *Enemy = Cast<ADroneBase>(Hit.GetActor());
                if (IsValid(Enemy))
                {
                    // Controller->GetBlackboardComponent()->SetValueAsObject(EnemyKey.SelectedKeyName, Enemy);
                    Controller->GetBlackboardComponent()->SetValueAsObject(FName{TEXT("Enemy")}, Enemy);
                }
            }
            else
            {
                ADroneBase *Enemy = nullptr;
                Controller->GetBlackboardComponent()->SetValueAsObject(FName{TEXT("Enemy")}, Enemy);
            }
        }
    }
}

void UBTService_Search::OnGameplayTaskActivated(UGameplayTask &Task)
{
}

void UBTService_Search::OnGameplayTaskDeactivated(UGameplayTask &Task)
{
}