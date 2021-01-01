// Copyright Utku Erden 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingCreator.generated.h"

UENUM()
enum MarkerType
{
	Cube	UMETA(DisplayName = "Cube"),
	Sphere  UMETA(DisplayName = "Sphere"),
	Capsule UMETA(DisplayName = "Capsule"),
	None	UMETA(DisplayName = "None")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UBuildingCreator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingCreator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	MarkerType GetWhichBuildingIsSelected();
	UFUNCTION(BlueprintCallable)
	void SetCubeBuilding();
	UFUNCTION(BlueprintCallable)
	void SetSphereBuilding();
	UFUNCTION(BlueprintCallable)
	void SetCapsuleBuilding();
	UFUNCTION(BlueprintCallable)
	void TraceGround();


private:
	UPROPERTY(EditAnywhere, Category=MarkerType)
	TEnumAsByte<MarkerType> markerType;
};
