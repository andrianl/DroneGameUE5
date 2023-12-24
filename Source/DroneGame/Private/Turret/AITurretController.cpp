// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret/AITurretController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAITurretController::AAITurretController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAITurretController::SetupPerceptionSystem()
{
}
