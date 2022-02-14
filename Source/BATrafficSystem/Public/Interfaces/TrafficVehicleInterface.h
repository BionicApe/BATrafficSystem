// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TrafficVehicleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTrafficVehicleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BATRAFFICSYSTEM_API ITrafficVehicleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Input")
	void SetInputs(float const Throttle, float const Brakes, float const Steering, bool const bUseHandbrake, bool const bIsReversing);
};
