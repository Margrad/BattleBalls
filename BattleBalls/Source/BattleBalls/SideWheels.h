// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SideWheels.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEBALLS_API USideWheels : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USideWheels();
	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DriveWheels(float Throttle);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	TArray<class AMotionAbsovingWheels*> GetWheels();

};
