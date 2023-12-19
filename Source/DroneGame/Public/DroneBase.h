// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DroneBase.generated.h"

UCLASS()
class DRONEGAME_API ADroneBase : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ADroneBase();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    // Function to handle drone movement
    UFUNCTION(BlueprintCallable, Category = "Drone")
    void MoveHorizontal(const FInputActionValue &Value);

    UFUNCTION(BlueprintCallable, Category = "Drone")
    void MoveVertical(const FInputActionValue &Value);

    // Function to handle drone rotation
    UFUNCTION(BlueprintCallable, Category = "Drone")
    void Rotate(const FInputActionValue &Value);

    class UHealthComponent *GetHealthComponent() const;

private:
    UFUNCTION()
    void OnCollisionBoxHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                           FVector NormalImpulse, const FHitResult &Hit);

protected:
    /* INPUTS */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputMappingContext *InputMapping;

    // UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    // class UInputAssetData* InputActions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputAction *InputMoveHorizontal;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputAction *InputMoveVertical;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputAction *InputRotate;

private:
    // Speed of the drone movement
    UPROPERTY(EditAnywhere, Category = "Drone")
    float MoveSpeed;

    // Speed of the drone rotation
    UPROPERTY(EditAnywhere, Category = "Drone")
    float RotationSpeed;

    // Scene component as the root for the drone
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone", meta = (AllowPrivateAccess = "true"))
    class USceneComponent *RootSceneComponent;

    // Collision component (box)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent *CollisionBox;

    // Mesh component for the drone (you may want to replace this with your own mesh)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone", meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *DroneMesh;

    UPROPERTY(VisibleAnywhere, Category = "Drone", meta = (AllowPrivateAccess = "true"))
    class UFloatingPawnMovement *MovementComponent;

    // Camera component for the drone
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone", meta = (AllowPrivateAccess = "true"))
    class UCameraComponent *DroneCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    class UHealthComponent *HealthComponent;
};
