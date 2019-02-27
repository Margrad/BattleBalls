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
		UStaticMeshComponent* CLMask;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* CRMask;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* FLWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* BLWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* FRWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* BRWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* CRWheel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* CLWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* FLAxle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* BLAxle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* FRAxle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* BRAxle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* CRAxle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USphereComponent* CLAxle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* FLAbsorver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* BLAbsorver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* FRAbsorver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* BRAbsorver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* CRAbsorver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* CLAbsorver;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* FLSpiner;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* BLSpiner;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* FRSpiner;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* BRSpiner;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* CRSpiner;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UPhysicsConstraintComponent* CLSpiner;

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

	// Overrride function to define how the pawn takes damage
	UFUNCTION(BlueprintCallable, Category = Damage)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	UFUNCTION(BlueprintPure, Category = HP)
	bool IsDead();
	UFUNCTION(BlueprintPure, Category = HP)
	float GetMaxHP();
	UFUNCTION(BlueprintPure, Category = HP)
	float GetCurrentHP();
	UFUNCTION(BlueprintPure, Category = HP)
	float GetHPRatio();
	
	UFUNCTION(BlueprintCallable, Category = Fire)
	FVector GetAimBias();
	UFUNCTION(BlueprintCallable, Category = Fire)
	void SetAimBias();

	UFUNCTION(BlueprintPure, Category = AsTarget)
	bool GetIsPossibleTarget() { return IsPossibleTarget; }

	UFUNCTION(BlueprintCallable, Category = AsTarget)
	void SetIsPossibleTarget(bool Targetable) {IsPossibleTarget = Targetable; }
	
	// Should be called at every tick
	// and returns if the run should make noise
	UFUNCTION(BlueprintCallable, Category = Audio)
	bool ShouldMakeEngineSound(float DeltaTime);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


	// HP Settings
	UPROPERTY(EditDefaultsOnly, Category = HP)
		float MaxHP = 120;
	UPROPERTY(EditDefaultsOnly, Category = HP)
		float CurrentHP = 0;

	float EngineRunDistance = 0;

	UPROPERTY(EditDefaultsOnly, Category = Team)
	FName Team = FName("Neutral");

	FVector AimDificultyBias = FVector(0, 0, 0);

	void SetWheels(USphereComponent* Wheel);
	void SetAxles(USphereComponent * Axle);
	void SetAbsorvers(UPhysicsConstraintComponent* Absorver);
	void SetSpiners(UPhysicsConstraintComponent* Spiner);
	void InitializeComponents();
	void AttachComponents();
	void SetWheelInPosition(USphereComponent* Wheel, USphereComponent* Axle, UPhysicsConstraintComponent* Absorver, UPhysicsConstraintComponent* Spiner, UStaticMeshComponent* Mask, FVector Position);
	void SetCamera();
	bool IsPossibleTarget = true;
};
