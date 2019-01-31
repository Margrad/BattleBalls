// All Copyrights reserved to Marco Granada.

#include "BaseAIController.h"
#include "Engine/World.h"
#include "VehicleBase.h"

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ThisVehicle = Cast<AVehicleBase>(GetPawn());
	if(!ThisVehicle){
		return;
	}
	TargetVehicle = Cast<AVehicleBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(TargetVehicle)) { return; }
	if (!ensure(ThisVehicle)) { return; }

}



