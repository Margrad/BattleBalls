// All Copyrights reserved to Marco Granada.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehicleBase.generated.h"

// Forward declaration
class UPhysicsConstraintComponent;
class USphereComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class USceneComponent;
class UCameraComponent;
class UWeaponComponent;
class UVehicleNavMovementComponent;
class UPawnMovementComponent;

/*
* Base class for the vehicles in this game
*/
UCLASS()
class BATTLEBALLS_API AVehicleBase : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AVehicleBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera Settings
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		USceneComponent* Gizmoball = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		UCameraComponent* Camera = nullptr;

	// Pointers to the needed vehicle component F=Front, B=Back, L=Left, R=Right
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* Body;

	// Wheels Section
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* FLMask;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* FRMask;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* BLMask;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* BRMask;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* FLWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* BLWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* FRWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* BRWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* FLAbsorver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* BLAbsorver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* FRAbsorver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* BRAbsorver;

	// Gun Section
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		UStaticMeshComponent* BarrelMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USceneComponent* Barrel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USceneComponent* BarrelBase;

	// Extra Functionalities Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		UWeaponComponent* WeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		UVehicleNavMovementComponent* MovementComponent;

	UFUNCTION(BlueprintCallable, Category = Team)
		void SetTeam(FName NewTeam);
	UFUNCTION(BlueprintCallable, Category = Team)
		FName GetTeam() { return Team; }


	UFUNCTION(BlueprintCallable, Category = Damage)
	void TakeDamage(float Damage);
	UFUNCTION(BlueprintPure, Category = HP)
	bool IsDead();
	UFUNCTION(BlueprintPure, Category = HP)
	float GetMaxHP();
	UFUNCTION(BlueprintPure, Category = HP)
	float GetCurrentHP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Movement Settings 
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float BaseThrottle = 150000;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float MaxSpeed = 770;
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float MaxRotation = 120;
	UPROPERTY(EditDefaultsOnly, Category = HP)
		float MaxHP = 120;
	UPROPERTY(EditDefaultsOnly, Category = HP)
		float CurrentHP = 0;



	UPROPERTY(EditDefaultsOnly, Category = Team)
	FName Team = FName("Neutral");

	void SetWheels(USphereComponent* Wheel);
	void SetAbsorvers(UPhysicsConstraintComponent* Absorver);
	void InitializeComponents();
	void AttachComponents();
	void SetCamera();
};
