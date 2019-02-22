// All Copyrights reserved to Marco Granada.

#include "WeaponComponent.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VehicleBase.h"

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
	FRotator CurrentAim = Barrel->GetForwardVector().Rotation();
	FRotator DestineAim = PointToAim.GetSafeNormal().Rotation();
	FRotator DifRotation = DestineAim - CurrentAim;
	
	// Elevate Barrel
	float DifPitch = FMath::Clamp<float>(DifRotation.Pitch,-1,1);
	//float DifPitch = DifRotation.Pitch;
	float DeltaT = GetWorld()->DeltaTimeSeconds;
	float DifElevation =  DifPitch* MaxElevationSpeed * DeltaT;
	float RawNewElevation = DifPitch + Barrel->RelativeRotation.Pitch;
	RawNewElevation = FMath::Clamp<float>(RawNewElevation, -3, 75);
	Barrel->SetRelativeRotation(FRotator(RawNewElevation, 0, 0));

	// Rotate Barrel
	if (FMath::Abs(DifRotation.Yaw) < 180) {
		DifRotation.Yaw *= -1;
	}
	float DifYaw = FMath::Clamp<float>(-DifRotation.Yaw, -1, 1);
	//float DifYaw = DifRotation.Yaw;
	float DifRot = DifYaw * MaxRotationSpeed * DeltaT;
	float RawNewRotation = BarrelBase->RelativeRotation.Yaw + DifRot;
	BarrelBase->SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

void UWeaponComponent::AutoAimAt(FVector Target)
{
	if (!ensure(Barrel)) {
		return;
	}

	auto BarrelLocation = Barrel->GetSocketLocation(FName("FireMouth"));
	FVector OUTSugestedVelocity;
	FCollisionResponseParams CollisionResponseParems = FCollisionResponseParams();
	TArray<AActor*> IgnoredActores;
	IgnoredActores.Add(GetOwner());
	bool bTrajectoryFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT OUTSugestedVelocity,
		BarrelLocation,
		Target,
		10000,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		CollisionResponseParems,
		IgnoredActores,
		false
	);
	if (bTrajectoryFound)
	{
		auto AimDirection = OUTSugestedVelocity.GetSafeNormal()+Cast<AVehicleBase>(GetOwner())->GetAimBias();
		MoveBarrel(AimDirection);
	}
}

void UWeaponComponent::AutoAimAtActor(AActor * Target)
{
	FVector AimAtLocation = Target->GetActorLocation();
	AutoAimAt(AimAtLocation);
}


bool UWeaponComponent::Fire()
{
	if(GetWorld()->TimeSeconds >= NextShotTime )
	{
		auto Location = BarrelMesh->GetSocketLocation(FName("FireMouth"));
		auto Rotation = BarrelMesh->GetSocketRotation(FName("FireMouth"));
		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileBP, Location, Rotation);
		NextShotTime = GetWorld()->TimeSeconds + ReloadTime;
		return true;
	}
	return false;
}

