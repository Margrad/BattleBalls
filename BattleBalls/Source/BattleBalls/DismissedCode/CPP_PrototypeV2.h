// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_PrototypeV2.generated.h"

// Forward declaration
class UPhysicsConstraintComponent;
class USphereComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class USceneComponent;
class UCameraComponent;

UCLASS()
class BATTLEBALLS_API ACPP_PrototypeV2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_PrototypeV2();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntedMoveForward(float Throttle);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntedMoveRight(float Throttle);

	// Camera Settings
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
	USceneComponent* Gizmoball = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	UCameraComponent* Camera = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Pointers to the needed vehicle component F=Front, B=Back, L=Left, R=Right
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* FLMask;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* FRMask;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* BLMask;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* BRMask;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* FLAxelConstrain;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* FLWheel;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* BLAxelConstrain;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* BLWheel;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* FRAxelConstrain;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* FRWheel;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* BRAxelConstrain;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* BRWheel;
	
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* FLAbsorver;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* FLAxle;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* BLAbsorver;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* BLAxle;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* FRAbsorver;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* FRAxle;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* BRAbsorver;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* BRAxle;



	void SetCamera();

	// Movement Settings 
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float BaseThrottle = 150000;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxSpeed = 770;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxRotation = 120;

	void SetAxelConstrains(UPhysicsConstraintComponent* AxelConstrain);
	void SetWheels(USphereComponent* Wheel);
	void SetAbsorvers(UPhysicsConstraintComponent* Absorver);
	void InitializeComponents();
	void AttachComponents();
};
