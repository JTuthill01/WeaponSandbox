#include "Pickups/Weapons/WeaponPickup/WeaponPickup.h"
#include "Character/Player/PlayerCharacter.h"
#include "Weapons/Base/WeaponBase.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponPickup::InteractableFound_Implementation()
{
	
}

void AWeaponPickup::InteractWithObject_Implementation(APlayerCharacter* PlayerRef)
{
	PlayerRef->SpawnWeapon(WeaponToSpawn, PlayerRef->GetActorLocation());

	if (!PlayerRef->GetHasWeapon())
		Destroy();
}


