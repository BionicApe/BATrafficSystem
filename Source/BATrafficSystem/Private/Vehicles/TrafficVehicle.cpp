// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/TrafficVehicle.h"

#include "Components/AudioComponent.h"
#include "Components/InputComponent.h"

#include "Components/CarBodyAppearenceComponent.h"
#include "Components/TrafficObstacleComponent.h"

#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include <BATrafficSystemTypes.h>


ATrafficVehicle::ATrafficVehicle(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/) : Super(ObjectInitializer)
{
	TrafficObstacleComponent = CreateDefaultSubobject<UTrafficObstacleComponent>(TEXT("TrafficObstacleComponent"));
	CarBodyAppearenceComponent = CreateDefaultSubobject<UCarBodyAppearenceComponent>(TEXT("CarBodyAppearenceComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	TrafficVehicleComponent = CreateDefaultSubobject<UTrafficVehicleComponent>(TEXT("TrafficVehicleComponent"));
}

void ATrafficVehicle::BeginPlay()
{
	Super::BeginPlay();
}

void ATrafficVehicle::Tick(float  DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSounds();
}

void ATrafficVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//TODO: Use Axis? the original package didn't use it...I don't see why we shouldn't

	InputComponent->BindAction<FInputBoolDelegate>("HandBreak", IE_Pressed, GetVehicleMovement(), &UChaosVehicleMovementComponent::SetHandbrakeInput, true);
	InputComponent->BindAction<FInputBoolDelegate>("HandBreak", IE_Released, GetVehicleMovement(), &UChaosVehicleMovementComponent::SetHandbrakeInput, false);

	InputComponent->BindAction<FInputBoolDelegate>("Reverse", IE_Pressed, this, &ATrafficVehicle::Reverse, true);
	InputComponent->BindAction<FInputBoolDelegate>("Reverse", IE_Released, this, &ATrafficVehicle::Reverse, false);

	InputComponent->BindAction<FInputFloatDelegate>("Throttle", IE_Pressed, GetVehicleMovement(), &UChaosVehicleMovementComponent::SetThrottleInput, 1.f);
	InputComponent->BindAction<FInputFloatDelegate>("Throttle", IE_Released, GetVehicleMovement(), &UChaosVehicleMovementComponent::SetThrottleInput, 0.f);

	InputComponent->BindAction<FInputFloatDelegate>("Right", IE_Pressed, GetVehicleMovement(), &UChaosVehicleMovementComponent::SetSteeringInput, 1.f);
	InputComponent->BindAction<FInputFloatDelegate>("Right", IE_Released, GetVehicleMovement(), &UChaosVehicleMovementComponent::SetSteeringInput, 0.f);

	InputComponent->BindAction<FInputFloatDelegate>("Left", IE_Pressed, GetVehicleMovement(), &UChaosVehicleMovementComponent::SetSteeringInput, -1.f);
	InputComponent->BindAction<FInputFloatDelegate>("Left", IE_Released, GetVehicleMovement(), &UChaosVehicleMovementComponent::SetSteeringInput, 0.f);

	InputComponent->BindAction<FInputBoolDelegate>("Brake", IE_Pressed, this, &ATrafficVehicle::Brake, true);
	InputComponent->BindAction<FInputBoolDelegate>("Brake", IE_Released, this, &ATrafficVehicle::Brake, false);

	InputComponent->BindAction<FInputBoolDelegate>("OpenDoor", IE_Pressed, CarBodyAppearenceComponent, &UCarBodyAppearenceComponent::SetAllDoorsOpen, true);
	InputComponent->BindAction<FInputBoolDelegate>("CloseDoor", IE_Pressed, CarBodyAppearenceComponent, &UCarBodyAppearenceComponent::SetAllDoorsOpen, false);

	InputComponent->BindAction("ToggleHeadlights", IE_Pressed, CarBodyAppearenceComponent, &UCarBodyAppearenceComponent::ToggleHeadlights);

	//InputComponent->BindAction("ToggleHeadlights", IE_Pressed, CarBodyAppearenceComponent, &UCarBodyAppearenceComponent::ToggleHazardlights);
}


void ATrafficVehicle::SetInputs_Implementation(float const Throttle, float const Brakes, float const Steering, bool const bUseHandbrake, bool const bIsReversing)
{
	GetVehicleMovement()->SetThrottleInput(Throttle);
	GetVehicleMovement()->SetBrakeInput(Brakes);
	GetVehicleMovement()->SetSteeringInput(Steering);
	GetVehicleMovement()->SetHandbrakeInput(bUseHandbrake);

	Reverse(bIsReversing);
}


void ATrafficVehicle::Reverse(bool const bIsReversing)
{
	if (bIsReversing && GetVehicleMovement()->GetUseAutoGears())
	{
		GetVehicleMovement()->SetUseAutomaticGears(false);
		GetVehicleMovement()->SetTargetGear(-1, true);
	}
	else if (!bIsReversing && !GetVehicleMovement()->GetUseAutoGears())
	{
		GetVehicleMovement()->SetTargetGear(1, true);
		GetVehicleMovement()->SetUseAutomaticGears(true);
	}
	CarBodyAppearenceComponent->SetReverseLight(bIsReversing);
}

void ATrafficVehicle::Brake(bool const bIsbraking)
{
	GetVehicleMovement()->SetBrakeInput(bIsbraking ? 1.f : 0.f);
	CarBodyAppearenceComponent->SetBrakeLight(bIsbraking);
}


void ATrafficVehicle::SetSounds()
{
	//////////////////////////////////////////////////////////////////////////
	//TODO:Delete this when when have an event from possess, not the RPM sound though
	//////////////////////////////////////////////////////////////////////////
	bool const bIsParked = TrafficVehicleComponent->ControlMode == ETrafficControlMode::PARKED_MODE;
	if (!bIsParked)
	{
		if (UChaosWheeledVehicleMovementComponent* WheeledVehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement()))
		{
			AudioComponent->SetFloatParameter("RPM", WheeledVehicleMovement->GetEngineRotationSpeed());
		}
	}
	AudioComponent->SetFloatParameter("Volume", bIsParked ? 0.f : 1.f);
}
