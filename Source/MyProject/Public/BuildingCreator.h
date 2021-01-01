// Copyright Utku Erden 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingCreator.generated.h"


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
	bool GetIsCubeBuildingSelected();
	UFUNCTION(BlueprintCallable)
	void SetIsCubeBuildingSelected(bool situation);
	UFUNCTION(BlueprintCallable)
	bool GetIsSphereBuildingSelected();
	UFUNCTION(BlueprintCallable)
	void SetIsSphereBuildingSelected(bool situation);
	UFUNCTION(BlueprintCallable)
	bool GetIsCapsuleBuildingSelected();
	UFUNCTION(BlueprintCallable)
	void SetIsCapsuleBuildingSelected(bool situation);


private:
	UPROPERTY(EditAnywhere)
	bool isCubeBuildingSelected = false;
	UPROPERTY(EditAnywhere)
	bool isSphereBuildingSelected = false;
	UPROPERTY(EditAnywhere)
	bool isCapsuleBuildingSelected = false;
	
};
