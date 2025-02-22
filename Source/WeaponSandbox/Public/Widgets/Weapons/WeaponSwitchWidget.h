#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSwitchWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class WEAPONSANDBOX_API UWeaponSwitchWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UWeaponSwitchWidget(const FObjectInitializer& Object);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Slot_1_Image;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Slot_2_Image;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Images, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> DefaultImage;
};
