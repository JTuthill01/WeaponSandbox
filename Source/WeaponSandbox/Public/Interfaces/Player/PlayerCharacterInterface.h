#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPlayerCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class WEAPONSANDBOX_API IPlayerCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	class APlayerCharacter* GetPlayerRef();
};
