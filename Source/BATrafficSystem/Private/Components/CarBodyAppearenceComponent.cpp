// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CarBodyAppearenceComponent.h"

// Sets default values for this component's properties
UCarBodyAppearenceComponent::UCarBodyAppearenceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCarBodyAppearenceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCarBodyAppearenceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCarBodyAppearenceComponent::SetReverseLight(bool const bIsLit)
{
	
}

void UCarBodyAppearenceComponent::SetBrakeLight(bool const bIsLit)
{

}

void UCarBodyAppearenceComponent::SetAllDoorsOpen(bool const bDoorOpen)
{


}

void UCarBodyAppearenceComponent::SetDoorOpen(ETrafficCarDoor CarDoor, bool const bDoorOpen)
{

}

void UCarBodyAppearenceComponent::ToggleHeadlights()
{

}

void UCarBodyAppearenceComponent::ToggleHazardlights()
{

}
