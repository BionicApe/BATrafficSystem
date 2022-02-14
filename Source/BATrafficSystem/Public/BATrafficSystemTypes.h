// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BATrafficSystemTypes.generated.h"

UENUM(BlueprintType)
enum class ETrafficControlMode : uint8 
{
	AI_MODE,
	PARKED_MODE,
	DRIVE_MODE
};

UENUM(BlueprintType)
enum class ETrafficAIMode : uint8
{
	ROAM,
	DRIVE_TO_A_POINT,
	NAVIGATE_TO_A_POINT,
	PREDEFINED_PATH
};

UENUM(BlueprintType)
enum class ETrafficCarDoor : uint8
{
	FRONT_LEFT,
	FRONT_RIGHT,
	REAR_LEFT,
	REAR_RIGHT,
};

UENUM(BlueprintType)
enum class ETrafficHitDirection : uint8
{
	FRONT,
	FRONT_LEFT,
	FRONT_RIGHT,
	LEFT,
	RIGHT,
	REAR_LEFT,
	REAR_RIGHT,
	REAR
};

/**
 * Enum_Current_traffic_light
 */
UENUM(BlueprintType)
enum class ETrafficLightStatus : uint8
{
	RED,
	RED_WITH_YELLOW,
	YELLOW,
	GREEN
};

/**
 * Enum_Give_a_way
 */
UENUM(BlueprintType)
enum class EGiveAWay : uint8
{
	UNDEFINED,
	GIVE_A_WAY,
	DRIVE
};

/**
 * Enum_OnAccident
 */
UENUM(BlueprintType)
enum class EAccidentReactionType : uint8
{
	KEEP_DRIVING,
	STOP,
	STOP_HAZARD_LIGHTS,
	PARK_ON_A_ROAD_SIDE,
	PARK_ON_A_ROAD_SIDE_HAZARD_LIGHTS,
	RUN_AWAY
};


/**
 * Enum_Reach_target_type
 */
UENUM(BlueprintType)
enum class EReachTargetType : uint8
{
	PARK_AT_POINT,
	PARK_ON_A_ROAD_SIDE,
	STOP_ON_ROAD,
	KEEP_DRIVING,
	FOLLOW_TARGET
};


/**
 *Enum_road_type
 */
UENUM(BlueprintType)
enum class ERoadtype : uint8
{
	CITY,
	FARMLANDS,
	HIGHWAY
};

/**
 *Enum_Traffic_arrow_type
 */
UENUM(BlueprintType)
enum class ETrafficArrowType : uint8
{
	NO_ARROW,
	STRAIGHT,
	RIGHT,
	LEFT,
	STRAIGHT_RIGHT,
	STRAIGHT_LEFT,
	PEDS
};


/**
 *Enum_Traffic_center
 */
UENUM(BlueprintType)
enum class ETrafficCenter : uint8
{
	Camera,
	Player,
	Custom
};

/**
 * Enum_Traffic_light_type
 */
UENUM(BlueprintType)
enum class ETrafficLightType : uint8
{
	TRAFFIC_LIGHTS,
	PRIORITY_ROAD
};

/**
 *Enum_TurnType
 */
UENUM(BlueprintType)
enum class ETurnType : uint8
{
	STRAIGHT,
	RIGHT,
	LEFT
};


/**
 * Next_Road_Struct
 */
USTRUCT(BlueprintType)
struct BATRAFFICSYSTEM_API FNextRoad
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Traffic")
	ETurnType TurnType = ETurnType::STRAIGHT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
	float Probability = 1.f;
};




/**
 * Single_car_spawn_probability_entry_struct
 */
USTRUCT(BlueprintType)
struct BATRAFFICSYSTEM_API FSingleVehicleSpawnProbability
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
	TMap<AActor*, float> VehiclesMap;
};


///**
// *Spline_point_struct
// */
//USTRUCT(BlueprintType)
//struct BATRAFFICSYSTEM_API FSplinePoint
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
//	FTransform Transform;
//	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
//	FVector ArriveTangent;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic")
//	FVector LeaveTangent;
//
//};
