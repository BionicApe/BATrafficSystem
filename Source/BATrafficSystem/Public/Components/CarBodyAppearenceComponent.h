// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CarBodyAppearenceComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATRAFFICSYSTEM_API UCarBodyAppearenceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCarBodyAppearenceComponent();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Traffic")
	void SetReverseLight(bool const bIsLit);

	UFUNCTION(BlueprintCallable, Category = "Traffic")
	void SetBrakeLight(bool const bIsLit);

	UFUNCTION(BlueprintCallable, Category = "Traffic")
	void SetAllDoorsOpen(bool const bDoorOpen);

	UFUNCTION(BlueprintCallable, Category = "Traffic")
	void SetDoorOpen(ETrafficCarDoor CarDoor, bool const bDoorOpen);

	UFUNCTION(BlueprintCallable, Category = "Traffic")
	void ToggleHeadlights();

	UFUNCTION(BlueprintCallable, Category = "Traffic")
	void ToggleHazardlights();

 };
