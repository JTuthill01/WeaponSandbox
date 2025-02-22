#include "Pickups/Base/PickupBase.h"

#include "Components/SphereComponent.h"

// Sets default values
APickupBase::APickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetCastShadow(false);

	SetRootComponent(BaseMesh);

	PickupRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Radius"));
	PickupRadius->SetupAttachment(BaseMesh);
	PickupRadius->SetSphereRadius(100.F);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupBase::InteractableFound_Implementation() {}

void APickupBase::InteractWithObject_Implementation(APlayerCharacter* PlayerRef) {}
