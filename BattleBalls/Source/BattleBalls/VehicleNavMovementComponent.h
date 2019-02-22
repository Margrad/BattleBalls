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
	void IntendMoveForward(float Throttle);
	// Tells the vehicle to move Right(Throttle > 0) or Left (Throttle <0)
	UFUNCTION(BlueprintCallable, Category = Movemente)
	void IntendTurnRight(float Throttle);
	// Gets the vehicle back upside
	UFUNCTION(BlueprintCallable, Category = Movemente)
	void GetBackUpSide();
	// Sets the component pointers to the needed vehicle wheels F=Front, B=Back, L=Left, R=Right
	UFUNCTION(BlueprintCallable, Category = Movemente)
	void InitializeWheelsVariables(UStaticMeshComponent * Bdy, USphereComponent * FL, USphereComponent * FR, USphereComponent * BL, USphereComponent * BR, USphereComponent * CL, USphereComponent * CR);

private:
		UStaticMeshComponent* Body;
		USphereComponent* FLWheel;
		USphereComponent* BLWheel;
		USphereComponent* FRWheel;
		USphereComponent* BRWheel;
		USphereComponent* CRWheel;
		USphereComponent* CLWheel;

	// Movement Settings 
	// Max Throttle for each wheel
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float BaseThrottle = 90000;
	// Max Speed, as the speed increases the throttle on the wheels is decreased
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxSpeed = 700;
	// Max Rotation speed, as the rotation speed increases the throttle on the wheels is decreased
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxRotation = 120;

	// This function is override so the created movement functions can be used with the Engine Navigation System
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

};
