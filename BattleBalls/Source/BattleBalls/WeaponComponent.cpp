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

void UWeaponComponent::InitializeComponent(USceneComponent* BarrelToSet, UStaticMeshComponent* BarrelMeshToSet)
{
	Barrel = BarrelToSet;
	BarrelMesh = BarrelMeshToSet;
}

void UWeaponComponent::Fire()
{
	auto Location = BarrelMesh->GetSocketLocation(FName("FireMouth"));
	auto Rotation = BarrelMesh->GetSocketRotation(FName("FireMouth"));
	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileBP,Location,Rotation);
}

