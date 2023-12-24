// Fill out your copyright notice in the Description page of Project Settings.

#include "Drone/DroneBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InputMappingContext.h"
#include "Inputs/InputAssetData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADroneBase::ADroneBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default values for movement and rotation
	// MoveSpeed = 1000.0f;
	// RotationSpeed = 100.0f;

	// Create a root scene component
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	// Create and set up a static mesh component for the drone
	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneMesh"));
	DroneMesh->SetupAttachment(RootSceneComponent);

	// Create a floating movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	// Create a camera component and attach it to the SpringArm
	DroneCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DroneCamera"));
	DroneCamera->SetupAttachment(DroneMesh);

	// Set the default camera position and rotation
	DroneCamera->SetRelativeLocation(FVector(-500.0f, 0.0f, 200.0f));
	DroneCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// Create a collision box component and attach it to the root component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootSceneComponent);

	DroneMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
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
			PEI->BindAction(InputRotate, ETriggerEvent::Triggered, this, &ADroneBase::RotationalMovement);
			PEI->BindAction(InputFire, ETriggerEvent::Triggered, this, &ADroneBase::Fire);
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

	constexpr float HorizontalSpeed = 500;

	// ��������� ��������� �������
	FVector2D MovementInput = Value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MovementInput.X) || !FMath::IsNearlyZero(MovementInput.Y))
	{
		FVector RightVector = GetActorRightVector();
		FVector ForwardVector = GetActorForwardVector();

		// ������� ����� ������ ������� �� ���������� �������
		FVector MovementDirection = RightVector * MovementInput.X + ForwardVector * (MovementInput.Y * -1);

		// ������� ������� �����
		AddMovementInput(MovementDirection.GetSafeNormal());
	}
}

void ADroneBase::MoveVertical(const FInputActionValue &Value)
{
	float VerticalMovementScale = Value.Get<float>();

	if (!FMath::IsNearlyZero(VerticalMovementScale))
	{
		FVector UpVector = FVector::UpVector;
		AddMovementInput(UpVector, VerticalMovementScale);
	}
}

void ADroneBase::RotationalMovement(const FInputActionValue &Value)
{
	// ��� ��������� �����

	constexpr float RotationalSpeed = 100;

	float RotationMovementScale = Value.Get<float>();

	if (!FMath::IsNearlyZero(RotationMovementScale))
	{
		float YawRotation = RotationMovementScale * RotationalSpeed * GetWorld()->GetDeltaSeconds();

		// ������� ��������� �����
		AddActorLocalRotation(FRotator(0.f, YawRotation, 0.f));
	}
}

void ADroneBase::Fire()
{
	if (IsValid(WeaponComponent))
	{
		WeaponComponent->Fire();
	}
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