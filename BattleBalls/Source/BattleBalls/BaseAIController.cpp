// All Copyrights reserved to Marco Granada.

#include "BaseAIController.h"
#include "Engine/World.h"
#include "VehicleBase.h"

void ABaseAIController::LostPawn()
{
	Destroy();
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



