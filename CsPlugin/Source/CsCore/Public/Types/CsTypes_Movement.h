// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Interpolation.h"
#include "Managers/Time/CsTypes_Update.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Movement.generated.h"

// Mover
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsMover : uint8
{
	Actor			UMETA(DisplayName = "Actor"),
	Component		UMETA(DisplayName = "Component"),
	ECsMover_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsMover : public TCsEnumMap<ECsMover>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsMover, ECsMover)
};

namespace NCsMover
{
	typedef ECsMover Type;

	namespace Ref
	{
		extern CSCORE_API const Type Actor;
		extern CSCORE_API const Type Component;
		extern CSCORE_API const Type ECsMover_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsMovement
{
	enum class EMover : uint8
	{
		Actor,
		Component,
		EMover_MAX
	};

	struct CSCORE_API EMMover : public TCsEnumMap<EMover>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMMover, EMover)
	};

	namespace NMover
	{
		namespace Ref
		{
			typedef EMover Type;

			extern CSCORE_API const Type Actor;
			extern CSCORE_API const Type Component;
			extern CSCORE_API const Type EMover_MAX;
		}
	}
}

#pragma endregion Mover

// MoveDestination
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsMoveDestination : uint8
{
	Location				UMETA(DisplayName = "Location"),
	Actor					UMETA(DisplayName = "Actor"),
	Component				UMETA(DisplayName = "Component"),
	Bone					UMETA(DisplayName = "Bone"),
	ECsMoveDestination_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsMoveDestination : public TCsEnumMap<ECsMoveDestination>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsMoveDestination, ECsMoveDestination)
};

namespace NCsMoveDestination
{
	typedef ECsMoveDestination Type;

	namespace Ref
	{
		extern CSCORE_API const Type Location;
		extern CSCORE_API const Type Actor;
		extern CSCORE_API const Type Component;
		extern CSCORE_API const Type Bone;
		extern CSCORE_API const Type ECsMoveDestination_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsMovement
{
	enum class EDestination : uint8
	{
		Location,
		Actor,
		Component,
		Bone,
		EDestination_MAX
	};

	struct CSCORE_API EMDestination : public TCsEnumMap<EDestination>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDestination, EDestination)
	};

	namespace NDestination
	{
		namespace Ref
		{
			typedef EDestination Type;

			extern CSCORE_API const Type Location;
			extern CSCORE_API const Type Actor;
			extern CSCORE_API const Type Component;
			extern CSCORE_API const Type Bone;
			extern CSCORE_API const Type EDestination_MAX;
		}
	}
}

#pragma endregion MoveDestination

// FCsMoveByInterp_Params
#pragma region

class AActor;
class USceneComponent;
class USkeletalMeshComponent;
class UObject;

// NCsMovement::NTo::NInterp::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsMovement, NTo, NInterp, NParams, FParams)

USTRUCT(BlueprintType)
struct CSCORE_API FCsMoveByInterp_Params
{
	GENERATED_USTRUCT_BODY()

public:

	/** How the object should be interpolated from the 
		"Start" to the Destination. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	ECsEasingType Easing;

	/** The type of object that is being moved. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	ECsMover Mover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FVector3f FromLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FName MoveObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FString MoveActorLabel;

	/** Actor that is moving.
		Only valid if Mover == MoverType::Actor. */
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Movement")
	AActor* MoveActor;

	/** Component that is moving.
		Only valid if Mover == MoverType::Component */
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Movement")
	USceneComponent* MoveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	ECsMoveDestination Destination;

	/** If Destination == DestinationType::Location,
			World location to move to.
		If Destination != DestinationType::Location (Actor, Component, or Bone),
			Offset from the ToActor or ToComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FVector3f ToLocation;

	/** The name of the Object to move to.
		Object is Actor or Component.
		If Destination == DestinationType::Actor,
			then Actor's name.
		If Destination == DestinationType::Component | DestinationType::Bone,
			then Component's name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FName ToObjectName;

	/** Label of the Actor to move to.
		Only valid in EDITOR.
		Only valid if Destination == DestinationType:: Actor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FString ToActorLabel;

	/** Bone to move to.
		Only valid if Destination == DestinatinType::Component. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FName ToBone;

	/** Actor to move to.
		Only valid if Destination == DestinationType::Actor. */
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Movement")
	AActor* ToActor;

