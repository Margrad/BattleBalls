// Fill out your copyright notice in the Description page of Project Settings.

#include "MotionAbsovingWheels.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include"Components/SphereComponent.h"

// Sets default values
AMotionAbsovingWheels::AMotionAbsovingWheels()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
	if (PrimaryActorTick.TickGroup = TG_PostPhysics) {

	}

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	ShockAbsorber = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	WheelRotationAllower = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axel Constraint"));


	SetRootComponent(ShockAbsorber);
	Axel->SetupAttachment(ShockAbsorber);
	Wheel->SetupAttachment(Axel);
	WheelRotationAllower->SetupAttachment(Axel);
}

// Called when the game starts or when spawned
void AMotionAbsovingWheels::BeginPlay()
{
	Super::BeginPlay();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &AMotionAbsovingWheels::IsToucnhingGround);

	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	ShockAbsorber->SetConstrainedComponents(BodyRoot, NAME_None, Axel, NAME_None);
	WheelRotationAllower->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);
	
}

// Called every frame
void AMotionAbsovingWheels::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics) {
		TotalThrottleMultiplier = 0;
	}
}

void AMotionAbsovingWheels::IsToucnhingGround(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	Wheel->AddForce(Axel->GetForwardVector()*TotalThrottleMultiplier*BaseWheelThrottle);
}

