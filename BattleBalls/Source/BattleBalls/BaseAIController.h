// All Copyrights reserved to Marco Granada.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"
class UAimingComponent;
class AVehicleBase;
/*
* Used to setup the AIController blueprint	
*/
UCLASS()
class BATTLEBALLS_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

private:
	AVehicleBase* ThisVehicle = nullptr;

	// Used to set how close the vehicle will get to its target
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 50;

	// Aiming component
	UAimingComponent* AimingComponent;

	// Sets the PlayerTank(Enemy in this case)
	AVehicleBase* TargetVehicle = nullptr;
};
