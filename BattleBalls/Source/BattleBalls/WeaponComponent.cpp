// All Copyrights reserved to Marco Granada.

#include "WeaponComponent.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::InitializeComponent(USceneComponent* BarrelBaseToSet, USceneComponent* BarrelToSet, UStaticMeshComponent* BarrelMeshToSet)
{
	Barrel = BarrelToSet;
	BarrelMesh = BarrelMeshToSet;
	BarrelBase = BarrelBaseToSet;
}

void UWeaponComponent::MoveBarrel(FVector PointToAim)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(BarrelBase)) { return; }
	if (!ensure(BarrelMesh)) { return; }

	// Get Move difference
	FRotator CurrentAim = BarrelMesh->GetForwardVector().Rotation();
	FRotator DestineAim = PointToAim.Rotation();
	FRotator DifRotation = DestineAim - CurrentAim;

	// Elevate Barrel
	float DifPitch = FMath::Clamp<float>(DifRotation.Pitch,-1,1);
	float DeltaT = GetWorld()->DeltaTimeSeconds;
	float DifElevation =  DifPitch* MaxElevationSpeed * DeltaT;
	float RawNewElevation = DifPitch + DifElevation;
	RawNewElevation = FMath::Clamp<float>(RawNewElevation, -15, 45);
	Barrel->SetRelativeRotation(FRotator(RawNewElevation, 0, 0));

	// Rotate Barrel
	float DifYaw = FMath::Clamp<float>(DifRotation.Yaw, -1, 1);
	float DifRot = DifYaw * MaxRotationSpeed * DeltaT;
	float RawNewRotation = DifYaw + DifRot;
	BarrelBase->SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

void UWeaponComponent::AIAimAt(FVector Target)
{
}


void UWeaponComponent::Fire()
{
	auto Location = BarrelMesh->GetSocketLocation(FName("FireMouth"));
	auto Rotation = BarrelMesh->GetSocketRotation(FName("FireMouth"));
	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileBP,Location,Rotation);
}

