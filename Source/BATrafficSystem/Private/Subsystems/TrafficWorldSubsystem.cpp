// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TrafficWorldSubsystem.h"
#include <Actors/ParkedVehicle.h>

void UTrafficWorldSubsystem::RegisterPath(ATrafficPath* NewPath)
{

}

void UTrafficWorldSubsystem::RegisterParkedCar(AParkedVehicle* NewParkedVehicle)
{
	ParkedVehicles.Add(NewParkedVehicle);
	
	if (!MainParkedVehicle)
	{
		MainParkedVehicle = NewParkedVehicle;
	}
	NewParkedVehicle->MainParkedVehicle = MainParkedVehicle;
}

ATrafficPath* UTrafficWorldSubsystem::GetTrafficPath()
{
	return nullptr;
}
