// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehicleBase.generated.h"

UCLASS()
class BATTLEBALLS_API AVehicleBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehicleBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditDefaultsOnly,Category = Setup)
	class UStaticMeshComponent* Body;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	class UWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	class UVehicleComponent* VehicleComponent;

	
};
