// Fill out your copyright notice in the Description page of Project Settings.


#include "TankyPawn.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Kismet/KismetMathLibrary.h"
#include <Camera/CameraComponent.h>
#include "Tanki.h"


// Sets default values
ATankyPawn::ATankyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch  = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}



// Called when the game starts or when spawned
void ATankyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentMoveFowardAxis = FMath::Lerp(CurrentMoveFowardAxis, TargetMoveForwardAxis, MovementSmoothness);

	FVector CurrentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector MovePosition = CurrentLocation+ForwardVector*MoveSpeed* CurrentMoveFowardAxis *DeltaTime;
	SetActorLocation(MovePosition, true);


	CurrentRotateRightAxis = FMath::Lerp(CurrentRotateRightAxis, TargetRotateRightAxis, RotationSmoothness);
	float Rotation = GetActorRotation().Yaw + CurrentRotateRightAxis * RotatiSpeed * DeltaTime;
	SetActorRotation(FRotator(0.f, Rotation, 0.f));

	UE_LOG(LogTanki, Verbose, TEXT("CurrentRotateRightAxis: %f"), CurrentRotateRightAxis);

	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TurretTargetPosition);
	FRotator CurrentRotation = TurretMesh->GetComponentRotation();
	TargetRotation.Roll = CurrentRotation.Roll;
	TargetRotation.Pitch = CurrentRotation.Pitch;
	TurretMesh->SetWorldRotation(FMath::Lerp(CurrentRotation, TargetRotation, TargetRotationSmootheness));
}

void ATankyPawn::MoveForward(float AxisValue)
{
	TargetMoveForwardAxis = AxisValue;
}

void ATankyPawn::RotateRight(float AxisValue)
{
	TargetRotateRightAxis = AxisValue;
}

void ATankyPawn::SetTurretTargetPosition(const FVector& TargetPosition)
{
	TurretTargetPosition = TargetPosition;
}
