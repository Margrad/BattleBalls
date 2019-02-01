// All Copyrights reserved to Marco Granada.

#include "BasePlayerController.h"
#include "Public/DrawDebugHelpers.h"
#include "WeaponComponent.h"
#include "Components/StaticMeshComponent.h"

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto WeaponComponent = GetPawn()->FindComponentByClass<UWeaponComponent>();
	if (!ensure(WeaponComponent)) { return; }
	FVector AimingAt = CrossAimingAt();
	WeaponComponent->AutoAimAt(AimingAt);
}

FVector ABasePlayerController::CrossAimingAt() {
	int32 Xsize, Ysize;
	GetViewportSize(Xsize,Ysize);
	FVector StartPosition;
	FVector WorldDirection;

	UWeaponComponent* Weapon = GetPawn()->FindComponentByClass<UWeaponComponent>();
	FVector FireMouthPosition;
	FRotator FireMouthRotator;
	Weapon->GetBarrel()->GetSocketWorldLocationAndRotation(FName("FireMouth"), FireMouthPosition, FireMouthRotator);

	DeprojectScreenPositionToWorld(Xsize*0.5, Yratio*Ysize, StartPosition, WorldDirection);
	StartPosition = PlayerCameraManager->GetCameraLocation();

	FHitResult HitObject;
	FVector EndPosition = StartPosition + WorldDirection * 50000;
	FVector AimingAt;
	if (GetWorld()->LineTraceSingleByChannel( // Do the line trace
		OUT HitObject,
		OUT StartPosition,
		OUT EndPosition,
		ECollisionChannel::ECC_Camera // Uses the visibility channel(not using glass I suposse)
	)) {
		AimingAt = HitObject.Location;
	}
	else {
		AimingAt = StartPosition + WorldDirection * 20000;
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Postion: %s  Direction: %s"), *WorldPostion.ToString(), *WorldDirection.ToString());
	return AimingAt;
}
