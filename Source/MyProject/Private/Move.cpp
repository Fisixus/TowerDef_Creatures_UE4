// Copyright Utku Erden 2021


#include "Move.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UMove::UMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMove::BeginPlay()
{
	Super::BeginPlay();

	FVector pos = GetOwner()->GetActorLocation();

	GetOwner()->SetActorLocation(pos + FVector(280.f,0.f, 0.f));
	// ...
	
}

// Called every frame
void UMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

