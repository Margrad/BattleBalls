// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PrototypeV2.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACPP_PrototypeV2::ACPP_PrototypeV2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initiate all required components
	InitializeComponents();
	Body->SetSimulatePhysics(true);
	Body->SetMassOverrideInKg(NAME_None, 100, true);

	AttachComponents();

	SetAbsorvers(FLAbsorver);
	SetAbsorvers(FRAbsorver);
	SetAbsorvers(BLAbsorver);
	SetAbsorvers(BRAbsorver);

	SetAxelConstrains(FLAxelConstrain);
	SetAxelConstrains(BLAxelConstrain);
	SetAxelConstrains(FRAxelConstrain);
	SetAxelConstrains(BRAxelConstrain);

	FLAbsorver->SetConstrainedComponents(Body, NAME_None, FLAxle, NAME_None);
	FRAbsorver->SetConstrainedComponents(Body, NAME_None, FRAxle, NAME_None);
	BLAbsorver->SetConstrainedComponents(Body, NAME_None, BLAxle, NAME_None);
	BRAbsorver->SetConstrainedComponents(Body, NAME_None, BRAxle, NAME_None);

	FLAxelConstrain->SetConstrainedComponents(FLAxle, NAME_None, FLWheel, NAME_None);
	FRAxelConstrain->SetConstrainedComponents(FRAxle, NAME_None, FRWheel, NAME_None);
	BLAxelConstrain->SetConstrainedComponents(BLAxle, NAME_None, BLWheel, NAME_None);
	BRAxelConstrain->SetConstrainedComponents(BRAxle, NAME_None, BRWheel, NAME_None);

	SetWheels(FLWheel);
	SetWheels(FRWheel);
	SetWheels(BLWheel);
	SetWheels(BRWheel);

	FLMask->SetCollisionProfileName(FName("OverlapAll"));
	FRMask->SetCollisionProfileName(FName("OverlapAll"));
	BLMask->SetCollisionProfileName(FName("OverlapAll"));
	BRMask->SetCollisionProfileName(FName("OverlapAll"));
	
	SetCamera();
}

// Called when the game starts or when spawned
void ACPP_PrototypeV2::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_PrototypeV2::SetCamera()
{
		Gizmoball = CreateDefaultSubobject<USceneComponent>(FName("Gizmball"));
		SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
		Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
		Gizmoball->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
		SpringArm->AttachToComponent(Gizmoball, FAttachmentTransformRules::KeepRelativeTransform);
		Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
		SpringArm->TargetArmLength = 300;
		Camera->SetRelativeLocation(FVector( 0, 0, 100));
		SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));
}

void ACPP_PrototypeV2::SetAxelConstrains(UPhysicsConstraintComponent * AxelConstrain)
{
	AxelConstrain->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45);
	AxelConstrain->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 45);
	AxelConstrain->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45);
}

void ACPP_PrototypeV2::SetWheels(USphereComponent * Wheel)
{
	Wheel->SetCollisionProfileName(FName("PhysicsActor"));
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(NAME_None, 10);
}

void ACPP_PrototypeV2::SetAbsorvers(UPhysicsConstraintComponent * Absorver)
{
	Absorver->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	Absorver->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	Absorver->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 10);
	Absorver->SetLinearPositionDrive(true, true, true);
	Absorver->SetLinearVelocityDrive(true, true, true);
	Absorver->SetLinearDriveParams(50, 10, 0);
	Absorver->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45);
	Absorver->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45);
	Absorver->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45);
}

void ACPP_PrototypeV2::InitializeComponents()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	FLMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("FLMask"));
	FRMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("FRMask"));
	BLMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("BLMask"));
	BRMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("BRMask"));
	FLAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FLAbsorber"));
	FLAxle = CreateDefaultSubobject<USphereComponent>(FName("FLAxel"));
	FLAxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FLAxelConstrain"));
	FLWheel = CreateDefaultSubobject<USphereComponent>(FName("FLWheel"));
	BLAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BLAbsorber"));
	BLAxle = CreateDefaultSubobject<USphereComponent>(FName("BLAxel"));
	BLAxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BLAxelConstrain"));
	BLWheel = CreateDefaultSubobject<USphereComponent>(FName("BLWheel"));
	FRAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FRAbsorber"));
	FRAxle = CreateDefaultSubobject<USphereComponent>(FName("FRAxel"));
	FRAxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FRAxelConstrain"));
	FRWheel = CreateDefaultSubobject<USphereComponent>(FName("FRWheel"));
	BRAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BRAbsorber"));
	BRAxle = CreateDefaultSubobject<USphereComponent>(FName("BRAxel"));
	BRAxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BRAxelConstrain"));
	BRWheel = CreateDefaultSubobject<USphereComponent>(FName("BRWheel"));

	Body->SetMobility(EComponentMobility::Movable);
	FLAxle->SetMobility(EComponentMobility::Movable);
	FRAxle->SetMobility(EComponentMobility::Movable);
	BLAxle->SetMobility(EComponentMobility::Movable);
	BRAxle->SetMobility(EComponentMobility::Movable);
	FLWheel->SetMobility(EComponentMobility::Movable);
	FRWheel->SetMobility(EComponentMobility::Movable);
	BLWheel->SetMobility(EComponentMobility::Movable);
	BRWheel->SetMobility(EComponentMobility::Movable);
}

