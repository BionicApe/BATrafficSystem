// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficPath.generated.h"

class USceneComponent;
class USplineComponent;

UCLASS()
class BATRAFFICSYSTEM_API ATrafficPath : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRootComponent;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* PrimarySplineComponent;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* SecondarySplineComponent;

	UPROPERTY(Category = "Traffic|Path", EditAnywhere, BlueprintReadWrite)
	TArray<AParkedVehicle*> ParkingSpots;

public:	
	// Sets default values for this actor's properties
	ATrafficPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//EXTRACTED FROM BP
	UFUNCTION(BlueprintCallable)
	virtual float FindClosestSplineDistance(const FVector& OriginLocation) const;

};
