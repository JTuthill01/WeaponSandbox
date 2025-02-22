#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PlayerCharacterController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class WEAPONSANDBOX_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerCharacterController();

	virtual void SetupInputComponent() override;

protected:

	virtual void BeginPlay() override;

#pragma region INPUT
	
	//Input Actions//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> WeaponFireAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> ZeroKeyAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> OneKeyAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> TwoKeyAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> ScrollAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> OpenWeaponWidgetAction;

	//Mapping Contexts//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InputMappings)
	TObjectPtr<UInputMappingContext> BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InputMappings)
	int32 BaseMappingPriority = 0;

	//Input Functions//
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Scroll(const FInputActionValue& Value);
	void Jump();
	void StopJump();
	void Interact();
	void WeaponFire();
	void StopWeaponFire();
	void OpenCloseWeaponWidget();
	//void ZeroKey();
	//void OneKey();
	//void TwoKey();
	
#pragma endregion

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY()
	TObjectPtr<class UWeaponSwitchWidget> WeaponWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UWeaponSwitchWidget> WeaponWidgetClass;

	bool bCanFire;
	bool bIsWeaponWidgetOpen;
};
