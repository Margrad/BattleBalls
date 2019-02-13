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

public:
	UFUNCTION(BlueprintCallable, Category = Dead)
	void LostPawn();


	UFUNCTION(BlueprintCallable, Category = TargetEvaluation)
		AActor* GetTargetFromArray(TArray<AActor*> FoundEnemies);

	UFUNCTION(BlueprintCallable, Category = TargetEvaluation)
	void MoveAroundTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

private:
	float EvaluateTarget(AActor* Target);

	AActor* CurrentTarget = nullptr;

};
