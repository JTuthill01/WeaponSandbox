#pragma once

UENUM(BlueprintType)
enum class EFireMode : uint8 { EFM_SemiAuto UMETA(DisplayName = "Semi Auto"), EFM_FullAuto UMETA(DisplayName = "Full Auto") };

UENUM(BlueprintType)
enum class EWeaponType : uint8 { EWT_Unarmed UMETA(DisplayName = "Unarmed"), EWT_Pistol UMETA(DisplayName = "Pistol"), EWT_SMG UMETA(DisplayName = "SMG"), EWT_Rifle UMETA(DisplayName = "Rifle")  };

UENUM(BlueprintType)
enum class EWeaponClass : uint8 { EWC_Unarmed, EWC_Primary, EWC_Secondary };

UENUM(BlueprintType)
enum class EWeaponName : uint8 { EWN_Unarmed UMETA(DisplayName = "Unarmed"), EWN_Pistol UMETA(DisplayName = "Pistol"), EWN_BelgianAR UMETA(DisplayName = "BelgianAR") };