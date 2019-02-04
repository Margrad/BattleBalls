// All Copyrights reserved to Marco Granada.

#include "VehicleBase.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "VehicleNavMovementComponent.h"
#include "WeaponComponent.h"


// Sets default values
AVehicleBase::AVehicleBase()
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

	SetWheels(FLWheel);
	SetWheels(FRWheel);
	SetWheels(BLWheel);
	SetWheels(BRWheel);
	
	FLMask->SetCollisionProfileName(FName("OverlapAll"));
	FRMask->SetCollisionProfileName(FName("OverlapAll"));
	BLMask->SetCollisionProfileName(FName("OverlapAll"));
	BRMask->SetCollisionProfileName(FName("OverlapAll"));

	FLAbsorver->SetConstrainedComponents(Body, NAME_None, FLWheel, NAME_None);
	FRAbsorver->SetConstrainedComponents(Body, NAME_None, FRWheel, NAME_None);
	BLAbsorver->SetConstrainedComponents(Body, NAME_None, BLWheel, NAME_None);
	BRAbsorver->SetConstrainedComponents(Body, NAME_None, BRWheel, NAME_None);

	SetCamera();
	MovementComponent->InitializeVariable(Body, FLWheel, FRWheel, BLWheel, BRWheel);
	WeaponComponent->InitializeComponent(BarrelBase, Barrel, BarrelMesh);
}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVehicleBase::SetCamera()
{
	Gizmoball = CreateDefaultSubobject<USceneComponent>(FName("Gizmball"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Gizmoball->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->AttachToComponent(Gizmoball, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->TargetArmLength = 300;
	Camera->SetRelativeLocation(FVector(0, 0, 100));
	SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));
}


void AVehicleBase::SetWheels(USphereComponent * Wheel)
{
	Wheel->SetCollisionProfileName(FName("PhysicsActor"));
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(NAME_None, 10);
}

void AVehicleBase::SetAbsorvers(UPhysicsConstraintComponent * Absorver)
{
	Absorver->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	Absorver->SetLinearYLimit(ELinearConstraintMotion::LCM_Limited, 10);
	Absorver->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
	Absorver->SetLinearPositionDrive(true, true, true);
	Absorver->SetLinearVelocityDrive(true, true, true);
	Absorver->SetLinearDriveParams(50, 10, 0);
	Absorver->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45);
	Absorver->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 45);
	Absorver->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45);

}

void AVehicleBase::InitializeComponents()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	FLMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("FLMask"));
	FRMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("FRMask"));
	BLMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("BLMask"));
	BRMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("BRMask"));
	FLAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FLAbsorber"));
	FLWheel = CreateDefaultSubobject<USphereComponent>(FName("FLWheel"));
	BLAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BLAbsorber"));
	BLWheel = CreateDefaultSubobject<USphereComponent>(FName("BLWheel"));
	FRAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FRAbsorber"));
	FRWheel = CreateDefaultSubobject<USphereComponent>(FName("FRWheel"));
	BRAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BRAbsorber"));
	BRWheel = CreateDefaultSubobject<USphereComponent>(FName("BRWheel"));

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BarrelMesh"));
	BarrelBase = CreateDefaultSubobject<USceneComponent>(FName("BarrelBase"));
	Barrel = CreateDefaultSubobject<USceneComponent>(FName("Barrel"));

	Body->SetMobility(EComponentMobility::Movable);
	FLWheel->SetMobility(EComponentMobility::Movable);
	FRWheel->SetMobility(EComponentMobility::Movable);
	BLWheel->SetMobility(EComponentMobility::Movable);
	BRWheel->SetMobility(EComponentMobility::Movable);

	MovementComponent = CreateDefaultSubobject<UVehicleNavMovementComponent>(FName("MovementComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(FName("WeaponComponent"));
}

void AVehicleBase::AttachComponents()
{
	SetRootComponent(Body);
	FLAbsorver->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	FLAbsorver->SetRelativeLocation(FVector(75, -75, -30));
	FLWheel->AttachToComponent(FLAbsorver, FAttachmentTransformRules::KeepRelativeTransform);
	FLMask->AttachToComponent(FLWheel, FAttachmentTransformRules::KeepRelativeTransform);

	FRAbsorver->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	FRAbsorver->SetRelativeLocation(FVector(75, 75, -30));
	FRWheel->AttachToComponent(FRAbsorver, FAttachmentTransformRules::KeepRelativeTransform);
	FRMask->AttachToComponent(FRWheel, FAttachmentTransformRules::KeepRelativeTransform);

	BLAbsorver->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	BLAbsorver->SetRelativeLocation(FVector(-75, -75, -30));
	BLWheel->AttachToComponent(BLAbsorver, FAttachmentTransformRules::KeepRelativeTransform);
	BLMask->AttachToComponent(BLWheel, FAttachmentTransformRules::KeepRelativeTransform);

	BRAbsorver->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	BRAbsorver->SetRelativeLocation(FVector(-75, 75, -30));
	BRWheel->AttachToComponent(BRAbsorver, FAttachmentTransformRules::KeepRelativeTransform);
	BRMask->AttachToComponent(BRWheel, FAttachmentTransformRules::KeepRelativeTransform);

	BarrelBase->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	Barrel->AttachToComponent(BarrelBase, FAttachmentTransformRules::KeepRelativeTransform);
	BarrelMesh->AttachToComponent(Barrel, FAttachmentTransformRules::KeepRelativeTransform);
}


// Called every frame
void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Reduce angular momento to stabilize flipping
	FVector NewAngularSpeed = Body->GetPhysicsAngularVelocity();
	NewAngularSpeed.Y *= DeltaTime;
	Body->SetPhysicsAngularVelocity(NewAngularSpeed);

}

// Called to bind functionality to input
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



