#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Player/PlayerCharacterInterface.h"
#include "Weapons/Enums/WeaponEnums.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClearViewport);

UCLASS()
class WEAPONSANDBOX_API APlayerCharacter : public ACharacter, public IPlayerCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

#pragma region Getters

	FORCEINLINE TObjectPtr<USkeletalMeshComponent> GetPlayerArms() const { return Arms; }
	FORCEINLINE TObjectPtr<class UCameraComponent> GetPlayerCamera() const { return Camera; }
	FORCEINLINE TMap<EWeaponClass, class AWeaponBase*> GetCurrentWeapon() const { return Weapons; }
	FORCEINLINE TMap<EWeaponType, class AWeaponBase*> GetCurrentWeaponMap() const { return WeaponMap; }
	FORCEINLINE bool GetHasWeapon() const { return bHasWeapon; }
	FORCEINLINE EWeaponClass GetWeaponClass() const { return WeaponClass; }
	FORCEINLINE EWeaponType GetCurrentWeaponType() const { return WeaponType; }

#pragma endregion

#pragma region Setters

	FORCEINLINE void SetWeaponClass(const EWeaponClass NewClass) { WeaponClass = NewClass; }
	FORCEINLINE void SetWeaponName(const EWeaponName InName) { WeaponName = InName; }
	FORCEINLINE void SetWeaponType(const EWeaponType InType) { WeaponType = InType; }

#pragma endregion

#pragma region Virtual Functions
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual APlayerCharacter* GetPlayerRef_Implementation() override;

	//Player Death
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion

#pragma region Public Functions
	
	void InteractWithObject();

	void WeaponFire();

	void SpawnWeapon(TSubclassOf<AWeaponBase> WeaponToSpawn, FVector Location);

	void SetWeaponVisibility(EWeaponClass InType);

	void SetWeaponVisibility(EWeaponType InType);

	bool GetWeaponInfo(EWeaponClass InClass, AWeaponBase*& OutWeapon, EWeaponType& OutType);

	bool GetWeaponType(EWeaponType InWeaponTypeEnum, AWeaponBase*& WeaponTypeOut, EWeaponType& OutWeaponTypeEnum);

#pragma endregion

	UPROPERTY(BlueprintAssignable)
	FOnClearViewport Clear;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
#pragma region Private Functions

	void ScanForInteractable();
#pragma endregion

#pragma region Variables
	UPROPERTY()
	AWeaponBase* CurrentType; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimSequence> PlayerWeaponFire;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponClass, AWeaponBase*> Weapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponType, AWeaponBase*> WeaponMap;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SK_Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Arms;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	EWeaponName WeaponName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	EWeaponClass WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	double InteractableTraceTimer;

	bool bHasWeapon;
	
	FTimerHandle InteractableTraceTimerHandle;
#pragma endregion
};
