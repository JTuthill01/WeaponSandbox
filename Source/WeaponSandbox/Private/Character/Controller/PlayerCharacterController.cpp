#include "WeaponSandbox/Public/Character/Controller/PlayerCharacterController.h"
#include "Character/Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Base/WeaponBase.h"
#include "Widgets/Weapons/WeaponSwitchWidget.h"

APlayerCharacterController::APlayerCharacterController() : bCanFire(true), bIsWeaponWidgetOpen(false)
{
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)); 
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
		Subsystem->ClearAllMappings();

		// Add each mapping context, along with their priority values. Higher values out prioritize lower values.
		Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
	}

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacterController::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopJump);
		}

		if (WeaponFireAction)
		{
			PlayerEnhancedInputComponent->BindAction(WeaponFireAction, ETriggerEvent::Started, this, &APlayerCharacterController::WeaponFire);
			PlayerEnhancedInputComponent->BindAction(WeaponFireAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopWeaponFire);
		}

		if (MovementAction)
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);

		if (LookAction)
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);

		if (InteractAction)
			PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacterController::Interact);

		if (OpenWeaponWidgetAction)
			PlayerEnhancedInputComponent->BindAction(OpenWeaponWidgetAction, ETriggerEvent::Started, this, &APlayerCharacterController::OpenCloseWeaponWidget);

		//if (ScrollAction)
			//PlayerEnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Scroll);

		/*
		if (ZeroKeyAction)
			PlayerEnhancedInputComponent->BindAction(ZeroKeyAction, ETriggerEvent::Started, this, &APlayerCharacterController::ZeroKey);

		if (OneKeyAction)
			PlayerEnhancedInputComponent->BindAction(OneKeyAction, ETriggerEvent::Started, this, &APlayerCharacterController::OneKey);

		if (TwoKeyAction)
			PlayerEnhancedInputComponent->BindAction(TwoKeyAction, ETriggerEvent::Started, this, &APlayerCharacterController::TwoKey);
		*/
	}
}

void APlayerCharacterController::Move(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0.F)
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), Value[1]);
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Value[0]);
	}
}

void APlayerCharacterController::Look(const FInputActionValue& Value)
{
	AddPitchInput(Value[1] * -1);
	AddYawInput(Value[0]);
}

