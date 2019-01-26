// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WheelSpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEBALLS_API UWheelSpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWheelSpawnPoint();

	AActor* GetSpawnedActor() const { return SpawnedWheel; };
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, category = Setup)
	TSubclassOf<AActor> WheelType;
	
	AActor* SpawnedWheel;
};
