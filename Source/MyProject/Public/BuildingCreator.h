// Copyright Utku Erden 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BuildingCreator.generated.h"

UENUM()
enum MarkerType
{
	Cube	UMETA(DisplayName = "Cube"),
	Cylinder  UMETA(DisplayName = "Cylinder"),
	Cone UMETA(DisplayName = "Cone"),
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
	void SetAsCubeBuilding();
	UFUNCTION(BlueprintCallable)
	void SetAsCylinderBuilding();
	UFUNCTION(BlueprintCallable)
	void SetAsConeBuilding();
	UFUNCTION(BlueprintCallable)
	void TraceGround();
	UFUNCTION(BlueprintCallable)
	void ShowMarker();
	UFUNCTION(BlueprintCallable)
	void HideMarker();
	UFUNCTION(BlueprintCallable)
	void ChangeMarkerColor(FLinearColor newColor);
	UFUNCTION(BlueprintCallable)
	void CancelBuildingCallback();


private:
	UPROPERTY(EditAnywhere, Category=MarkerType)
	TEnumAsByte<MarkerType> markerType;
	UPROPERTY(EditAnywhere, Category = "SceneObjects")
	UObject* markerObj;
	APlayerController* inputController;
	AActor* markerActor;
	FVector mousePos;
	FVector mouseRot;
	UStaticMeshComponent* markerMesh;
	UMaterialInstanceDynamic* markerMat;
	UInputComponent* inputComponent = nullptr;
};
