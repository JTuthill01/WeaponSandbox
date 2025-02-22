#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interact/InteractInterface.h"
#include "PickupBase.generated.h"

UCLASS()
class WEAPONSANDBOX_API APickupBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractableFound_Implementation() override;
	
	virtual void InteractWithObject_Implementation(APlayerCharacter* PlayerRef) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USphereComponent> PickupRadius;
};
