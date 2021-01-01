// Copyright Utku Erden 2021

#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"	
#include "Components/PrimitiveComponent.h"
#include "BuildingCreator.h"


#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))
#define OUT



APlayerController* inputController;
FVector mousePos;
FVector mouseRot;

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
	inputController = GetWorld()->GetFirstPlayerController();
	inputController->bEnableClickEvents = true;
	inputController->bShowMouseCursor = true;

	//TODO: Change it to pawn => inputController->BindAction("MouseLeftClicked", IE_Pressed, this, &BuildingCreator::MyFunction);
	// ...
}

MarkerType UBuildingCreator::GetWhichBuildingIsSelected()
{
	return markerType;
}

void UBuildingCreator::SetCubeBuilding()
{
	markerType = Cube;
}


void UBuildingCreator::SetSphereBuilding()
{
	markerType = Sphere;
}


void UBuildingCreator::SetCapsuleBuilding()
{
	markerType = Capsule;
}

void UBuildingCreator::TraceGround()
{
	FVector playerViewPointLoc;
	FRotator playerViewPointRot;

	inputController->GetPlayerViewPoint
	(OUT playerViewPointLoc,
		OUT playerViewPointRot
	);

	inputController->DeprojectMousePositionToWorld(OUT mousePos, OUT mouseRot);
	mousePos = mousePos + mouseRot * 10000.f;
	//UE_LOG(LogTemp, Error, TEXT("Pos:%s"), *(mousePos.ToString()));
	DrawDebugLine
	(
		GetWorld(),
		playerViewPointLoc,
		mousePos,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		5.f
	);
	FCollisionQueryParams TraceParams(FName(""), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		playerViewPointLoc,
		mousePos,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* actorHit = hit.GetActor();
	if (actorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("HitName:%s"), *(actorHit->GetName()));
	}
}

// Called every frame
void UBuildingCreator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (inputController->IsInputKeyDown(EKeys::RightMouseButton)) {
		markerType = None;
		UE_LOG(LogTemp, Error, TEXT("Nothing is selected!"));
	}
	
	if(markerType != None)
		TraceGround();
}

