// Copyright Epic Games, Inc. All Rights Reserved.

#include "DroneGameGameMode.h"
#include "DroneGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADroneGameGameMode::ADroneGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
