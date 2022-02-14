// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ParkedVehicle.h"
#include "Subsystems/TrafficWorldSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetMathLibrary.h"
#include <UObject/Object.h>
#include <EngineUtils.h>
#include <Actors/TrafficPath.h>
#include <Components/SplineComponent.h>
#include <Math/Vector.h>


AParkedVehicle::AParkedVehicle() : Super()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
}

void AParkedVehicle::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("AParkedVehicle::BeginPlay World is Null"));
		return;
	}

	UTrafficWorldSubsystem* TrafficWorldSubsystem = GetWorld()->GetSubsystem<UTrafficWorldSubsystem>();
	if (!TrafficWorldSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("AParkedVehicle::BeginPlay TrafficWorldSubsystem is Null"));
		return;
	}

	//Sequence 0 //Set Main Parked Car
	TrafficWorldSubsystem->RegisterParkedCar(this);
	//END: Sequence 0	
	//Sequence 1 //Get Random Traffic Path to get Spawn Cars Map TODO: (this should be replaced)
	CurrentPath = TrafficWorldSubsystem->GetTrafficPath();
	//END: Sequence 1
	//Sequence 2
	if (bCanParkHere)
	{
		ClosestPath->ParkingSpots.AddUnique(this);
	}
	//END: Sequence 2
	//Sequence 3//Chance to spawn a car. If false, car will not be spawned in this location.
	bool const bShouldSpawn = UKismetMathLibrary::RandomBoolWithWeight(SpawnChance);
	if (bShouldSpawn)
	{
		//Run Parked Car Timer for the first time, and then start the timer
		ParkedCarTimer();

		//FTimerDynamicDelegate Delegate;
		//Delegate.BindWeakLambda(this, [this]()
		//	{
		//		MyCustomMethod(MyParam);
		//	});

		//UKismetSystemLibrary::K2_SetTimerDelegate(Delegate,)
	}
	//END: Sequence 3



}

void AParkedVehicle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is null"));
		return;
	}
	FVector const MyLocation = GetActorLocation();//Used multiple times, we put it here

	//Sequence0
	if (bIsAlignedToSurface)
	{
		FVector const StartTrace = MyLocation + FVector(0.f, 0.f, 200.f);
		FVector const EndTrace = MyLocation + FVector(0.f, 0.f, -200.f);

		FHitResult Hit;
		FCollisionObjectQueryParams ObjectQueryParams;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		bool const bHit = World->LineTraceSingleByObjectType(Hit, StartTrace, EndTrace, ObjectQueryParams, Params);

		if (bHit)
		{
			FVector const RightVector = StaticMeshComp->GetRightVector();
			FVector const CrossProduct1 = FVector::CrossProduct(RightVector, Hit.ImpactNormal);
			FVector const CrossProduct2 = FVector::CrossProduct(Hit.ImpactNormal, CrossProduct1);

			FRotator const RotationFromAxes = UKismetMathLibrary::MakeRotationFromAxes(CrossProduct1, CrossProduct2, Hit.ImpactNormal);

			StaticMeshComp->SetWorldLocationAndRotation(Hit.Location, RotationFromAxes);
		}
	}
	//END: Sequence 0
	//Sequence 1

	UMaterialInstanceDynamic* MID = StaticMeshComp->CreateDynamicMaterialInstance(0, MasterMaterial);

	FLinearColor Color1 = bCanStartDriving ? FLinearColor::Blue : bCanParkHere ? FLinearColor::Green : FLinearColor::Red;
	FLinearColor Color2 = bCanParkHere ? Color1 : FLinearColor::Red;

	MID->SetVectorParameterValue("Color", Color1);
	MID->SetVectorParameterValue("Secondary Color", Color2);
	MID->SetScalarParameterValue("Opacity", SpawnChance);
	//END Sequence 1

	//Sequence 2
	DistanceToClosestPath = 10000000.f;//Big Number to compare
	//TODO: DON'T DO GET ALL ACTORS OF CLASS!!

	for (TActorIterator<AActor> It(World, ATrafficPath::StaticClass()); It; ++It)
	{
		AActor* Actor = *It;
		if (ATrafficPath* TrafficPath = Cast<ATrafficPath>(Actor))
		{
			float const  DistanceSpline = TrafficPath->FindClosestSplineDistance(MyLocation);
			FVector const  DistanceAlongSpline = TrafficPath->SecondarySplineComponent->GetLocationAtDistanceAlongSpline(DistanceSpline, ESplineCoordinateSpace::World);

			float const Distance = FVector::Distance(DistanceAlongSpline, MyLocation);
			if (Distance < DistanceToClosestPath)
			{
				DistanceToClosestPath = Distance;
				ClosestPath = TrafficPath;
			}
		}
	}
	//END: Sequence 2
}


FVector AParkedVehicle::GetTrafficSpawnCenterLocation() const
{
	if (APlayerCameraManager* PCM = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		return PCM->GetCameraLocation();
	}
	return FVector::ZeroVector;
}

void AParkedVehicle::AddParkedVehicle(int32 Amount)
{
	//This is rubbish
	if (MainParkedVehicle)
	{
		MainParkedVehicle->NumberOfParkedVehicles += Amount;
	}
}

bool AParkedVehicle::VisibilityCheckParkedVehicle(int32 Iterations)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is null"));
		return true;
	}

	static TArray<FVector> TraceArray = {
		FVector(0.f, 0.f, 0.5f),
		FVector(1.f, 0.f, 0.25f),
		FVector(-1.f, 0.f, 0.25f),
		FVector(0.f, -0.5f, 0.25f),
		FVector(0.f, 0.5f, 0.25f),
	};

	for (int32 i = 0; i < Iterations; i++)
	{
		FVector VectorToUse;
		if (i < TraceArray.Num())
		{
			VectorToUse = TraceArray[i];
		}
		else
		{
			VectorToUse = FVector(
				UKismetMathLibrary::RandomFloatInRange(-1.f, 1.f),
				UKismetMathLibrary::RandomFloatInRange(-0.5f, 0.5f),
				UKismetMathLibrary::RandomFloatInRange(0.f, 0.5f)
			);
		}

		FVector const SphereBounds = VectorToUse * StaticMeshComp->Bounds.SphereRadius;
		FVector const StartTrace = StaticMeshComp->Bounds.Origin + SphereBounds;

		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		bool const bHit = World->LineTraceSingleByChannel(Hit, StartTrace, SpawnCenterLoc, ECollisionChannel::ECC_Visibility, Params);
		if (bHit)
		{
			return false;
		}
	}
	return true;
}

void AParkedVehicle::ParkedCarTimer_Implementation()
{

}