// All Copyrights reserved to Marco Granada.

#include "VehicleNavMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

void UVehicleNavMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector DirectionToGo = MoveVelocity.GetSafeNormal();
	FVector DirectionFacing = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float DotProd = FVector::DotProduct(DirectionToGo, DirectionFacing);
	float CrossProd = FVector::CrossProduct(DirectionFacing, DirectionToGo).Z;

	// Simple way to move forward
	IntendMoveForward(DotProd);

	// Complex way to turn, turns faster  when the move to location is behind the pawn
	//          ^
	//   ------1|---..
	//          |      \
	//          |       .
	// ---------|-------|------>
	//  -1      |       1
	//          |      /
	//   ---- -1|---''

	if (DotProd < 0)
	{
		if (CrossProd > 0)
		{
			IntendTurnRight(1);
		}
		else {
			IntendTurnRight(-1);
		}
	}
	else {
		IntendTurnRight(CrossProd);
	}
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
	CLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	CRWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
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
	CLWheel->AddForce(Body->GetForwardVector()*Throttle*BaseThrottle);
	CRWheel->AddForce(Body->GetForwardVector()*Throttle*-BaseThrottle);
}

void UVehicleNavMovementComponent::GetBackUpSide()
{

	FRotator CurrentRotation = GetOwner()->GetRootComponent()->GetComponentRotation();
	FVector Position = GetOwner()->GetActorLocation();
	while (FMath::Abs(CurrentRotation.Roll) > 120) {
		Position.Z += 1000.0;
		GetOwner()->SetActorLocation(Position, true, nullptr, ETeleportType::None);
		CurrentRotation.Roll = 0;
		GetOwner()->SetActorRotation(CurrentRotation, ETeleportType::ResetPhysics);
		Position.Z -= 990.0;
		GetOwner()->SetActorLocation(Position, true, nullptr, ETeleportType::ResetPhysics);
		CurrentRotation = GetOwner()->GetRootComponent()->GetComponentRotation();
	}
}


void UVehicleNavMovementComponent::InitializeWheelsVariables(UStaticMeshComponent * Bdy, USphereComponent * FL, USphereComponent * FR, USphereComponent * BL, USphereComponent * BR, USphereComponent * CL, USphereComponent * CR)
{
		Body=Bdy;
		FLWheel=FL;
		BLWheel=BL;
		FRWheel = FR;
		BRWheel = BR;
		CRWheel = CR;
		CLWheel = CL;
}


