// Copyright Utku Erden 2021

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "BuildingCreator.h"
#include "InputManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UInputManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void InvokeCancelBuilding();
	UFUNCTION(BlueprintCallable)
	void InvokeConstructBuilding();
	UFUNCTION(BlueprintCallable)
	void InvokeRotateCam();
private:
	AActor* buildingCreatorActor;
		
};
