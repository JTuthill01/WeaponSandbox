#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class WEAPONSANDBOX_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void InteractableFound();

	UFUNCTION(BlueprintNativeEvent)
	void InteractWithObject(class APlayerCharacter* PlayerRef);
};
