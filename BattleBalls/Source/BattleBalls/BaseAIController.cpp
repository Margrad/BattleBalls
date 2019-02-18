// All Copyrights reserved to Marco Granada.

#include "BaseAIController.h"
#include "Engine/World.h"
#include "VehicleBase.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	// TODO add proper evaluation

	// Check if target is not null and moves arround it;
	// MoveAroundTarget();
}


float ABaseAIController::EvaluateTarget(AActor * Target)
{
	if (!Cast<AVehicleBase>(Target)->GetIsPossibleTarget())
	{
		return 0;
	}
	float distance = (GetPawn()->GetActorLocation() - Target->GetActorLocation()).Size();
	float LocationValue = 10000 / (distance + 1000);
	float HPValue = Cast<AVehicleBase>(Target)->GetHPRatio() * 20;

	return LocationValue + HPValue;
}


AActor* ABaseAIController::SelectTargetFromArray(TArray<AActor*> FoundEnemies)
{
	if (FoundEnemies.Num() == 0) { return nullptr; }
	TArray<float> Evaluations;
	for (auto Enemy : FoundEnemies) {
		Evaluations.Add(EvaluateTarget(Enemy));
	}
	int32 MaxIndex = 0;
	int32 i = 0;
	float Max = 0;
	for (auto Evaluation : Evaluations) {
		if (Evaluation > Max) {
			Max = Evaluation;
			MaxIndex = i;
		}
		i++;
	}
	if (Max <= 0) { return nullptr; }

	return FoundEnemies[MaxIndex];
}

void ABaseAIController::MoveAroundTarget()
{
	if (!Blackboard->GetValueAsObject("Enemy")) {
		UE_LOG(LogTemp, Warning, TEXT("Ups..."));
		return; 
	}
	
	FVector TargetLocation = Cast<AActor>(Blackboard->GetValueAsObject("Enemy"))->GetActorLocation();
	FVector Distance = TargetLocation - GetPawn()->GetActorLocation();
	//FVector NewLocation1 = FVector(-Distance.Y, Distance.X, Distance.Z)+TargetLocation;
	FVector NewLocation2 = FVector(Distance.Y, -Distance.X, Distance.Z)+TargetLocation;

	//if (NewLocation1.Size() < NewLocation2.Size()) {
	//	MoveToLocation(NewLocation1.GetSafeNormal()*500, 100, false);
	//	return ;
	//}
	MoveToLocation(NewLocation2.GetSafeNormal() * 500, 100, false, true, true, false);
}
