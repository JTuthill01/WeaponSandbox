#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/Enums/WeaponEnums.h"
#include "WeaponBase.generated.h"

UCLASS()
class WEAPONSANDBOX_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

#pragma region Getters

	FORCEINLINE TSubclassOf<class AWeaponPickup> GetPickupClass() const { return PickupClass; }
	FORCEINLINE FName GetSocketName() const { return SocketName; }
	FORCEINLINE EWeaponClass GetWeaponClass() const { return WeaponClass; }
	FORCEINLINE EWeaponName GetWeaponName() const { return WeaponName; }
	FORCEINLINE EWeaponType GetWeaponType() const { return  WeaponType; }
	FORCEINLINE TObjectPtr<USkeletalMeshComponent> GetBaseMesh()const { return BaseMesh; }
	FORCEINLINE TObjectPtr<UAnimSequence> GetFireSequence() const { return FireSequence; }

#pragma endregion

#pragma region BP Getters

	UFUNCTION(BlueprintPure, BlueprintCallable)
	EWeaponName GetCurrentWeaponEnumNameBP() { return WeaponName; }
	
#pragma endregion

#pragma region Setters

	void SetWeaponType(const EWeaponType InType) { WeaponType = InType; }

#pragma endregion

	virtual void Tick(float DeltaSeconds) override;

	void WeaponFire(const TObjectPtr<class APlayerCharacter>& PlayerRef);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BulletTrace(const TObjectPtr<APlayerCharacter>& InRef);

#pragma region Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	TObjectPtr<USkeletalMeshComponent> BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	TObjectPtr<UAnimSequence> FireSequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	double Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	double Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	EWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	EWeaponClass WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	EWeaponName WeaponName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	TSubclassOf<AWeaponPickup> PickupClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Variables)
	FName SocketName;

#pragma endregion
};
