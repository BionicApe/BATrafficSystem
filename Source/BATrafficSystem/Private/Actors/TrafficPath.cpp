// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TrafficPath.h"
#include "Components/SplineComponent.h"

ATrafficPath::ATrafficPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimarySplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PrimarySplineComponent"));
	SecondarySplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SecondarySplineComponent"));
}

// Called when the game starts or when spawned
void ATrafficPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrafficPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATrafficPath::FindClosestSplineDistance(const FVector& OriginLocation) const
{
	return 0.f;
}