void APlayerCharacterController::Scroll(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 6.F, FColor::Purple, L"Value is: " + FString::SanitizeFloat(Value[0]));
	
	if (Value[0] > 0.F)
	{
		AWeaponBase* LocalWeapon;
		
		switch (EWeaponType LocalType = PlayerRef->GetCurrentWeaponType(); PlayerRef->GetCurrentWeaponMap()[LocalType]->GetWeaponType())
		{
		case EWeaponType::EWT_Unarmed:

			if (PlayerRef->GetWeaponType(EWeaponType::EWT_Pistol, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);
			
			break;
			
		case EWeaponType::EWT_Pistol:

			if (PlayerRef->GetWeaponType(EWeaponType::EWT_SMG, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);

			else if (PlayerRef->GetWeaponType(EWeaponType::EWT_Rifle, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);
			
			break;
			
		case EWeaponType::EWT_SMG:

			if (PlayerRef->GetWeaponType(EWeaponType::EWT_Rifle, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);

			else if (PlayerRef->GetWeaponType(EWeaponType::EWT_Rifle, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);
			
			break;
			
		case EWeaponType::EWT_Rifle:

			if (PlayerRef->GetWeaponType(EWeaponType::EWT_Unarmed, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);
			
			break;
			
		default:
			break;
		}
	}

	else if (Value[0] < 0.F)
	{
		AWeaponBase* LocalWeapon;
		
		switch (EWeaponType LocalType = PlayerRef->GetCurrentWeaponType(); PlayerRef->GetCurrentWeaponMap()[LocalType]->GetWeaponType())
		{
		case EWeaponType::EWT_Unarmed:

			if (PlayerRef->GetWeaponType(EWeaponType::EWT_Rifle, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);

			else if (PlayerRef->GetWeaponType(EWeaponType::EWT_Rifle, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);
			
			break;
			
		case EWeaponType::EWT_Pistol:

			if (PlayerRef->GetWeaponType(EWeaponType::EWT_Unarmed, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);

			else if (PlayerRef->GetWeaponType(EWeaponType::EWT_Rifle, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);
			
			break;
			
		case EWeaponType::EWT_SMG:

			if (PlayerRef->GetWeaponType(EWeaponType::EWT_Pistol, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);

			else if (PlayerRef->GetWeaponType(EWeaponType::EWT_Rifle, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);
			
			break;
			
		case EWeaponType::EWT_Rifle:

			if (PlayerRef->GetWeaponType(EWeaponType::EWT_SMG, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);

			else if (PlayerRef->GetWeaponType(EWeaponType::EWT_Rifle, LocalWeapon, LocalType))
				PlayerRef->GetCurrentWeaponMap()[LocalType]->SetWeaponType(LocalType);
			
			break;
			
		default:
			break;
		}
	}
}

void APlayerCharacterController::Interact()
{
	if (IsValid(PlayerRef))
		PlayerRef->InteractWithObject();
}

void APlayerCharacterController::WeaponFire()
{
	if (bCanFire)
	{
		PlayerRef->WeaponFire();
		
		bCanFire = false;
	}
}

void APlayerCharacterController::StopWeaponFire()
{
	bCanFire = true;
}

void APlayerCharacterController::OpenCloseWeaponWidget()
{
	if (IsValid(WeaponWidget) && WeaponWidget->IsInViewport())
	{
		FInputModeGameOnly InputMode;

		SetInputMode(InputMode);

		bShowMouseCursor = false;

		bIsWeaponWidgetOpen = false;

		WeaponWidget->RemoveFromParent();
	}
	
	else if (!IsValid(WeaponWidget) || !WeaponWidget->IsInViewport())
	{
		if (WeaponWidget = CreateWidget<UWeaponSwitchWidget>(this, WeaponWidgetClass); IsValid(WeaponWidget))
		{
			WeaponWidget->AddToViewport();
			
			FInputModeUIOnly UIOnly;

			SetInputMode(UIOnly);

			bShowMouseCursor = true;

			bIsWeaponWidgetOpen = true;
		}
	}
}

/*
void APlayerCharacterController::ZeroKey()
{
	const EWeaponType LocalClass = PlayerRef->GetCurrentWeaponType();
	PlayerRef->SetWeaponName(PlayerRef->GetCurrentWeaponMap()[LocalClass]->GetWeaponName());

	PlayerRef->SetWeaponVisibility(LocalClass);

	PlayerRef->SetWeaponClass(EWeaponClass::EWC_Unarmed);
	PlayerRef->SetWeaponName(EWeaponName::EWN_Unarmed);
	PlayerRef->SetWeaponType(EWeaponType::EWT_Unarmed);
}

void APlayerCharacterController::OneKey()
{
	PlayerRef->SetWeaponClass(EWeaponClass::EWC_Primary);

	const EWeaponClass LocalClass = PlayerRef->GetWeaponClass();
	PlayerRef->SetWeaponName(PlayerRef->GetCurrentWeapon()[LocalClass]->GetWeaponName());

	PlayerRef->SetWeaponVisibility(LocalClass);
}

void APlayerCharacterController::TwoKey()
{
	PlayerRef->SetWeaponClass(EWeaponClass::EWC_Secondary);

	const EWeaponClass LocalClass = PlayerRef->GetWeaponClass();
	PlayerRef->SetWeaponName(PlayerRef->GetCurrentWeapon()[LocalClass]->GetWeaponName());

	PlayerRef->SetWeaponVisibility(LocalClass);
}
*/

void APlayerCharacterController::Jump() { GetCharacter()->Jump(); }

void APlayerCharacterController::StopJump() { GetCharacter()->StopJumping(); }


