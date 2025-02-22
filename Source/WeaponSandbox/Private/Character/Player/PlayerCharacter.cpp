#include "Character/Player/PlayerCharacter.h"
#include "Interfaces/Interact/InteractInterface.h"
#include "Weapons/Base/WeaponBase.h"
#include "Pickups/Weapons/WeaponPickup/WeaponPickup.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : WeaponName(EWeaponName::EWN_Unarmed), WeaponClass(EWeaponClass::EWC_Unarmed), WeaponType(EWeaponType::EWT_Unarmed),
	InteractableTraceTimer(0.25), bHasWeapon(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);
	Arms->SetCastShadow(false);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(InteractableTraceTimerHandle, this, &APlayerCharacter::ScanForInteractable, InteractableTraceTimer, true);

	//AWeaponBase* TempWeapon;

	//Weapons.Emplace(WeaponClass, TempWeapon);
	//WeaponMap.Emplace(WeaponType, TempWeapon);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearAllTimersForObject(this);
}

void APlayerCharacter::InteractWithObject()
{
	const FVector Start = Camera->GetComponentLocation();
	const FVector End = Start + (Camera->GetComponentRotation().Vector() * 400.F);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Emplace(this);

	TraceObjects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	
	if (FHitResult HitResult; UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
				IInteractInterface::Execute_InteractWithObject(HitResult.GetActor(), this);
		}
	}
}

void APlayerCharacter::WeaponFire()
{
	if (WeaponType != EWeaponType::EWT_Unarmed)
	{
		WeaponMap[WeaponType]->GetBaseMesh()->PlayAnimation(WeaponMap[WeaponType]->GetFireSequence(), false);

		WeaponMap[WeaponType]->WeaponFire(this);

		//Arms->PlayAnimation(PlayerWeaponFire, false);
	}
}

/*
void APlayerCharacter::SpawnWeapon(TSubclassOf<AWeaponBase> WeaponToSpawn, FVector Location)
{
	WeaponClass = WeaponToSpawn->GetDefaultObject<AWeaponBase>()->GetWeaponClass();

	FVector PickupLocation{GetActorLocation() + (GetActorRotation().Vector() * 40.F)};

	FTransform PickupTransform = UKismetMathLibrary::MakeTransform(PickupLocation, FRotator::ZeroRotator);
	
	if (IsValid(CurrentType))
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (bHasWeapon = Weapons.Contains(WeaponClass); !bHasWeapon)
		{
			CurrentType->GetBaseMesh()->SetVisibility(false);
			
			if (CurrentType = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, Location, GetActorRotation(), Params); IsValid(CurrentType))
			{
				Weapons.Emplace(CurrentType->GetWeaponClass(),CurrentType);
			
				if (auto&& SpawnedPickup = GetWorld()->SpawnActor<AWeaponPickup>(CurrentType->GetPickupClass(), PickupTransform); IsValid(SpawnedPickup))
				{
					Weapons[CurrentType->GetWeaponClass()]->AttachToComponent(Arms, FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentType->GetSocketName());

					WeaponClass = CurrentType->GetWeaponClass();

					WeaponName = CurrentType->GetWeaponName();

					CurrentType->GetBaseMesh()->SetVisibility(true);
				}
			}
		}
	}

	if (!IsValid(CurrentType))
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (CurrentType = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, Location, GetActorRotation(), Params); IsValid(CurrentType))
		{
			if (auto&& SpawnedPickup = GetWorld()->SpawnActor<AWeaponPickup>(CurrentType->GetPickupClass(), PickupTransform); IsValid(SpawnedPickup))
			{
				Weapons.Emplace(CurrentType->GetWeaponClass(),CurrentType);
			
				Weapons[CurrentType->GetWeaponClass()]->AttachToComponent(Arms, FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentType->GetSocketName());

				WeaponName = CurrentType->GetWeaponName();

				WeaponClass = CurrentType->GetWeaponClass();
			}
		}
	}
} */

