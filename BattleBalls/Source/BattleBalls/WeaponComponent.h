// All Copyrights reserved to Marco Granada.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEBALLS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Fire)
	void InitializeComponent(USceneComponent* BarrelBase, USceneComponent* Barrel, UStaticMeshComponent* BarrelMesh);

	// This function will move the Barrel in the camera direction
	UFUNCTION(BlueprintCallable, Category = Fire)
	void MoveBarrel(FVector PointToAim);

	// This function will calculate the barrel position to hit a target
	UFUNCTION(BlueprintCallable, Category = Fire)
	void AutoAimAt(FVector Target);

	// Get BarrelMesh position to use in PlayerController->CrossAimAt
	UStaticMeshComponent* GetBarrel() { return BarrelMesh; }


	UFUNCTION(BlueprintCallable, Category = Fire)
	void Fire();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	USceneComponent* Barrel;
	USceneComponent* BarrelBase;
	UStaticMeshComponent* BarrelMesh;
	UPROPERTY(EditDefaultsOnly, Category = Fire)
	TSubclassOf<AActor> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float MaxElevationSpeed = 25;

	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float MaxRotationSpeed = 25;

};
