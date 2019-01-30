// Fill out your copyright notice in the Description page of Project Settings.

#include "WheelSpawnPoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UWheelSpawnPoint::UWheelSpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWheelSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnedWheel = GetWorld()->SpawnActorDeferred<AActor>(WheelType, GetComponentTransform());
	if (!(SpawnedWheel)) { return; }
	SpawnedWheel->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedWheel, GetComponentTransform());
	// ...
	
}


