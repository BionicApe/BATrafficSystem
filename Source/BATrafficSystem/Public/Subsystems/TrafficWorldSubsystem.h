// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TrafficWorldSubsystem.generated.h"

class AParkedVehicle;

/**
 *
 */
UCLASS()
class BATRAFFICSYSTEM_API UTrafficWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(Transient)
	TArray<ATrafficPath*> TrafficPaths;
	
	UPROPERTY(Transient)
	TArray<AParkedVehicle*> ParkedVehicles;

	UPROPERTY(Transient)
	AParkedVehicle* MainParkedVehicle;

public:

	UFUNCTION(BlueprintCallable, Category = "TrafficSystem")
	void RegisterPath(ATrafficPath* NewPath);

	UFUNCTION(BlueprintCallable, Category = "TrafficSystem")
	void RegisterParkedCar(AParkedVehicle* NewParkedVehicle);

	ATrafficPath* GetTrafficPath();
};
