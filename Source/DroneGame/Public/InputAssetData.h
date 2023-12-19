// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputAssetData.generated.h"

/**
 *
 */
UCLASS()
class DRONEGAME_API UInputAssetData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction *InputMoveHorizontal;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction *InputMoveVertical;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction *InputRotate;
};
