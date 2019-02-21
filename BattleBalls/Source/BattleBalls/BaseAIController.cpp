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
	float Evaluation;
	float MaxEvaluation=0;
	AActor* Target = nullptr;

	for (auto Enemy : FoundEnemies) {
		Evaluation=EvaluateTarget(Enemy);
		if (Evaluation>MaxEvaluation) {
			MaxEvaluation = Evaluation;
			Target = Enemy;
		}
	}
	return Target;
}

void ABaseAIController::MoveAroundTarget()
{
	if (!Blackboard->GetValueAsObject("Enemy")) {
		UE_LOG(LogTemp, Warning, TEXT("Ups..."));
		return; 
	}

	FVector ThisActorRotation = GetPawn()->GetActorRotation().Vector();
	FVector ThisActorLocation = GetPawn()->GetActorLocation();
	FVector TargetLocation = Cast<AActor>(Blackboard->GetValueAsObject("Enemy"))->GetActorLocation();
	FVector Distance = TargetLocation - ThisActorLocation;

	FVector NewLocation1 = FVector(-Distance.Y, Distance.X, Distance.Z).GetSafeNormal() * 1000 +TargetLocation;
	FVector NewLocation2 = FVector(Distance.Y, -Distance.X, Distance.Z).GetSafeNormal() * 1000 +TargetLocation;
	UE_LOG(LogTemp, Warning, TEXT("ThisPost %s"), *ThisActorLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Target %s"), *TargetLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Diff %s"), *Distance.ToString());
	UE_LOG(LogTemp, Warning, TEXT("NL1 %s"), *NewLocation1.ToString());
	UE_LOG(LogTemp, Warning, TEXT("NL2 %s"), *NewLocation2.ToString());

	if (FVector::DotProduct((NewLocation1-ThisActorLocation), ThisActorRotation) > FVector::DotProduct((NewLocation2 - ThisActorLocation), ThisActorRotation)) {
		MoveToLocation(NewLocation1, 300, false, true, true, false);
		return ;
	}
	MoveToLocation(NewLocation2, 300, false, true, true, false);
}