	/** Component to move to.
		Only valid if Destination == DestinationType::Component */
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Movement")
	USceneComponent* ToComponent;

	/** Component to move to.
		Only valid if Destination == DestinationType::Component */
	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Movement")
	USkeletalMeshComponent* ToMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FECsUpdateGroup Group;

	FCsMoveByInterp_Params() :
		Easing(ECsEasingType::Linear),
		Mover(ECsMover::Actor),
		FromLocation(FVector3f::ZeroVector),
		MoveObjectName(NAME_None),
		MoveActorLabel(),
		MoveActor(nullptr),
		MoveComponent(nullptr),
		Destination(ECsMoveDestination::Location),
		ToLocation(FVector3f::ZeroVector),
		ToObjectName(NAME_None),
		ToActorLabel(),
		ToBone(NAME_None),
		ToActor(nullptr),
		ToComponent(nullptr),
		ToMeshComponent(nullptr),
		Time(0.0f),
		Group()
	{
	}

#define ParamsType NCsMovement::NTo::NInterp::NParams::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	void ConditionalSetSafeMoveObject(const FString& Context, const UObject* WorldContext);

	void ConditionalSetSafeDestinationObject(const FString& Context, const UObject* WorldContext);

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

class AActor;
class USceneComponent;
class USkeletalMeshComponent;
class UObject;

namespace NCsMovement
{
	namespace NTo
	{
		namespace NInterp
		{
			namespace NParams
			{
				struct CSCORE_API FParams
				{
				#define MoverType NCsMovement::EMover
				#define DestinationType NCsMovement::EDestination

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(Easing, ECsEasingType)
					CS_DECLARE_MEMBER_WITH_PROXY(Mover, MoverType)
					CS_DECLARE_MEMBER_WITH_PROXY(FromLocation, FVector3f)
					CS_DECLARE_MEMBER_WITH_PROXY(MoveObjectName, FName)
					CS_DECLARE_MEMBER_WITH_PROXY(MoveActorLabel, FString)

					/** Actor that is moving.
						Only valid if Mover == MoverType::Actor. */
					TWeakObjectPtr<AActor> MoveActor;
					/** Component that is moving.
						Only valid if Mover == MoverType::Component */
					TWeakObjectPtr<USceneComponent> MoveComponent;

					CS_DECLARE_MEMBER_WITH_PROXY(Destination, DestinationType)

					/** If Destination == DestinationType::Location,
							World location to move to.
						If Destination != DestinationType::Location (Actor, Component, or Bone), 
							Offset from the ToActor or ToComponent. */
					CS_DECLARE_MEMBER_WITH_PROXY(ToLocation, FVector3f)
					
					/** The name of the Object to move to.
						Object is Actor or Component. 
						If Destination == DestinationType::Actor, 
							then Actor's name. 
						If Destination == DestinationType::Component | DestinationType::Bone,
							then Component's name. */
					CS_DECLARE_MEMBER_WITH_PROXY(ToObjectName, FName)

					/** Label of the Actor to move to.
						Only valid in EDITOR.
						Only valid if Destination == DestinationType:: Actor. */
					CS_DECLARE_MEMBER_WITH_PROXY(ToActorLabel, FString)

					/** Bone to move to. 
						Only valid if Destination == DestinatinType::Component. */
					CS_DECLARE_MEMBER_WITH_PROXY(ToBone, FName)

					/** Actor to move to.
						Only valid if Destination == DestinationType::Actor. */
					TWeakObjectPtr<AActor> ToActor;
					/** Component to move to. 
						Only valid if Destination == DestinationType::Component */
					TWeakObjectPtr<USceneComponent> ToComponent;
					TWeakObjectPtr<USkeletalMeshComponent> ToMeshComponent;

