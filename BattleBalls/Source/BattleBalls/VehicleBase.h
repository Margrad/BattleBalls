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
	
	//Funtion to setupe the Sidewheels properly
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetWheels(class USideWheels* LeftWheels, class USideWheels* RightWheels);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendMoveForward(float ThrottleMultiplier);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IndendMoveRigth(float ThrottleMultiplier);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	// Recive input and send it to the wheel
	// Recive input

	class USideWheels* LeftWheels = nullptr;
	class USideWheels* RightWheels = nullptr;
	
};
