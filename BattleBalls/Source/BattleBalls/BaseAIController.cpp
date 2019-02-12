// All Copyrights reserved to Marco Granada.

#include "BaseAIController.h"
#include "Engine/World.h"
#include "VehicleBase.h"

void ABaseAIController::LostPawn()
{
	Destroy();
}

float ABaseAIController::EvaluateTarget(AActor * Target)
{
	if (!Cast<AVehicleBase>(Target)->GetIsPossibleTarget())
	{
		return 0;
	}
	float distance = (GetPawn()->GetActorLocation()-Target->GetActorLocation()).Size();
	float LocationValue = 10000 / (distance + 1000);
	float HPValue = Cast<AVehicleBase>(Target)->GetHPRatio()*20;

	return LocationValue + HPValue;
}

AActor* ABaseAIController::GetTargetFromArray(TArray<AActor*> FoundEnemies)
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

	/*
	if (CurrentTarget != FoundEnemies[MaxIndex]) {
		CurrentTarget = FoundEnemies[MaxIndex];
		//UE_LOG(LogTemp, Warning, TEXT("%s has new target: %s : %f"), *GetPawn()->GetName(), *CurrentTarget->GetName(), Max);
	}*/
	return FoundEnemies[MaxIndex];
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// TODO add proper evaluation

}



