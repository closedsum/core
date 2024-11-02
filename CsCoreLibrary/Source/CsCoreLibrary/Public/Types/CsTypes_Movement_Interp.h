// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Movement.h"
#include "Managers/Time/CsTypes_Update.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

#include "CsTypes_Movement_Interp.generated.h"

// FCsMoveByInterp_Params
#pragma region

struct FCsMoveByInterp_Params;

// ParamsType (NCsMovement::NTo::NInterp::NParams::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsMovement, NTo, NInterp, NParams, FParams)

namespace NCsMoveByInterp_Params
{
	using ParamsType = NCsMovement::NTo::NInterp::NParams::FParams;

	struct CSCORELIBRARY_API FImpl
	{
	public:

		static void CopyToParams(FCsMoveByInterp_Params* This, ParamsType* Params);
		static void CopyToParamsAsValue(const FCsMoveByInterp_Params* This, ParamsType* Params);
	};
}

class AActor;
class USceneComponent;
class USkeletalMeshComponent;
class UObject;

// ParamsType (NCsMovement::NTo::NInterp::NParams::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsMovement, NTo, NInterp, NParams, FParams)

USTRUCT(BlueprintType)
struct CSCORELIBRARY_API FCsMoveByInterp_Params
{
	GENERATED_USTRUCT_BODY()

public:

	/** How the object should be interpolated from the 
		"Start" to the Destination. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	ECsEasingType Easing;

	/** The type of object that is being moved. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	ECsMover Mover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	FVector3f FromLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	FName MoveObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	FString MoveActorLabel;

	/** Actor that is moving.
		Only valid if Mover == MoverType::Actor. */
	UPROPERTY(BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	AActor* MoveActor;

	/** Component that is moving.
		Only valid if Mover == MoverType::Component */
	UPROPERTY(BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	USceneComponent* MoveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	ECsMoveDestination Destination;

	/** If Destination == DestinationType::Location,
			World location to move to.
		If Destination != DestinationType::Location (Actor, Component, or Bone),
			Offset from the ToActor or ToComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	FVector3f ToLocation;

	/** The name of the Object to move to.
		Object is Actor or Component.
		If Destination == DestinationType::Actor,
			then Actor's name.
		If Destination == DestinationType::Component | DestinationType::Bone,
			then Component's name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	FName ToObjectName;

	/** Label of the Actor to move to.
		Only valid in EDITOR.
		Only valid if Destination == DestinationType:: Actor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	FString ToActorLabel;

	/** Bone to move to.
		Only valid if Destination == DestinatinType::Component. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	FName ToBone;

	/** Actor to move to.
		Only valid if Destination == DestinationType::Actor. */
	UPROPERTY(BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	AActor* ToActor;

	/** Component to move to.
		Only valid if Destination == DestinationType::Component */
	UPROPERTY(BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	USceneComponent* ToComponent;

	/** Component to move to.
		Only valid if Destination == DestinationType::Component */
	UPROPERTY(BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	USkeletalMeshComponent* ToMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
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

	using ParamsType = NCsMovement::NTo::NInterp::NParams::FParams;
	using _Impl = NCsMoveByInterp_Params::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params) { _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const { _Impl::CopyToParamsAsValue(this, Params); }

	void ConditionalSetSafeMoveObject(const FString& Context, const UObject* WorldContext);

	void ConditionalSetSafeDestinationObject(const FString& Context, const UObject* WorldContext);

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning) const;
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
				struct CSCORELIBRARY_API FParams
				{
					using MoverType = NCsMovement::EMover;
					using DestinationType = NCsMovement::EDestination;

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
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning) const;

					FVector3f GetEndLocation() const;

					void Reset();
				};

				struct CSCORELIBRARY_API FResource : public TCsResourceContainer<FParams>
				{
					~FResource(){}
				};

				#define CS_PARAMS_PAYLOAD_SIZE 256

				struct CSCORELIBRARY_API FManager : public NCsResource::NManager::NValue::TFixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
				{
					~FManager(){}
				};

				#undef CS_PARAMS_PAYLOAD_SIZE
			}
		}

		namespace NSpeed
		{
			namespace NParams
			{
				struct CSCORELIBRARY_API FParams
				{

				};
			}
		}
	}
}

#pragma endregion FCsMoveByInterp_Params

// FCsSpeedInterpInfo
#pragma region

struct FCsSpeedInterpInfo;

// InfoType (NCsSpeed:NInterp::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpeed, NInterp, FInfo)

namespace NCsSpeedInterpInfo
{
	using InfoType = NCsSpeed::NInterp::FInfo;

	struct CSCORELIBRARY_API FImpl
	{
	public:

		static void CopyToInfo(FCsSpeedInterpInfo* This, InfoType* Info);
		static void CopyToInfoAsValue(const FCsSpeedInterpInfo* This, InfoType* Info);
	};
}

class UCurveFloat;

// InfoType (NCsSpeed:NInterp::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpeed, NInterp, FInfo)

/**
* Describes how speed should be interpolated.
*/
USTRUCT(BlueprintType)
struct CSCORELIBRARY_API FCsSpeedInterpInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	ECsSpeedInterpMethod Method;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	ECsSpeedInterpDirection Direction;

	/** 
		 This is only Valid for Method == Easing (ECsSpeedInterpMethod::Easing). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	ECsEasingType Easing;

	/**
		 This is only Valid for Method == Curve (ECsSpeedInterpMethod::Curve). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	UCurveFloat* Curve;

	/** Time (Duration) it should take to go from Min Speed to Max Speed. 
	     This is only Valid for Methods:
		   Easing	(ECsSpeedInterpMethod::Easing) 
		   Curve	(ECsSpeedInterpMethod::Curve) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
	float Time;

	/** This is only Valid for Method == Acceleration (ECsSpeedInterpMethod::Acceleration). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCoreLibrary|Movement")
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

#if WITH_EDITOR
	void OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName);
#endif // #if WITH_EDITOR

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning) const;

	using InfoType = NCsSpeed::NInterp::FInfo;
	using _Impl = NCsSpeedInterpInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info) { _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info) const { _Impl::CopyToInfoAsValue(this, Info); }

	FString PrintSummary(const int32& IndentSpaces = 0);
};

namespace NCsSpeed
{
	namespace NInterp
	{
		struct CSCORELIBRARY_API FInfo
		{
			using MethodType = NCsSpeed::NInterp::EMethod;
			using DirectionType = NCsSpeed::NInterp::EDirection;

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
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning) const { return true; }
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
		struct CSCORELIBRARY_API FInterp
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