					CS_DECLARE_MEMBER_WITH_PROXY(Time, float)
					CS_DECLARE_MEMBER_WITH_PROXY(Group, FECsUpdateGroup)

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Easing, ECsEasingType::Linear),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Mover, MoverType::Actor),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(FromLocation, FVector3f::ZeroVector),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(MoveObjectName, NAME_None),
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(MoveActorLabel),
						MoveActor(nullptr),
						MoveComponent(nullptr),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Destination, DestinationType::Location),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(ToLocation, FVector3f::ZeroVector),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(ToObjectName, NAME_None),
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(ToActorLabel),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(ToBone, NAME_None),
						ToActor(nullptr),
						ToComponent(nullptr),
						ToMeshComponent(nullptr),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, 0.0f),
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Group)
					{
						CS_CTOR_SET_MEMBER_PROXY(Easing);
						CS_CTOR_SET_MEMBER_PROXY(Mover);
						CS_CTOR_SET_MEMBER_PROXY(FromLocation);
						CS_CTOR_SET_MEMBER_PROXY(MoveObjectName);
						CS_CTOR_SET_MEMBER_PROXY(MoveActorLabel);
						CS_CTOR_SET_MEMBER_PROXY(Destination);
						CS_CTOR_SET_MEMBER_PROXY(ToLocation);
						CS_CTOR_SET_MEMBER_PROXY(ToObjectName);
						CS_CTOR_SET_MEMBER_PROXY(ToActorLabel);
						CS_CTOR_SET_MEMBER_PROXY(ToBone);
						CS_CTOR_SET_MEMBER_PROXY(Time);
						CS_CTOR_SET_MEMBER_PROXY(Group);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Easing, ECsEasingType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Mover, MoverType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FromLocation, FVector3f)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MoveObjectName, FName)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MoveActorLabel, FString)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Destination, DestinationType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ToLocation, FVector3f)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ToObjectName, FName)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ToActorLabel, FString)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ToBone, FName)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Group, FECsUpdateGroup)

					void SetMoveActor(AActor* Value);
					AActor* GetMoveActor() const;

					void SetMoveComponent(USceneComponent* Value);
					USceneComponent* GetMoveComponent() const;

					void SetToActor(AActor* Value);
					AActor* GetToActor() const;

					void SetToComponent(USceneComponent* Value);
					USceneComponent* GetToComponent() const;

					void SetToMeshComponent(USkeletalMeshComponent* Value);
					USkeletalMeshComponent* GetToMeshComponent() const;

					void ConditionalSetMoveObjectChecked(const FString& Context, UObject* WorldContext);

					void ConditionalSetDestinationObjectChecked(const FString& Context, UObject* WorldContext);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

					FVector3f GetEndLocation() const;

					void Reset();

				#undef MoverType
				#undef DestinationType
				};

				struct CSCORE_API FResource : public TCsResourceContainer<FParams>
				{
				};

				#define CS_PARAMS_PAYLOAD_SIZE 256

				struct CSCORE_API FManager : public NCsResource::NManager::NValue::TFixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
				{
				};

				#undef CS_PARAMS_PAYLOAD_SIZE
			}
		}

		namespace NSpeed
		{
			namespace NParams
			{
				struct CSCORE_API FParams
				{

				};
			}
		}
	}
}

#pragma endregion FCsMoveByInterp_Params

// SpeedFormat
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsSpeedFormat : uint8
{
	UUpS				UMETA(DisplayName = "Unreal Units per Second"),
	MpH					UMETA(DisplayName = "Miles per Hour"),
	KpH					UMETA(DisplayName = "Kilometers per Hour"),
	ECsSpeedFormat_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpeedFormat final : public TCsEnumMap<ECsSpeedFormat>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeedFormat, ECsSpeedFormat)
};

namespace NCsSpeedFormat
{
	typedef ECsSpeedFormat Type;

	namespace Ref
	{
		extern CSCORE_API const Type UUpS;
		extern CSCORE_API const Type MpH;
		extern CSCORE_API const Type KpH;
		extern CSCORE_API const Type ECsSpeedFormat_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpeed
{
	enum class EFormat : uint8 
	{
		// Unreal Units per Second
		UUpS,
		// Miles per Hour
		MpH,
		// Kilometers per Hour
		KpH,
		EFormat_MAX
	};

	struct CSCORE_API EMFormat final : public TCsEnumMap<EFormat>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMFormat, EFormat)
	};

