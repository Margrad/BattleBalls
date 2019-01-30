// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleBase.h"
#include "WeaponComponent.h"
#include "VehicleComponent.h"
#include "SideWheels.h"

// Sets default values
AVehicleBase::AVehicleBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVehicleBase::IntendMoveForward(float ThrottleMultiplier)
{

	//UE_LOG(LogTemp, Warning, TEXT("Throttle : %f"), ThrottleMultiplier);
	
	RightWheels->DriveWheels(ThrottleMultiplier);
	LeftWheels->DriveWheels(ThrottleMultiplier);
}

void AVehicleBase::IndendMoveRigth(float ThrottleMultiplier)
{
	//UE_LOG(LogTemp, Warning, TEXT("Throttle : %f"), ThrottleMultiplier);
	RightWheels->DriveWheels(-ThrottleMultiplier);
	LeftWheels->DriveWheels(ThrottleMultiplier);
}

// Called every frame
void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVehicleBase::SetWheels(USideWheels * LeftWheelsToSet, USideWheels * RightWheelsToSet)
{
	RightWheels = RightWheelsToSet;
	LeftWheels = LeftWheelsToSet;
}

