// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "UObject/UObjectGlobals.h"
#include "Interfaces/TrafficVehicleInterface.h"
#include "TrafficVehicle.generated.h"

class UTrafficObstacleComponent;
class UAudioComponent;
class UCarBodyAppearenceComponent;
class UTrafficVehicleComponent;


/**
 * 
 */
UCLASS()
class BATRAFFICSYSTEM_API ATrafficVehicle : public AWheeledVehiclePawn, public ITrafficVehicleInterface
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE_OneParam(FInputBoolDelegate, bool);
	DECLARE_DELEGATE_OneParam(FInputFloatDelegate, float);

public:

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTrafficObstacleComponent* TrafficObstacleComponent;
	
	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCarBodyAppearenceComponent* CarBodyAppearenceComponent;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTrafficVehicleComponent* TrafficVehicleComponent;
	
	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioComponent;

public:
	
	/** Default UObject constructor. */
	ATrafficVehicle(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:	
	
	virtual void SetInputs_Implementation(float const Throttle, float const Brakes, float const Steering, bool const bUseHandbrake, bool const bIsReversing) override;

	virtual void Reverse(bool const bIsReversing);

	virtual void Brake(bool const bIsbraking);

	virtual void SetSounds();
};