void APlayerCharacter::SpawnWeapon(TSubclassOf<AWeaponBase> WeaponToSpawn, FVector Location)
{
	WeaponType = WeaponToSpawn->GetDefaultObject<AWeaponBase>()->GetWeaponType();

	FVector PickupLocation{GetActorLocation() + (GetActorRotation().Vector() * 40.F)};

	FTransform PickupTransform = UKismetMathLibrary::MakeTransform(PickupLocation, FRotator::ZeroRotator);
	
	if (IsValid(CurrentType))
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (bHasWeapon = WeaponMap.Contains(WeaponType); !bHasWeapon)
		{
			CurrentType->GetBaseMesh()->SetVisibility(false);
			
			if (CurrentType = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, Location, GetActorRotation(), Params); IsValid(CurrentType))
			{
				WeaponMap.Emplace(CurrentType->GetWeaponType(),CurrentType);
			
				if (auto&& SpawnedPickup = GetWorld()->SpawnActor<AWeaponPickup>(CurrentType->GetPickupClass(), PickupTransform); IsValid(SpawnedPickup))
				{
					WeaponMap[CurrentType->GetWeaponType()]->AttachToComponent(Arms, FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentType->GetSocketName());

					WeaponType = CurrentType->GetWeaponType();

					WeaponName = CurrentType->GetWeaponName();

					WeaponClass = CurrentType->GetWeaponClass();

					CurrentType->GetBaseMesh()->SetVisibility(true);
				}
			}
		}
	}

	if (!IsValid(CurrentType))
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (CurrentType = GetWorld()->SpawnActor<AWeaponBase>(WeaponToSpawn, Location, GetActorRotation(), Params); IsValid(CurrentType))
		{
			if (auto&& SpawnedPickup = GetWorld()->SpawnActor<AWeaponPickup>(CurrentType->GetPickupClass(), PickupTransform); IsValid(SpawnedPickup))
			{
				WeaponMap.Emplace(CurrentType->GetWeaponType(),CurrentType);
			
				WeaponMap[CurrentType->GetWeaponType()]->AttachToComponent(Arms, FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentType->GetSocketName());

				WeaponName = CurrentType->GetWeaponName();

				WeaponClass = CurrentType->GetWeaponClass();

				WeaponType = CurrentType->GetWeaponType();
			}
		}
	}
}

void APlayerCharacter::SetWeaponVisibility(const EWeaponClass InType)
{
	if (Weapons.IsEmpty())
		return;

	TArray<EWeaponClass> OutKeys;
	Weapons.GetKeys(OutKeys);

	if (!OutKeys.IsEmpty())
	{
		for (int32 i = 0; i < OutKeys.Num(); ++i)
		{
			if (OutKeys[i] != InType)
			{
				if (IsValid(Weapons[OutKeys[i]]))
					Weapons[OutKeys[i]]->GetBaseMesh()->SetVisibility(false);
			}

			else if (OutKeys[i] == InType)
			{
				if (IsValid(Weapons[OutKeys[i]]))
					Weapons[OutKeys[i]]->GetBaseMesh()->SetVisibility(true);
			}
		}
	}
}

void APlayerCharacter::SetWeaponVisibility(const EWeaponType InType)
{
	if (WeaponMap.IsEmpty())
		return;

	TArray<EWeaponType> OutKeys;
	WeaponMap.GetKeys(OutKeys);

	if (!OutKeys.IsEmpty())
	{
		for (int32 i = 0; i < OutKeys.Num(); ++i)
		{
			if (OutKeys[i] != InType)
			{
				if (IsValid(WeaponMap[OutKeys[i]]))
					WeaponMap[OutKeys[i]]->GetBaseMesh()->SetVisibility(false);
			}

			else if (OutKeys[i] == InType)
			{
				if (IsValid(WeaponMap[OutKeys[i]]))
					WeaponMap[OutKeys[i]]->GetBaseMesh()->SetVisibility(true);
			}
		}
	}
}

bool APlayerCharacter::GetWeaponInfo(const EWeaponClass InClass, AWeaponBase*& OutWeapon, EWeaponType& OutType)
{
	bool bWasSuccessful;
	
	if (Weapons.IsEmpty())
		return bWasSuccessful = false;

	OutWeapon = *Weapons.Find(InClass);

	OutType = Weapons[InClass]->GetWeaponType();

	bWasSuccessful = Weapons.Contains(InClass);

	return bWasSuccessful;
}

bool APlayerCharacter::GetWeaponType(const EWeaponType InWeaponTypeEnum, AWeaponBase*& WeaponTypeOut, EWeaponType& OutWeaponTypeEnum)
{
	bool bWasSuccessful;
	
	if (WeaponMap.IsEmpty())
		return bWasSuccessful = false;

	WeaponTypeOut = *WeaponMap.Find(InWeaponTypeEnum);

	OutWeaponTypeEnum = WeaponMap[InWeaponTypeEnum]->GetWeaponType();

	bWasSuccessful = WeaponMap.Contains(InWeaponTypeEnum);

	return bWasSuccessful;
}

void APlayerCharacter::ScanForInteractable()
{
	const FVector Start = Camera->GetComponentLocation();
	const FVector End = Start + (Camera->GetComponentRotation().Vector() * 400.F);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Emplace(this);

	TraceObjects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	if (FHitResult HitResult; UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
				IInteractInterface::Execute_InteractableFound(HitResult.GetActor());
		}
	}
}

APlayerCharacter* APlayerCharacter::GetPlayerRef_Implementation() { return this; }


