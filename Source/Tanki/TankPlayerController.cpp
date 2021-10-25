// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "TankyPawn.h"
#include "Engine/Engine.h"


ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}


void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankyPawn = Cast<ATankyPawn>(GetPawn());
}

void ATankPlayerController::MoveForward(float AxisValue)
{

	TankyPawn->MoveForward(AxisValue);
}

void ATankPlayerController::RotateRight(float AxisValue)
{

	TankyPawn->RotateRight(AxisValue);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	if (!TankyPawn)
	{
		return;
	};

	FVector WorldMousePosition, WorldMouseDirection;
	DeprojectMousePositionToWorld(WorldMousePosition, WorldMouseDirection);

	FVector TargetTurretDirecton = WorldMousePosition - TankyPawn->GetActorLocation();
	TargetTurretDirecton.Z = 0.f;
	TargetTurretDirecton.Normalize();
	FVector TargetTurretPosition = TankyPawn->GetActorLocation()+ TargetTurretDirecton*1000.f;
	DrawDebugLine(GetWorld(), TankyPawn->GetActorLocation(), TargetTurretPosition, FColor::Green, false, 0.1f, 0, 5.f);
}


