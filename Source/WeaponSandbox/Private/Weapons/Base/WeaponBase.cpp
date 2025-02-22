#include "Weapons/Base/WeaponBase.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

AWeaponBase::AWeaponBase() : Damage(0.0), Range(0.0), WeaponType(EWeaponType::EWT_Pistol), WeaponClass(EWeaponClass::EWC_Unarmed),  WeaponName(EWeaponName::EWN_Pistol),
	PickupClass(nullptr), SocketName(NAME_None)
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetCastShadow(false);

	SetRootComponent(BaseMesh);
}

void AWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AWeaponBase::WeaponFire(const TObjectPtr<APlayerCharacter>& PlayerRef)
{
	BulletTrace(PlayerRef);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::BulletTrace(const TObjectPtr<APlayerCharacter>& InRef)
{
	FHitResult HitResult;

	FVector Start{ BaseMesh->GetSocketLocation("Fire_FX_Slot") };
	FVector Rotation{ BaseMesh->GetSocketRotation("Fire_FX_Slot").Vector() };
	FVector End{ Start + Rotation * 10'000.F };

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Emplace(InRef);
	ActorsToIgnore.Emplace(this);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TraceObjects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	const bool& bHasBeenHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);
}