void ACPP_PrototypeV2::AttachComponents()
{
	SetRootComponent(Body);
	FLAbsorver->AttachToComponent(Body,FAttachmentTransformRules::KeepRelativeTransform);
	FLAbsorver->SetRelativeLocation(FVector(55, -55, -30));
	FLAxle->AttachToComponent(FLAbsorver, FAttachmentTransformRules::KeepRelativeTransform);
	FLWheel->AttachToComponent(FLAxle, FAttachmentTransformRules::KeepRelativeTransform);
	FLAxelConstrain->AttachToComponent(FLWheel, FAttachmentTransformRules::KeepRelativeTransform);
	FLMask->AttachToComponent(FLWheel, FAttachmentTransformRules::KeepRelativeTransform);

	FRAbsorver->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	FRAbsorver->SetRelativeLocation(FVector(55, 55, -30));
	FRAxle->AttachToComponent(FRAbsorver, FAttachmentTransformRules::KeepRelativeTransform);
	FRWheel->AttachToComponent(FRAxle, FAttachmentTransformRules::KeepRelativeTransform);
	FRAxelConstrain->AttachToComponent(FRWheel, FAttachmentTransformRules::KeepRelativeTransform);
	FRMask->AttachToComponent(FRWheel, FAttachmentTransformRules::KeepRelativeTransform);

	BLAbsorver->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	BLAbsorver->SetRelativeLocation(FVector(-55, -55, -30));
	BLAxle->AttachToComponent(BLAbsorver, FAttachmentTransformRules::KeepRelativeTransform);
	BLWheel->AttachToComponent(BLAxle, FAttachmentTransformRules::KeepRelativeTransform);
	BLAxelConstrain->AttachToComponent(BLWheel, FAttachmentTransformRules::KeepRelativeTransform);
	BLMask->AttachToComponent(BLWheel, FAttachmentTransformRules::KeepRelativeTransform);

	BRAbsorver->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	BRAbsorver->SetRelativeLocation(FVector(-55, 55, -30));
	BRAxle->AttachToComponent(BRAbsorver, FAttachmentTransformRules::KeepRelativeTransform);
	BRWheel->AttachToComponent(BRAxle, FAttachmentTransformRules::KeepRelativeTransform);
	BRAxelConstrain->AttachToComponent(BRWheel, FAttachmentTransformRules::KeepRelativeTransform);
	BRMask->AttachToComponent(BRWheel, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void ACPP_PrototypeV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Reduce angular momento to stabilize flipping
	FVector NewAngularSpeed = Body->GetPhysicsAngularVelocity();
	NewAngularSpeed.Y *= 0.1;
	Body->SetPhysicsAngularVelocity(NewAngularSpeed);
}

// Called to bind functionality to input
void ACPP_PrototypeV2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPP_PrototypeV2::IntedMoveForward(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	FVector waist;
	float CurrentSpeed;
	this->GetVelocity().ToDirectionAndLength(waist, CurrentSpeed);
	float ratio =  CurrentSpeed / MaxSpeed;
	ratio = FMath::Clamp<float>(ratio, 0, 1);
	Throttle *= (1 - ratio);
	FLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	FRWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	BLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	BRWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
}

void ACPP_PrototypeV2::IntedMoveRight(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	float CurrentAngularSpeed = FMath::Abs(Body->GetPhysicsAngularVelocity().Z);
	float ratio = CurrentAngularSpeed / MaxRotation;
	ratio = FMath::Clamp<float>(ratio, 0, 1);
	Throttle *= (1 - ratio);
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	FLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	FRWheel->AddForce(Body->GetForwardVector()*Throttle*-BaseThrottle);
	BLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	BRWheel->AddForce(Body->GetForwardVector()*Throttle*-BaseThrottle);
}

