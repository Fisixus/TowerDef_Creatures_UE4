// Copyright Utku Erden 2021

#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"	
#include "Components/PrimitiveComponent.h"
#include "BuildingCreator.h"



#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(text), fstring))
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
	
	inputController = GetWorld()->GetFirstPlayerController();
	inputController->bEnableClickEvents = true;
	inputController->bShowMouseCursor = true;
	markerActor = Cast<AActor>(markerObj);
	if (markerActor != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Name:%s"), *(markerActor->GetName()));
		markerMesh = markerActor->FindComponentByClass<UStaticMeshComponent>();
		markerMat = UMaterialInstanceDynamic::Create(markerMesh->GetMaterial(0), NULL);
		HideMarker();
		ChangeMarkerColor(FLinearColor(1.f, 0.f, 0.f, 0.75f));
	}
	//TODO: !!! Why UInputComponent in here is not worked, unless BP_Default_Pawn is working
}

void UBuildingCreator::CancelBuildingCallback()
{
	markerType = None;
	UE_LOG(LogTemp, Error, TEXT("Nothing is selected!"));
	HideMarker();
}

void UBuildingCreator::ChangeMarkerColor(FLinearColor newColor)
{
	markerMat->SetVectorParameterValue(FName(TEXT("MainColor")), newColor);
	//markerMat->SetScalarParameterValue(FName(TEXT("MainColor")),1.f);
	markerMesh->SetMaterial(0, markerMat);
}

void UBuildingCreator::ShowMarker()
{
	//markerMesh->SetVisibility(true, true);
	markerActor->SetActorHiddenInGame(false);
}

void UBuildingCreator::HideMarker()
{
	//markerMesh->SetVisibility(false, true);
	markerActor->SetActorHiddenInGame(true);
}

MarkerType UBuildingCreator::GetWhichBuildingIsSelected()
{
	return markerType;
}

void UBuildingCreator::SetAsCubeBuilding()
{
	//UE_LOG(LogTemp, Error, TEXT("SA!!"));
	markerType = Cube;
	ShowMarker();
}


void UBuildingCreator::SetAsCylinderBuilding()
{
	markerType = Cylinder;
	ShowMarker();
}


void UBuildingCreator::SetAsConeBuilding()
{
	markerType = Cone;
	ShowMarker();
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
	/*
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
	*/
	FCollisionQueryParams TraceParams(FName(""), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		playerViewPointLoc,
		mousePos,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1),
		TraceParams
	);

	AActor* actorHit = hit.GetActor();
	if (actorHit)
	{
		if(actorHit->GetName().Contains("AllowedArea", ESearchCase::IgnoreCase, ESearchDir::FromStart))
		{
			//UE_LOG(LogTemp, Warning, TEXT("HitName:%s"), *(actorHit->GetName()));
			ChangeMarkerColor(FLinearColor(0.f, 1.f, 0.f, 0.75f));
		}
		else 
		{
			ChangeMarkerColor(FLinearColor(1.f, 0.f, 0.f, 0.75f));
		}
		FVector markerPos = hit.Location;
		markerActor->SetActorLocation(FVector(markerPos.X, markerPos.Y, 0.2f));
		
	}
}

// Called every frame
void UBuildingCreator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*
	if (inputController->IsInputKeyDown(EKeys::SpaceBar)) 
	{
		markerType = None;
		UE_LOG(LogTemp, Error, TEXT("Nothing is selected!"));
		HideMarker();
	}
	*/
	if(markerType != None)
	{
		TraceGround();
	}
}

