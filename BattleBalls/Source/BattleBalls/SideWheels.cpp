// Fill out your copyright notice in the Description page of Project Settings.

#include "SideWheels.h"
#include "MotionAbsovingWheels.h"
#include "WheelSpawnPoint.h"
// Sets default values for this component's properties

USideWheels::USideWheels()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts

void USideWheels::BeginPlay()
{
	Super::BeginPlay();

	// ...


}


// Called every frame
/*
void USideWheels::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/

TArray<AMotionAbsovingWheels*> USideWheels::GetWheels()
{
	TArray<AMotionAbsovingWheels*> Wheels;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children) {
		auto SpawnPointChild = Cast<UWheelSpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnChild = SpawnPointChild->GetSpawnedActor();

		auto Wheel = Cast<AMotionAbsovingWheels>(SpawnChild);
		if (!Wheel) continue;
		Wheels.Add(Wheel);
	}

	return Wheels;
}

void USideWheels::DriveWheels(float Throttle)
{
	auto Wheels = GetWheels();
	if (Wheels.Num() == 0) {
		//UE_LOG(LogTemp, Warning, TEXT("DriveWheels: Ground is touched: Throttle : %f"), Throttle);
		UE_LOG(LogTemp, Error, TEXT("DriveWheels: No Wheels found!"), Throttle);
		return;
	}
	for (auto Wheel : Wheels) {
		Wheel->AddDrivingMultiplier(Throttle);
	}
}