	namespace NFormat
	{
		typedef EFormat Type;

		extern CSCORE_API const Type UUpS;
		extern CSCORE_API const Type MpH;
		extern CSCORE_API const Type KpH;
		extern CSCORE_API const Type EFormat_MAX;
	}
}

#pragma endregion SpeedFormat

// 1 uu = ~ 0.00000621372 mi
// 1 mi = 160934 uu
// 1 sec = ~0.000277778 hr
// 1 hr = 3600 sec

// UUpS to MpH = 3600 / 160943 = ~ 0.022368167612
#define CS_UNREAL_UNITS_PER_SECOND_TO_MILES_PER_HOUR 0.022368167612f
// MpH to UUpS = 160943 / 3600 = ~ 44.7063889
#define CS_MILES_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND 44.7063889f
// UUpS to KpH = 3600 / 100000 = 0.036
#define CS_UNREAL_UNITS_PER_SECOND_TO_KILOMETERS_PER_HOUR 0.036f
// KpH to UUpS = 100000 / 3600 = ~ 27.7777778
#define CS_KILOMETERS_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND 27.7777778f
// MpH to KpH
#define CS_MILES_PER_HOUR_TO_KILOMETERS_PER_HOUR 1.60934f
// KpH to MpH
#define CS_KILOMETERS_PER_HOUR_TO_MILES_PER_HOUR 0.621371

// FCsSpeed
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSpeed
{
	GENERATED_USTRUCT_BODY()

	/** UUpS: Unreal Units per Second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement", meta = (DisplayName = "UUpS: Unreal Units per Second", ClampMin = "0.0", UIMin = "0.0"))
	float UUpS;

	/** MpH: Miles per Hour */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement", meta = (DisplayName = "MpH: Miles per Hour", ClampMin = "0.0", UIMin = "0.0"))
	float MpH;

	/** KpH: Kilometers per Hour */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement", meta = (DisplayName = "KpH: Kilometers per Hour", ClampMin = "0.0", UIMin = "0.0"))
	float KpH;

	FCsSpeed() :
		UUpS(0.0f),
		MpH(0.0f),
		KpH(0.0f)
	{
	}

	FORCEINLINE void FromUUpS()
	{
		MpH = CS_UNREAL_UNITS_PER_SECOND_TO_MILES_PER_HOUR * UUpS;
		KpH = CS_UNREAL_UNITS_PER_SECOND_TO_KILOMETERS_PER_HOUR * UUpS;
	}

	FORCEINLINE void FromMpH()
	{
		UUpS = CS_MILES_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND * MpH;
		KpH = CS_MILES_PER_HOUR_TO_KILOMETERS_PER_HOUR * MpH;
	}

	FORCEINLINE void FromKpH()
	{
		UUpS = CS_KILOMETERS_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND * KpH;
		MpH = CS_KILOMETERS_PER_HOUR_TO_MILES_PER_HOUR * KpH;
	}

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("%f UUpS %f MpH %f KpH"), UUpS, MpH, KpH); }

#if WITH_EDITOR
	void OnPostEditChange(const FName& PropertyName);
#endif // #if WITH_EDITOR

private:

	FORCEINLINE void __Nothing() const {}
};

#pragma endregion FCsSpeed

// SpeedInterpMethod
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsSpeedInterpMethod : uint8
{
	/** Apply the Acceleration as a Delta. 
	     Usually in the form of sf = so + a * dt. 
		  sf = Final Speed 
		  so = Initial Speed
		  a = Acceleration
		  dt = Delta Time */
	Acceleration				UMETA(DisplayName = "Acceleration"),
	/** Using a Duration and Easing Type, determine the Speed. */
	Easing						UMETA(DisplayName = "Easing"),
	/** Using a Duration and Curve, determine the Speed. */
	Curve						UMETA(DisplayName = "Curve"),
	ECsSpeedInterpMethod_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpeedInterpMethod final : public TCsEnumMap<ECsSpeedInterpMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeedInterpMethod, ECsSpeedInterpMethod)
};

