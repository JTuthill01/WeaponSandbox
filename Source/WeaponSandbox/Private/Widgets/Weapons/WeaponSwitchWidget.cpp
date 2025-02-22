#include "Widgets/Weapons/WeaponSwitchWidget.h"

#include "Components/Image.h"

UWeaponSwitchWidget::UWeaponSwitchWidget(const FObjectInitializer& Object) : Super(Object)
{
}

void UWeaponSwitchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Slot_1_Image->SetBrushFromTexture(DefaultImage);

	Slot_2_Image->SetBrushFromTexture(DefaultImage);
}
