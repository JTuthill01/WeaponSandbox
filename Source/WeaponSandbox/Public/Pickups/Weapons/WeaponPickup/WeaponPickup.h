#pragma once

#include "CoreMinimal.h"
#include "Pickups/Base/PickupBase.h"
#include "WeaponPickup.generated.h"

UCLASS()
class WEAPONSANDBOX_API AWeaponPickup : public APickupBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponPickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractableFound_Implementation() override;
	
	virtual void InteractWithObject_Implementation(APlayerCharacter* PlayerRef) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	TSubclassOf<class AWeaponBase> WeaponToSpawn;
};