namespace NCsSpeedInterpMethod
{
	typedef ECsSpeedInterpMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type Acceleration;
		extern CSCORE_API const Type Easing;
		extern CSCORE_API const Type Curve;
		extern CSCORE_API const Type ECsSpeedInterpMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpeed
{
	namespace NInterp
	{
		enum class EMethod : uint8
		{
			/** Apply the Acceleration as a Delta.
			 Usually in the form of sf = so + a * dt.
			  sf = Final Speed
			  so = Initial Speed
			  a = Acceleration
			  dt = Delta Time */
			Acceleration,
			/** Using a Duration and Easing Type, determine the Speed. */
			Easing,
			/** Using a Duration and Curve, determine the Speed. */
			Curve,
			EMethod_MAX
		};

		struct CSCORE_API EMMethod final : public TCsEnumMap<EMethod>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMMethod, EMethod)
		};

		namespace NMethod
		{
			typedef EMethod Type;

			extern CSCORE_API const Type Acceleration;
			extern CSCORE_API const Type Easing;
			extern CSCORE_API const Type Curve;
			extern CSCORE_API const Type EMethod_MAX;
		}
	}
}

#pragma endregion SpeedInterpMethod

// SpeedInterpDirection
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsSpeedInterpDirection : uint8
{
	/** Increasing toward the Target Speed. */
	Increasing					UMETA(DisplayName = "Increasing"),
	/** Decreasing toward the Target Speed. */
	Decreasing					UMETA(DisplayName = "Decreasing"),
	ECsSpeedInterpDirection_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpeedInterpDirection final : public TCsEnumMap<ECsSpeedInterpDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeedInterpDirection, ECsSpeedInterpDirection)
};

namespace NCsSpeedInterpDirection
{
	typedef ECsSpeedInterpDirection Type;

	namespace Ref
	{
		extern CSCORE_API const Type Increasing;
		extern CSCORE_API const Type Decreasing;
		extern CSCORE_API const Type ECsSpeedInterpDirection_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpeed
{
	namespace NInterp
	{
		enum class EDirection : uint8 
		{
			/** Increasing toward the Target Speed. */
			Increasing,
			/** Decreasing toward the Target Speed. */
			Decreasing,
			EDirection_MAX
		};

		struct CSCORE_API EMDirection final : public TCsEnumMap<EDirection>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDirection, EDirection)
		};

		namespace NDirection
		{
			typedef EDirection Type;

			extern CSCORE_API const Type Increasing;
			extern CSCORE_API const Type Decreasing;
			extern CSCORE_API const Type EDirection_MAX;
		}
	}
}

#pragma endregion SpeedInterpDirection

