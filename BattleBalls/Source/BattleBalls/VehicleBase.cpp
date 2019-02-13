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
#include "BaseAIController.h"
#include "BasePlayerController.h"


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
	SetAbsorvers(CLAbsorver);
	SetAbsorvers(CRAbsorver);

	SetSpiners(FLSpiner);
	SetSpiners(FRSpiner);
	SetSpiners(BLSpiner);
	SetSpiners(BRSpiner);
	SetSpiners(CLSpiner);
	SetSpiners(CRSpiner);

	SetWheels(FLWheel);
	SetWheels(FRWheel);
	SetWheels(BLWheel);
	SetWheels(BRWheel);
	SetWheels(CLWheel);
	SetWheels(CRWheel);

	SetAxles(FLAxle);
	SetAxles(FRAxle);
	SetAxles(BLAxle);
	SetAxles(BRAxle);
	SetAxles(CLAxle);
	SetAxles(CRAxle);

	FLMask->SetCollisionProfileName(FName("OverlapAll"));
	FRMask->SetCollisionProfileName(FName("OverlapAll"));
	BLMask->SetCollisionProfileName(FName("OverlapAll"));
	BRMask->SetCollisionProfileName(FName("OverlapAll"));
	CLMask->SetCollisionProfileName(FName("OverlapAll"));
	CRMask->SetCollisionProfileName(FName("OverlapAll"));
	CRMask->SetRelativeScale3D(FVector(0.65, 0.65, 0.65));
	CLMask->SetRelativeScale3D(FVector(0.65, 0.65, 0.65));
	FRMask->SetRelativeScale3D(FVector(0.65, 0.65, 0.65));
	FLMask->SetRelativeScale3D(FVector(0.65, 0.65, 0.65));
	BRMask->SetRelativeScale3D(FVector(0.65, 0.65, 0.65));
	BLMask->SetRelativeScale3D(FVector(0.65, 0.65, 0.65));


	FLAbsorver->SetConstrainedComponents(Body, NAME_None, FLAxle, NAME_None);
	FRAbsorver->SetConstrainedComponents(Body, NAME_None, FRAxle, NAME_None);
	BLAbsorver->SetConstrainedComponents(Body, NAME_None, BLAxle, NAME_None);
	BRAbsorver->SetConstrainedComponents(Body, NAME_None, BRAxle, NAME_None);
	CLAbsorver->SetConstrainedComponents(Body, NAME_None, CLAxle, NAME_None);
	CRAbsorver->SetConstrainedComponents(Body, NAME_None, CRAxle, NAME_None);


	FLSpiner->SetConstrainedComponents(FLAxle, NAME_None, FLWheel, NAME_None);
	FRSpiner->SetConstrainedComponents(FRAxle, NAME_None, FRWheel, NAME_None);
	BLSpiner->SetConstrainedComponents(BLAxle, NAME_None, BLWheel, NAME_None);
	BRSpiner->SetConstrainedComponents(BRAxle, NAME_None, BRWheel, NAME_None);
	CLSpiner->SetConstrainedComponents(CLAxle, NAME_None, CLWheel, NAME_None);
	CRSpiner->SetConstrainedComponents(CRAxle, NAME_None, CRWheel, NAME_None);

	SetCamera();
	MovementComponent->InitializeWheelsVariables(Body, FLWheel, FRWheel, BLWheel, BRWheel, CLWheel, CRWheel);

	BarrelMesh->SetRelativeLocation(FVector(95, 0, 0));
	BarrelMesh->SetRelativeScale3D(FVector(0.2, 0.2, 1));
	BarrelMesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	WeaponComponent->InitializeComponent(BarrelBase, Barrel, BarrelMesh);

	// Set Damage/HP Values
	CurrentHP = MaxHP;
}

void AVehicleBase::SetTeam(FName NewTeam)
{
	Team = NewTeam;
}


float AVehicleBase::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	CurrentHP -= DamageAmount;
	AController* Controller = GetController();
	if (IsDead() && Controller) {
		IsPossibleTarget = false;
		UnPossessed();
		if (Cast<ABaseAIController>(Controller))
		{
			Cast<ABaseAIController>(Controller)->LostPawn();
		}
		else if (Cast<ABasePlayerController>(Controller))
		{
			Cast<ABasePlayerController>(Controller)->LostPawn();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Could not cast to AI or Player Controller"));
			Controller->Destroy();
		}
	}
	return DamageAmount;
}

bool AVehicleBase::IsDead()
{
	if (CurrentHP == 0) {
		return true;
	}else if(CurrentHP<0){
		CurrentHP = 0;
		return true;
	}
	return false;
}

float AVehicleBase::GetMaxHP()
{
	return MaxHP;
}

float AVehicleBase::GetCurrentHP()
{
	return CurrentHP;
}

float AVehicleBase::GetHPRatio()
{
	return CurrentHP/MaxHP;
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
	Wheel->SetMassOverrideInKg(NAME_None, 20);
}

void AVehicleBase::SetAxles(USphereComponent * Axle)
{
	Axle->SetCollisionProfileName(FName("Axle"));
	Axle->SetSimulatePhysics(true);
	Axle->SetMassOverrideInKg(NAME_None, 1);
}

