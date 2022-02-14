// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BATrafficSystemTypes.h"
#include "Engine/EngineTypes.h"
#include "ParkedVehicle.generated.h"


class UStaticMeshComponent;
class AParkedVehicle;
class AActor;
class ATrafficPath;
class UMaterialInterface;

/**
 *
 */
UCLASS()
class BATRAFFICSYSTEM_API AParkedVehicle : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;
	//Config
	UPROPERTY(Category = "Traffic|Settings", EditAnywhere, BlueprintReadWrite)
	int32 MaxParkedVehicles = 30;

	UPROPERTY(Category = "Traffic|Settings", EditAnywhere, BlueprintReadWrite)
	ETrafficCenter TrafficCenter = ETrafficCenter::Camera;

	UPROPERTY(Category = "Traffic|Settings", EditAnywhere, BlueprintReadWrite)
	float MinSpawnDistance = 4000.f;

	UPROPERTY(Category = "Traffic|Settings", EditAnywhere, BlueprintReadWrite)
	float MaxSpawnDistance = 12000.f;

	UPROPERTY(Category = "Traffic|Settings", EditAnywhere, BlueprintReadWrite)
	bool bSpawnOnlyOffScreen = true;
	//END: Config

	//Basic
	UPROPERTY(Category = "Traffic|Basic", EditAnywhere, BlueprintReadWrite)
	ERoadtype RoadType = ERoadtype::CITY;

	UPROPERTY(Category = "Traffic|Basic", EditAnywhere, BlueprintReadWrite)
	float SpawnChance;

	UPROPERTY(Category = "Traffic|Basic", EditAnywhere, BlueprintReadWrite)
	bool bIsAlignedToSurface = true;

	UPROPERTY(Category = "Traffic|Basic", EditAnywhere, BlueprintReadWrite)
	bool bCanStartDriving = true;

	UPROPERTY(Category = "Traffic|Basic", EditAnywhere, BlueprintReadWrite)
	bool bCanParkHere = true;
	//END: Basic

	//Advanced
	//UPROPERTY(Category = "Traffic|Advanced", EditAnywhere, BlueprintReadWrite)
	//TArray<TEnumAsByte<EObjectTypeQuery>> StickToObjectTypes = { ECC_WorldStatic };

	UPROPERTY(Category = "Traffic|Advanced", EditAnywhere, BlueprintReadWrite)
	float MaxDelayForStartDriving = 180.f;

	UPROPERTY(Category = "Traffic|Advanced", EditAnywhere, BlueprintReadWrite)
	float SpawnOffsetZ = 15.f;
	//END: Advanced

	//System
	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	int32 VehicleSpawnVisibilityIterat = 4;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	FVector SpawnCenterLoc = FVector::ZeroVector;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	AParkedVehicle* MainParkedVehicle;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	AActor* VehicleAssigned;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> VehicleClassToSPawn;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	int32 NumberOfParkedVehicles = 0;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	float DistanceToPlayer = 0.f;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	bool bRunInitialSetup = true;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	float DistanceToClosestPath = 0.f;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	ATrafficPath* ClosestPath;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	ATrafficPath* CurrentPath;

	UPROPERTY(Category = "Traffic|System", EditAnywhere, BlueprintReadWrite)
	FTimerHandle SpawnTimerHandle;
	//END: System

	//Extracted from BP Code (not variables)
	UPROPERTY(Category = "Traffic|Extracted", EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* MasterMaterial;
	//END: Extracted from BP Code (not variables)

	//Events
	UPROPERTY(Category="Traffic|Events", BlueprintNativeEvent)
	void ParkedCarTimer();
	virtual void ParkedCarTimer_Implementation();


public:

	AParkedVehicle();

protected:

	virtual void BeginPlay()override;

public:

	virtual void OnConstruction(const FTransform& Transform) override;

	//FROM BP
	UFUNCTION(BlueprintCallable, Category = "Traffic")
	virtual FVector GetTrafficSpawnCenterLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Traffic")
	virtual void AddParkedVehicle(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Traffic")
	bool VisibilityCheckParkedVehicle(int32 Iterations);

};