// FCsAcceleration
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsAcceleration
{
	GENERATED_USTRUCT_BODY()

	/** UUpS/S: Unreal Units per Second Second. 
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement", meta = (DisplayName = "UUpS/S: Unreal Units per Second Second", ClampMin = "0.0", UIMin = "0.0"))
	float UUpSS;
	 
	/** MpH/S: Miles per Hour Second Second.
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement", meta = (DisplayName = "MpH/S: Miles per Hour Second", ClampMin = "0.0", UIMin = "0.0"))
	float MpHS;

	/** KpH/S: Kilometers per Hour Second.
		 This is only Valid for Method == Delta (ECsAccelerationMethod::Delta). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement", meta = (DisplayName = "KpH/S: Kilometers per Hour Second", ClampMin = "0.0", UIMin = "0.0"))
	float KpHS;

	FCsAcceleration() :
		UUpSS(0.0f),
		MpHS(0.0f),
		KpHS(0.0f)
	{
	}

	FORCEINLINE void FromUUpSS()
	{
		MpHS = CS_UNREAL_UNITS_PER_SECOND_TO_MILES_PER_HOUR * UUpSS;
		KpHS = CS_UNREAL_UNITS_PER_SECOND_TO_KILOMETERS_PER_HOUR * UUpSS;
	}

	FORCEINLINE void FromMpHS()
	{
		UUpSS = CS_MILES_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND * MpHS;
		KpHS = CS_MILES_PER_HOUR_TO_KILOMETERS_PER_HOUR * MpHS;
	}

	FORCEINLINE void FromKpHS()
	{
		UUpSS = CS_KILOMETERS_PER_HOUR_TO_UNREAL_UNITS_PER_SECOND * KpHS;
		MpHS = CS_KILOMETERS_PER_HOUR_TO_MILES_PER_HOUR * KpHS;
	}

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("%f UUpSS %f MpHS %f KpHS"), UUpSS, MpHS, KpHS); }

#if WITH_EDITOR
	void OnPostEditChange(const FName& PropertyName);
#endif // #if WITH_EDITOR
};

#pragma endregion FCsAcceleration

// FCsSpeedInterpInfo
#pragma region

class UCurveFloat;

// NCsSpeed:NInterp::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpeed, NInterp, FInfo)

/**
* Describes how speed should be interpolated.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSpeedInterpInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	ECsSpeedInterpMethod Method;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	ECsSpeedInterpDirection Direction;

	/** 
		 This is only Valid for Method == Easing (ECsSpeedInterpMethod::Easing). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	ECsEasingType Easing;

	/**
		 This is only Valid for Method == Curve (ECsSpeedInterpMethod::Curve). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	UCurveFloat* Curve;

	/** Time (Duration) it should take to go from Min Speed to Max Speed. 
	     This is only Valid for Methods:
		   Easing	(ECsSpeedInterpMethod::Easing) 
		   Curve	(ECsSpeedInterpMethod::Curve) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	float Time;

	/** This is only Valid for Method == Acceleration (ECsSpeedInterpMethod::Acceleration). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Movement")
	FCsAcceleration Acceleration;

	FCsSpeedInterpInfo() :
		Method(ECsSpeedInterpMethod::Acceleration),
		Direction(ECsSpeedInterpDirection::Increasing),
		Easing(ECsEasingType::Linear),
		Curve(nullptr),
		Time(0.0f),
		Acceleration()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

#define InfoType NCsSpeed::NInterp::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	FString PrintSummary(const int32& IndentSpaces = 0);

private:

	FORCEINLINE void __Nothing() const {}

public:

#if WITH_EDITOR
	void OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName);
#endif // #if WITH_EDITOR
};

namespace NCsSpeed
{
	namespace NInterp
	{
		struct CSCORE_API FInfo
		{
		#define MethodType NCsSpeed::NInterp::EMethod
		#define DirectionType NCsSpeed::NInterp::EDirection

		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Method, MethodType)
			CS_DECLARE_MEMBER_WITH_PROXY(Direction, DirectionType)
			CS_DECLARE_MEMBER_WITH_PROXY(Easing, ECsEasingType)
			CS_DECLARE_MEMBER_WITH_PROXY(Curve, UCurveFloat*)
			CS_DECLARE_MEMBER_WITH_PROXY(Time, float)
			CS_DECLARE_MEMBER_WITH_PROXY(Acceleration, FCsAcceleration)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Method, MethodType::Acceleration),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Direction, DirectionType::Increasing),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Easing, ECsEasingType::Linear),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Curve, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, 0.0f),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Acceleration)
			{
				CS_CTOR_SET_MEMBER_PROXY(Method);
				CS_CTOR_SET_MEMBER_PROXY(Direction);
				CS_CTOR_SET_MEMBER_PROXY(Easing);
				CS_CTOR_SET_MEMBER_PROXY(Curve);
				CS_CTOR_SET_MEMBER_PROXY(Time);
				CS_CTOR_SET_MEMBER_PROXY(Acceleration);
			}

			FORCEINLINE FInfo(FInfo& B)
			{
				SetMethod(B.GetMethod());
				SetDirection(B.GetDirection());
				SetEasing(B.GetEasing());
				SetCurve(B.GetCurve());
				SetTime(B.GetTime());
				SetAcceleration(B.GetAcceleration());
			}

			FORCEINLINE FInfo(const FInfo& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Method, MethodType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Direction, DirectionType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Easing, ECsEasingType)
			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Curve, UCurveFloat)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Acceleration, FCsAcceleration)

			FORCEINLINE void Copy(const FInfo& B)
			{
				SetMethod(B.GetMethod());
				SetDirection(B.GetDirection());
				SetEasing(B.GetEasing());
				SetCurve(B.GetCurve());
				SetTime(B.GetTime());
				SetAcceleration(B.GetAcceleration());
			}

			bool IsValidChecked(const FString& Context) const { return true; }
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const { return true; }

		#undef MethodType
		#undef DirectionType
		};
	}
}

#pragma endregion FCsSpeedInterpInfo

// NCsSpeed::NInterp::FInterp
#pragma region

// NCsSpeed::NInterp::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpeed, NInterp, FInfo)

namespace NCsSpeed
{
	namespace NInterp
	{
		/**
		*
		*/
		struct CSCORE_API FInterp
		{
		#define InfoType NCsSpeed::NInterp::FInfo

		public:

			bool bMinBound;

			/** Usually the same as MinSpeedAsPercent.
				[-1.0f, 1.0f] inclusive. */
			float MinBound;

			bool bMaxBound;

			/** Usually 1.0f.
				[-1.0f, 1.0f] inclusive. */
			float MaxBound;;

			/** Max Speed in UUpS (Unreal Units per Second). 
				This is usually considered to be a value of 1.0f on a normalized scale. 
				If MaxSpeedAsPercent is altered 1.0f to something < 1.0f, the Speed will
				be clamped to PercentOfMaxSpeed * MaxSpeed. */
			float MaxSpeed;

			/** Maximum Speed as a percent.
				 % of MaxSpeed.
				 [0.0f, 1.0f] inclusive. */
			float PercentOfMaxSpeed;

			/** Minimum Speed in UUpS (Unreal Units per Second). */
			float MinSpeed;

			/** Minimum Speed as a percent. 
				 MinSpeed / MaxSpeed. 
				 [0.0f, 1.0f] inclusive. */
			float MinSpeedAsPercent;

			/** Describes how to interpolate Speed over time. */
			InfoType* Info;

			/** The desired speed to reach in UUpS (Unreal Units per Second). 
				Should be <= MaxSpeed. */
			float TargetSpeed;

			/** Target Speed as a percent. 
				 TargetSpeed / MaxSpeed. */
			float TargetSpeedAsPercent;

			/** Sign 1 or -1 to indicate whether Speed is increasing (1) or 
				decreasing (-1) to TargetSpeedAsPercent */
			float DirectionSign;

			/** Interp's Acceleration as a percent. 
				 Interp->Acceleration.UUpSS / MaxSpeed.
				 [0.0f , 1.0f] inclusive. 
				 Only Valid if Interp->Method == Acceleration (ECsSpeedInterpMethod::Acceleration) */
			float AccelerationAsPercent;

			float CurrentSpeedAsPercent;

			float CurrentAlpha;

			FInterp() :
				bMinBound(true),
				MinBound(0.0f),
				bMaxBound(true),
				MaxBound(1.0f),
				MaxSpeed(0.0f),
				PercentOfMaxSpeed(1.0f),
				MinSpeed(0.0f),
				MinSpeedAsPercent(0.0f),
				Info(nullptr),
				TargetSpeed(0.0f),
				TargetSpeedAsPercent(0.0f),
				DirectionSign(1.0f),
				AccelerationAsPercent(0.0f),
				CurrentSpeedAsPercent(0.0f),
				CurrentAlpha(0.0f)
			{
			}

			void SetMaxSpeed(const float& Speed);
			
			void SetPercentOfMaxSpeed(const float& Percent);

			void SetMinSpeed(const float& Speed);

			void SetInfo(InfoType* InInfo);

			void SetTargetSpeed(const float& Speed);

			void SetTargetSpeedAsPercent(const float& Percent);

			/**
			*
			*
			* @param Percent Value [0.0f, 1.0f] Inclusive.
			*/
			void SetCurrentSpeedAsPercent(const float& Percent);

			void Update(const float& DeltaTime);

			float RemapValue(const float& Value) const;

		#undef InfoType
		};
	}
}

#pragma endregion NCsSpeed::NInterp::FInterp