void AVehicleBase::SetAbsorvers(UPhysicsConstraintComponent * Absorver)
{
	Absorver->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	Absorver->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	Absorver->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 40);
	Absorver->SetLinearPositionDrive(true, true, true);
	Absorver->SetLinearVelocityDrive(true, true, true);
	Absorver->SetLinearDriveParams(2500, 500, 0);
	Absorver->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45);
	Absorver->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45);
	Absorver->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45);
}

void AVehicleBase::SetSpiners(UPhysicsConstraintComponent * Spiner)
{

	Spiner->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45);
	Spiner->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 45);
	Spiner->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45);
}

void AVehicleBase::InitializeComponents()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	FLMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("FLMask"));
	FRMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("FRMask"));
	BLMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("BLMask"));
	BRMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("BRMask"));
	CLMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("CLMask"));
	CRMask = CreateDefaultSubobject<UStaticMeshComponent>(FName("CRMask"));

	FLAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FLAbsorber"));
	FLWheel = CreateDefaultSubobject<USphereComponent>(FName("FLWheel"));
	BLAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BLAbsorber"));
	BLWheel = CreateDefaultSubobject<USphereComponent>(FName("BLWheel"));
	FRAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FRAbsorber"));
	FRWheel = CreateDefaultSubobject<USphereComponent>(FName("FRWheel"));
	BRAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BRAbsorber"));
	BRWheel = CreateDefaultSubobject<USphereComponent>(FName("BRWheel"));
	CRAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("CRAbsorber"));
	CRWheel = CreateDefaultSubobject<USphereComponent>(FName("CRWheel"));
	CLAbsorver = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("CLAbsorber"));
	CLWheel = CreateDefaultSubobject<USphereComponent>(FName("CLWheel"));


	FLSpiner = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FLSpiner"));
	FLAxle = CreateDefaultSubobject<USphereComponent>(FName("FLAxle"));
	BLSpiner = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BLSpiner"));
	BLAxle = CreateDefaultSubobject<USphereComponent>(FName("BLAxle"));
	FRSpiner = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FRSpiner"));
	FRAxle = CreateDefaultSubobject<USphereComponent>(FName("FRAxle"));
	BRSpiner = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BRSpiner"));
	BRAxle = CreateDefaultSubobject<USphereComponent>(FName("BRAxle"));
	CRSpiner = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("CRSpiner"));
	CRAxle = CreateDefaultSubobject<USphereComponent>(FName("CRAxle"));
	CLSpiner = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("CLSpiner"));
	CLAxle = CreateDefaultSubobject<USphereComponent>(FName("CLAxle"));



	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BarrelMesh"));
	BarrelBase = CreateDefaultSubobject<USceneComponent>(FName("BarrelBase"));
	Barrel = CreateDefaultSubobject<USceneComponent>(FName("Barrel"));

	Body->SetMobility(EComponentMobility::Movable);
	FLWheel->SetMobility(EComponentMobility::Movable);
	FRWheel->SetMobility(EComponentMobility::Movable);
	BLWheel->SetMobility(EComponentMobility::Movable);
	BRWheel->SetMobility(EComponentMobility::Movable);
	CLWheel->SetMobility(EComponentMobility::Movable);
	CRWheel->SetMobility(EComponentMobility::Movable);
	FLAxle->SetMobility(EComponentMobility::Movable);
	FRAxle->SetMobility(EComponentMobility::Movable);
	BLAxle->SetMobility(EComponentMobility::Movable);
	BRAxle->SetMobility(EComponentMobility::Movable);
	CLAxle->SetMobility(EComponentMobility::Movable);
	CRAxle->SetMobility(EComponentMobility::Movable);

	MovementComponent = CreateDefaultSubobject<UVehicleNavMovementComponent>(FName("MovementComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(FName("WeaponComponent"));
}

void AVehicleBase::AttachComponents()
{
	SetRootComponent(Body);

	SetWheelInPosition(FLWheel, FLAxle, FLAbsorver, FLSpiner, FLMask, FVector(87, -71, -85));
	SetWheelInPosition(FRWheel, FRAxle, FRAbsorver, FRSpiner, FRMask, FVector(87, 71, -85));
	SetWheelInPosition(BLWheel, BLAxle, BLAbsorver, BLSpiner, BLMask, FVector(-87, -71, -85));
	SetWheelInPosition(BRWheel, BRAxle, BRAbsorver, BRSpiner, BRMask, FVector(-87, 71, -85));
	SetWheelInPosition(CLWheel, CLAxle, CLAbsorver, CLSpiner, CLMask, FVector(0, -100, -85));
	SetWheelInPosition(CRWheel, CRAxle, CRAbsorver, CRSpiner, CRMask, FVector(0, 100, -85));

	BarrelBase->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	Barrel->AttachToComponent(BarrelBase, FAttachmentTransformRules::KeepRelativeTransform);
	BarrelMesh->AttachToComponent(Barrel, FAttachmentTransformRules::KeepRelativeTransform);
}

void AVehicleBase::SetWheelInPosition(USphereComponent * Wheel, USphereComponent * Axle, UPhysicsConstraintComponent * Absorver, UPhysicsConstraintComponent * Spiner, UStaticMeshComponent * Mask, FVector Position)
{
	Absorver->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	Absorver->SetRelativeLocation(Position);
	Axle->AttachToComponent(Absorver, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	Spiner->AttachToComponent(Wheel, FAttachmentTransformRules::KeepRelativeTransform);
	Mask->AttachToComponent(Wheel, FAttachmentTransformRules::KeepRelativeTransform);
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



