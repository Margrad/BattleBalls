// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PrototypeV2.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACPP_PrototypeV2::ACPP_PrototypeV2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initiate all required components
	InitializeComponents();
	AttachComponents();
	
	SetAxelConstrains(FLAxelConstrain);
	SetAxelConstrains(BLAxelConstrain);
	SetAxelConstrains(FRAxelConstrain);
	SetAxelConstrains(BRAxelConstrain);
	

}

// Called when the game starts or when spawned
void ACPP_PrototypeV2::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_PrototypeV2::SetAxelConstrains(UPhysicsConstraintComponent * AxelConstrain)
{
	AxelConstrain->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45);
	AxelConstrain->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 45);
	AxelConstrain->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45);
	AxelConstrain->SetLinearXLimit(ELinearConstraintMotion::LCM_Limited, 15);
	AxelConstrain->SetLinearYLimit(ELinearConstraintMotion::LCM_Limited, 15);
	AxelConstrain->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 15);
	AxelConstrain->SetLinearPositionDrive(true, true, true);
	AxelConstrain->SetLinearVelocityDrive(true, true, true);
}

void ACPP_PrototypeV2::InitializeComponents()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	//FLAbsorber = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FLAbsorber"));
	//FLAxel = CreateDefaultSubobject<USphereComponent>(FName("FLAxel"));
	FLAxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FLAxelConstrain"));
	FLWheel = CreateDefaultSubobject<USphereComponent>(FName("FLWheel"));
	//BLAbsorber = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BLAbsorber"));
	//BLAxel = CreateDefaultSubobject<USphereComponent>(FName("BLAxel"));
	BLAxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BLAxelConstrain"));
	BLWheel = CreateDefaultSubobject<USphereComponent>(FName("BLWheel"));
	//FRAbsorber = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FRAbsorber"));
	//FRAxel = CreateDefaultSubobject<USphereComponent>(FName("FRAxel"));
	FRAxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("FRAxelConstrain"));
	FRWheel = CreateDefaultSubobject<USphereComponent>(FName("FRWheel"));
	//BRAbsorber = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BRAbsorber"));
	//BRAxel = CreateDefaultSubobject<USphereComponent>(FName("BRAxel"));
	BRAxelConstrain = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("BRAxelConstrain"));
	BRWheel = CreateDefaultSubobject<USphereComponent>(FName("BRWheel"));
}

void ACPP_PrototypeV2::AttachComponents()
{
	SetRootComponent(Body);
	FLAxelConstrain->AttachToComponent(Body,FAttachmentTransformRules::KeepRelativeTransform);
	FLAxelConstrain->SetRelativeLocation(FVector(55, -55, -30));
	FLWheel->AttachToComponent(FLAxelConstrain, FAttachmentTransformRules::KeepRelativeTransform);
	//FLAxel->AttachToComponent(FLAbsorber, FAttachmentTransformRules::KeepRelativeTransform);
	//FLAxelConstrain->AttachToComponent(FLWheel, FAttachmentTransformRules::KeepRelativeTransform);
	FRAxelConstrain->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	FRAxelConstrain->SetRelativeLocation(FVector(55, 55, -30));
	FRWheel->AttachToComponent(FRAxelConstrain, FAttachmentTransformRules::KeepRelativeTransform);

	BLAxelConstrain->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	BLAxelConstrain->SetRelativeLocation(FVector(-55, -55, -30));
	BLWheel->AttachToComponent(BLAxelConstrain, FAttachmentTransformRules::KeepRelativeTransform);

	BRAxelConstrain->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	BRAxelConstrain->SetRelativeLocation(FVector(-55, 55, -30));
	BRWheel->AttachToComponent(BRAxelConstrain, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void ACPP_PrototypeV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_PrototypeV2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

