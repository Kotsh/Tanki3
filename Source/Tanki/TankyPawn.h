// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankyPawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TANKI_API ATankyPawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ATankyPawn();

	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
		void RotateRight(float AxisValue);

	

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotatiSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MovementSmoothness=0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSmoothness=0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float TargetRotationSmootheness = 0.5f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Movement")
		void SetTurretTargetPosition(const FVector& TargetPosition);

private:
	float CurrentMoveFowardAxis = 0.f;
	float TargetMoveForwardAxis = 0.f;
	float CurrentRotateRightAxis = 0.f;
	float TargetRotateRightAxis = 0.f;

	FVector TurretTargetPosition;
};
