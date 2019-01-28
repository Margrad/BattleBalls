// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_PrototypeV2.generated.h"

// Forward declaration
class UPhysicsConstraintComponent;
class USphereComponent;
class UStaticMeshComponent;

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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Pointers to the needed vehicle component F=Front, B=Back, L=Left, R=Right
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* Body;
	//UPhysicsConstraintComponent* FLAbsorber;
	//USphereComponent* FLAxel;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* FLAxelConstrain;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* FLWheel;
	//UPhysicsConstraintComponent* BLAbsorber;
	//USphereComponent* BLAxel;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* BLAxelConstrain;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* BLWheel;
	//UPhysicsConstraintComponent* FRAbsorber;
	//USphereComponent* FRAxel;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* FRAxelConstrain; 
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* FRWheel;
	//UPhysicsConstraintComponent* BRAbsorber;
	//USphereComponent* BRAxel;
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* BRAxelConstrain;
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* BRWheel;

	void SetAxelConstrains(UPhysicsConstraintComponent* AxelConstrain);

	void InitializeComponents();
	void AttachComponents();
};
