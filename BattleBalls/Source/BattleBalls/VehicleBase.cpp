// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleBase.h"
#include "WeaponComponent.h"
#include "VehicleComponent.h"

// Sets default values
AVehicleBase::AVehicleBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(FName("WeaponComponent"));
	VehicleComponent = CreateDefaultSubobject<UVehicleComponent>(FName("VehicleComponent"));

}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	
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

