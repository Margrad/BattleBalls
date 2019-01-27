// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionAbsovingWheels.generated.h"

UCLASS()
class BATTLEBALLS_API AMotionAbsovingWheels : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMotionAbsovingWheels();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Activated when the wheel is touching ground
	UFUNCTION()
	void IsToucnhingGround(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//Recieves the input for a wheel from 0 to 1;
	UFUNCTION(BlueprintCallable)
	void AddDrivingMultiplier(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	float BaseWheelThrottle = 1000000;

	UPROPERTY(EditDefaultsOnly)
	float TotalThrottleMultiplier = 0;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UPhysicsConstraintComponent* ShockAbsorber = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* Axel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent* WheelRotationAllower = nullptr;
};
