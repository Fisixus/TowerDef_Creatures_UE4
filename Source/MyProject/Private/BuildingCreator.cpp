// Copyright Utku Erden 2021

#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"	
#include "BuildingCreator.h"

#define OUT

// Sets default values for this component's properties
UBuildingCreator::UBuildingCreator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildingCreator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuildingCreator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector playerViewPointLoc;
	FRotator playerViewPointRot;
	// ...
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(OUT playerViewPointLoc,
	 OUT playerViewPointRot
	);
	//UE_LOG(LogTemp, Warning, TEXT("Location:%s, Rotation:%s"), *playerViewPointLoc.ToString(), *playerViewPointRot.ToString());
	FVector lineTraceEnd = playerViewPointLoc + GetOwner()->GetActorForwardVector() * 10000.f;
	DrawDebugLine
	(
		GetWorld(),
		playerViewPointLoc,
		lineTraceEnd,
		FColor(255,0,0),
		false,
		0.f,
		0.f,
		5.f
	);
}

