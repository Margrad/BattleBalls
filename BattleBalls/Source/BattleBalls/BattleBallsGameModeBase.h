// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleBallsGameModeBase.generated.h"
/*
*	Defines the game dificulty settings
*/
UENUM(BlueprintType)		
enum class EDificultyEnum : uint8
{
	DE_Easy 	UMETA(DisplayName = "Easy"),
	DE_Normal 	UMETA(DisplayName = "Normal"),
	DE_Hard		UMETA(DisplayName = "Hard")
};

/**
 * 
 */
UCLASS()
class BATTLEBALLS_API ABattleBallsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	// Returns the game difficulty
	UFUNCTION(BlueprintCallable, Category = Setup)
	EDificultyEnum GetGameDificulty() { return GameDificulty; };

	// Sets the Game Dificulty
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetGameDificulty(EDificultyEnum Dificulty);

private:
	EDificultyEnum GameDificulty = EDificultyEnum::DE_Normal;
};
