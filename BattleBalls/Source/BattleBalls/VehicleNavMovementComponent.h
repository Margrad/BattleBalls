// All Copyrights reserved to Marco Granada.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "VehicleNavMovementComponent.generated.h"


class USphereComponent;
class UStaticMeshComponent;
/**
 * This class is used override RequestDirectMove() so it uses the vehicle movement functions
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLEBALLS_API UVehicleNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	// 
	
	// Tells the vehicle to move foward(Throttle > 0) or back (Throttle <0)
	UFUNCTION(BlueprintCallable, Category = Movemente)
	void IntedMoveForward(float Throttle);
	// Tells the vehicle to move Right(Throttle > 0) or Left (Throttle <0)
	UFUNCTION(BlueprintCallable, Category = Movemente)
	void IntedTurnRight(float Throttle);
	// Sets the component pointers to the needed vehicle wheels F=Front, B=Back, L=Left, R=Right
	UFUNCTION(BlueprintCallable, Category = Movemente)
	void InitializeVariable(UStaticMeshComponent* Bdy, USphereComponent* FL, USphereComponent* FR, USphereComponent* BL, USphereComponent* BR);

private:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* FLWheel;
	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* BLWheel;
	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* FRWheel;
	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* BRWheel;

	// Movement Settings 
	// Max Throttle for each wheel
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float BaseThrottle = 150000;
	// Max Speed, as the speed increases the throttle on the wheels is decreased
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxSpeed = 870;
	// Max Rotation speed, as the rotation speed increases the throttle on the wheels is decreased
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxRotation = 150;

	// This function is override so the created movement functions can be used with the Engine Navigation System
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

};
