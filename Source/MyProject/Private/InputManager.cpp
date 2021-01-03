// Copyright Utku Erden 2021

#include "GameFramework/Actor.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "InputManager.h"

UInputComponent* inputComponent;

// Sets default values for this component's properties
UInputManager::UInputManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInputManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("BuildingCreator"), FoundActors);
	if (FoundActors.Num() != 0)
	{
		buildingCreatorActor = FoundActors[0];
	}

	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent)
	{
		//UE_LOG(LogTemp, Error, TEXT("SA!"));
		inputComponent->BindAction
		(
			"CancelBuilding", // The input binding (specified in DefaultInput.ini)
			IE_Pressed, // React when button pressed (or on release, etc., if desired)
			this, // The object instance that is going to react to the input
			&UInputManager::InvokeCancelBuilding // The function that will fire when input is received
		);

		inputComponent->BindAction
		(
			"ConstructBuilding", // The input binding (specified in DefaultInput.ini)
			IE_Pressed, // React when button pressed (or on release, etc., if desired)
			this, // The object instance that is going to react to the input
			&UInputManager::InvokeConstructBuilding // The function that will fire when input is received
		);
	}
	// ...
	
}

void UInputManager::InvokeCancelBuilding()
{
	//UBuildingCreator* actorClass = Cast<UBuildingCreator>(GetWorld()->SpawnActor(UBuildingCreator::StaticClass()));


	//TODO: Why this is not working !!!!!! 
	//AActor* FoundActors2;
	//FoundActors2 = UGameplayStatics::GetActorOfClass(GetWorld(), UBuildingCreator::StaticClass());
	if (buildingCreatorActor)
	{
		buildingCreatorActor->FindComponentByClass<UBuildingCreator>()->CancelBuildingCallback();
	}

}

void UInputManager::InvokeConstructBuilding()
{
	if (buildingCreatorActor)
	{
		buildingCreatorActor->FindComponentByClass<UBuildingCreator>()->ConstructBuildingCallback();
	}
}


// Called every frame
void UInputManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

