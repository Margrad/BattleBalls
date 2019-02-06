// All Copyrights reserved to Marco Granada.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBALLS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Fire)
	FVector CrossAimingAt();

	virtual void Tick(float) override;


	UFUNCTION(BlueprintCallable, Category = Dead)
	void LostPawn();

private:
	// Ratio of the screen pointed by the crosshair from the top
	// (0 is on the very top and 1 is ate the bottom)
	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float Yratio = 0.45; 
};
