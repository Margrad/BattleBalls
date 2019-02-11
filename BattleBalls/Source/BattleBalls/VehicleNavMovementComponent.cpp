// All Copyrights reserved to Marco Granada.

#include "VehicleNavMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

void UVehicleNavMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector DirectionToGo = MoveVelocity.GetSafeNormal();
	FVector DirectionFacing = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float Throttle = FVector::DotProduct(DirectionToGo, DirectionFacing);
	IntendMoveForward(Throttle);

	Throttle = FVector::CrossProduct(DirectionFacing, DirectionToGo).Z;
	IntendTurnRight(Throttle);
}


void UVehicleNavMovementComponent::IntendMoveForward(float ThrottleIn)
{

	float Throttle = FMath::Clamp<float>(ThrottleIn, -1, 1);
	float CurrentSpeed;
	CurrentSpeed = GetOwner()->GetVelocity().Size();
	float ratio = CurrentSpeed / MaxSpeed;
	ratio = FMath::Clamp<float>(ratio, 0, 1);
	Throttle = Throttle * (1 - ratio);
	FLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	FRWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	BLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	BRWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
}

void UVehicleNavMovementComponent::IntendTurnRight(float ThrottleIn)
{
	float Throttle = FMath::Clamp<float>(ThrottleIn, -1, 1);
	float CurrentAngularSpeed = FMath::Abs(Body->GetPhysicsAngularVelocityInDegrees().Z);
	float ratio = CurrentAngularSpeed / MaxRotation;
	ratio = FMath::Clamp<float>(ratio, 0, 1);
	Throttle *= (1 - ratio);
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);

	FLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	FRWheel->AddForce(Body->GetForwardVector()*Throttle*-BaseThrottle);
	BLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	BRWheel->AddForce(Body->GetForwardVector()*Throttle*-BaseThrottle);
}

void UVehicleNavMovementComponent::GetBackUpSide()
{
	// TODO fix this function.
	FRotator CurrentRotation = GetOwner()->GetRootComponent()->GetComponentRotation();//GetActorRotation();
	FVector Position = GetOwner()->GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Pre jump: %s"), *Position.ToString());
	Position.Z += 300.0;
	if (FMath::Abs(CurrentRotation.Roll) > 120 ) {
		GetOwner()->SetActorLocation(Position, true, nullptr, ETeleportType::ResetPhysics);
		GetOwner()->SetActorRotation(FRotator(0, 0, 0), ETeleportType::None);
	}

}

void UVehicleNavMovementComponent::InitializeVariable(UStaticMeshComponent * Bdy, USphereComponent * FL, USphereComponent * FR, USphereComponent * BL, USphereComponent * BR)
{
		Body=Bdy;
		FLWheel=FL;
		BLWheel=BL;
		FRWheel=FR;
		BRWheel=BR;
}


