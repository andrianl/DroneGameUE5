// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InputMappingContext.h"
#include "InputAssetData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "HealthComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADroneBase::ADroneBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default values for movement and rotation
	MoveSpeed = 1000.0f;
	RotationSpeed = 100.0f;

	// Create a root scene component
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	// Create and set up a static mesh component for the drone
	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneMesh"));
	DroneMesh->SetupAttachment(RootSceneComponent);

	// Create a floating movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	// Create a camera component and attach it to the root component
	DroneCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DroneCamera"));
	DroneCamera->SetupAttachment(RootSceneComponent);

	// Set the default camera position and rotation
	DroneCamera->SetRelativeLocation(FVector(-500.0f, 0.0f, 200.0f));
	DroneCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// Create a collision box component and attach it to the root component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootSceneComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ADroneBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentHit.AddDynamic(this, &ADroneBase::OnCollisionBoxHit);
}

// Called every frame
void ADroneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADroneBase::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	// Get the player controller
	APlayerController *PC = Cast<APlayerController>(GetController());

	if (IsValid(PC))
	{
		// Get the local player subsystem
		UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

		if (IsValid(Subsystem))
		{
			// Clear out existing mapping, and add our mapping
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Subsystem!"), *GetNameSafe(this));
		}

		// Get the EnhancedInputComponent
		UEnhancedInputComponent *PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

		if (IsValid(PEI))
		{
			// Bind the actions
			PEI->BindAction(InputMoveHorizontal, ETriggerEvent::Triggered, this, &ADroneBase::MoveHorizontal);
			PEI->BindAction(InputMoveVertical, ETriggerEvent::Triggered, this, &ADroneBase::MoveVertical);
			PEI->BindAction(InputRotate, ETriggerEvent::Triggered, this, &ADroneBase::Rotate);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component!"), *GetNameSafe(this));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an PlayerController!"), *GetNameSafe(this));
	}
}

void ADroneBase::MoveHorizontal(const FInputActionValue &Value)
{
	auto ValueVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Display, TEXT("Horizontal movement X: %f. Y: %f."), ValueVector.X, ValueVector.Y);
}

void ADroneBase::MoveVertical(const FInputActionValue &Value)
{
	auto ValueVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Display, TEXT("Vertical movement X: %f. Y: %f."), ValueVector.X, ValueVector.Y);
}

void ADroneBase::Rotate(const FInputActionValue &Value)
{
	auto ValueVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Display, TEXT("Rotate movement X: %f. Y: %f."), ValueVector.X, ValueVector.Y);
}

UHealthComponent *ADroneBase::GetHealthComponent() const
{
	return HealthComponent;
}

void ADroneBase::OnCollisionBoxHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
								   FVector NormalImpulse, const FHitResult &Hit)
{
	UE_LOG(LogTemp, Display, TEXT("CollisionHit"));
}