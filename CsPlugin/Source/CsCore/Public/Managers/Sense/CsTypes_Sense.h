// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/Property/Ref/CsProperty_Ref_bool.h"
#include "Types/Property/Ref/CsProperty_Ref_Vector.h"

#include "CsTypes_Sense.generated.h"

// SenseObjectType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSenseObjectType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSenseObjectType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSenseObjectType)

struct CSCORE_API EMCsSenseObjectType : public TCsEnumStructMap<FECsSenseObjectType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSenseObjectType, FECsSenseObjectType, uint8)
};

namespace NCsSenseObjectType
{
	typedef FECsSenseObjectType Type;

	extern CSCORE_API const Type Player;
	extern CSCORE_API const Type AI;
}

#pragma endregion SenseObjectType

// SenseTeam
#pragma region

UENUM(BlueprintType)
enum class ECsSenseTeam : uint8
{
	Friendly			UMETA(DisplayName = "Friendly"),
	Enemy				UMETA(DisplayName = "Enemy"),
	Neutral				UMETA(DisplayName = "Neutral"),
	ECsSenseTeam_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSenseTeam : public TCsEnumMap<ECsSenseTeam>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSenseTeam, ECsSenseTeam)
};

namespace NCsSenseTeam
{
	typedef ECsSenseTeam Type;

	namespace Ref
	{
		extern CSCORE_API const Type Friendly;
		extern CSCORE_API const Type Enemy;
		extern CSCORE_API const Type Neutral;
		extern CSCORE_API const Type ECsSenseTeam_MAX;
	}
}

#pragma endregion SenseTeam

// SenseActorType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSenseActorType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSenseActorType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSenseActorType)

struct CSCORE_API EMCsSenseActorType : public TCsEnumStructMap<FECsSenseActorType, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsSenseActorType)
};

namespace ECsSenseActorType
{
	extern CSCORE_API const FECsSenseActorType Player;
	extern CSCORE_API const FECsSenseActorType AI;
}

#pragma endregion SenseActorType

// FCsSenseInfo_DEPRECATED
#pragma region

USTRUCT(BlueprintType)
struct FCsSenseInfo_DEPRECATED
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sense")
	FECsSenseActorType ActorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sense")
	ECsSenseTeam Team;

	/** TODO: Need to update UniqueObjectId to be FGuid in GameInstance */
	UPROPERTY()
	uint64 Id;
	UPROPERTY()
	uint64 ObserveeId;

	// Me to Actor

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	FVector3f MeToActorDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float MeToActorDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float MeToActorDistanceSq;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	FVector3f MeToActorDirXY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float MeToActorDistanceXY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float MeToActorDistanceXYSq;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float MeToActorDot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float MeToActorAbsDeltaAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	FRotator3f MeToActorBodyRotation;

	// View to Actor

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	FVector3f ViewToActorDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	FRotator3f ViewToActorBodyRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float ViewToActorDot;

	// Sight

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	bool bSeesActorByRadius;
	TCsBool_Ref bSeesActorByRadiusHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorByRadius, const uint64&, const uint64&, const bool&);
	FOnSeesActorByRadius OnSeesActorByRadius_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	bool bSeesActorByDot;
	TCsBool_Ref bSeesActorByDotHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorByDot, const uint64&, const uint64&, const bool&);
	FOnSeesActorByRadius OnSeesActorByDot_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	bool bSeesActor;
	TCsBool_Ref bSeesActorHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActor, const uint64&, const uint64&, const bool&);
	FOnSeesActor OnSeesActor_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	bool bSeesActorBody;
	TCsBool_Ref bSeesActorBodyHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorBody, const uint64&, const uint64&, const bool&);
	FOnSeesActorBody OnSeesActorBody_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	bool bSeesActorHead;
	TCsBool_Ref bSeesActorHeadHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorHead, const uint64&, const uint64&, const bool&);
	FOnSeesActorHead OnSeesActorHead_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float LastTime_SeesActorByRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float LastTime_SeesActorByDot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float LastTime_SeesActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float SeesActorBodyTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float NotSeesActorBodyTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float LastTime_SeesActorBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float LastTime_SeesActorHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float StartTime_TraceMeToActorBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float StartTime_TraceMeToActorHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	uint8 TraceRequestId_MeToActorBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	uint8 TraceRequestId_MeToActorHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float LastKnown_DistanceToActor;
	
	UPROPERTY(VisibleAnywhere, Category = "CsCore|Sense")
	FVector LastKnown_ActorLocation;
	TCsFVector_Ref LastKnown_ActorLocationHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChange_LastKnown_ActorLocation, const uint64&, const uint64&, const FVector3d&);
	FOnChange_LastKnown_ActorLocation OnChange_LastKnown_ActorLocation_Event;

	FCsSenseInfo_DEPRECATED()
	{
		ActorType = EMCsSenseActorType::Get().GetMAX();
		Team = ECsSenseTeam::Friendly;
		Id = MAX_uint64;
		ObserveeId = MAX_uint64;
		// Me to Actor
		MeToActorDir = FVector3f::ZeroVector;
		MeToActorDistance = 0.0f;;
		MeToActorDistanceSq = 0.0f;
		MeToActorDirXY = FVector3f::ZeroVector;
		MeToActorDistanceXY = 0.0f;
		MeToActorDistanceXYSq = 0.0f;
		MeToActorDot = 0.0f;
		MeToActorAbsDeltaAngle = 0.0f;
		MeToActorBodyRotation = FRotator3f::ZeroRotator;
		// View to Actor
		ViewToActorDir = FVector3f::ZeroVector;
		ViewToActorBodyRotation = FRotator3f::ZeroRotator;
		ViewToActorDot = 0.0f;
		// Sight
		bSeesActorByRadius= false;
		bSeesActorByDot= false;
		bSeesActor = false;
		bSeesActorBody = false;
		bSeesActorHead = false;
		LastTime_SeesActorByRadius = 0.0f;
		LastTime_SeesActorByDot = 0.0f;
		LastTime_SeesActor = 0.0f;
		SeesActorBodyTime = 0.0f;
		NotSeesActorBodyTime = 0.0f;
		LastTime_SeesActorBody = 0.0f;
		LastTime_SeesActorHead = 0.0f;
		StartTime_TraceMeToActorBody = 0.0f;
		StartTime_TraceMeToActorHead = 0.0f;
		TraceRequestId_MeToActorBody = 255;
		TraceRequestId_MeToActorHead = 255;
		LastKnown_DistanceToActor = 0.0f;
		LastKnown_ActorLocation = FVector3d::ZeroVector;
	}

	~FCsSenseInfo_DEPRECATED()
	{
		bSeesActorByRadiusHandle.Reset();
		bSeesActorByDotHandle.Reset();
		bSeesActorHandle.Reset();
		bSeesActorBodyHandle.Reset();
		bSeesActorHeadHandle.Reset();
		LastKnown_ActorLocationHandle.Reset();
	}

public:

	void Init()
	{
		bSeesActorByRadiusHandle.Set(&bSeesActorByRadius);
		bSeesActorByRadiusHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo_DEPRECATED::OnChange_bSeesActorByRadius);
		OnSeesActorByRadius_Event.Clear();
		bSeesActorByDotHandle.Set(&bSeesActorByDot);
		bSeesActorByDotHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo_DEPRECATED::OnChange_bSeesActorByDot);
		OnSeesActorByDot_Event.Clear();
		bSeesActorHandle.Set(&bSeesActor);
		bSeesActorHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo_DEPRECATED::OnChange_bSeesActor);
		OnSeesActor_Event.Clear();
		bSeesActorBodyHandle.Set(&bSeesActorBody);
		bSeesActorBodyHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo_DEPRECATED::OnChange_bSeesActorBody);
		OnSeesActorBody_Event.Clear();
		bSeesActorHeadHandle.Set(&bSeesActorHead);
		bSeesActorHeadHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo_DEPRECATED::OnChange_bSeesActorHead);
		OnSeesActorHead_Event.Clear();

		LastKnown_ActorLocationHandle.Set(&LastKnown_ActorLocation);
		LastKnown_ActorLocationHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo_DEPRECATED::OnChange_LastKnown_ActorLocation);
		OnChange_LastKnown_ActorLocation_Event.Clear();
	}

	void SetSeesActorByRadius(const bool &Value)
	{
		bSeesActorByRadius = Value;
		bSeesActorByRadiusHandle.Resolve();
	}

	void OnChange_bSeesActorByRadius(const bool &Value)
	{
		OnSeesActorByRadius_Event.Broadcast(Id, ObserveeId, Value);
	}

	void SetSeesActorByDot(const bool &Value)
	{
		bSeesActorByDot = Value;
		bSeesActorByDotHandle.Resolve();
	}

	void OnChange_bSeesActorByDot(const bool &Value)
	{
		OnSeesActorByDot_Event.Broadcast(Id, ObserveeId, Value);
	}

	void SetSeesActor(const bool &Value)
	{
		bSeesActor = Value;
		bSeesActorHandle.Resolve();
	}

	void OnChange_bSeesActor(const bool &Value)
	{
		OnSeesActor_Event.Broadcast(Id, ObserveeId, Value);
	}

	void SetSeesActorBody(const bool &Value)
	{
		bSeesActorBody = Value;
		bSeesActorBodyHandle.Resolve();
	}

	void OnChange_bSeesActorBody(const bool &Value)
	{
		OnSeesActorBody_Event.Broadcast(Id, ObserveeId, Value);
	}

	void SetSeesActorHead(const bool &Value)
	{
		bSeesActorHead = Value;
		bSeesActorHeadHandle.Resolve();
	}

	void OnChange_bSeesActorHead(const bool &Value)
	{
		OnSeesActorHead_Event.Broadcast(Id, ObserveeId, Value);
	}

	void OnChange_LastKnown_ActorLocation(const FVector3d& Value)
	{
		OnChange_LastKnown_ActorLocation_Event.Broadcast(Id, ObserveeId, Value);
	}
};

#pragma endregion FCsSenseInfo_DEPRECATED

// FCsSenseData_DEPRECATED
#pragma region

USTRUCT(BlueprintType)
struct FCsSenseData_DEPRECATED
{
	GENERATED_USTRUCT_BODY()

	/** Whether to Sense by Radius */
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "CsCore|Sense", meta = (ScriptName = "m_bRadius", InlineEditConditionToggle))
	bool bRadius;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "CsCore|Sense", meta = (ScriptName = "m_Radius", editcondition = "bRadius", ClampMin = "0.0", UIMin = "0.0"))
	float Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float RadiusSq;

	/** Minimum View Angle for Sensing */
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "CsCore|Sense", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Angle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float Radians;
	/** Minimum Dot to Target Actor for Sensing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float Dot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sense")
	TMap<FECsSenseActorType, float> TraceIntervals;

	FCsSenseData_DEPRECATED()
	{
		bRadius = false;
		Radius = 3000.0f;
		RadiusSq = Radius * Radius;
		Angle = 45.0f;
		Radians = FMath::DegreesToRadians(Angle);
		Dot = FMath::Cos(Radians);

		const int32& Count = EMCsSenseActorType::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			TraceIntervals.Add(EMCsSenseActorType::Get().GetEnumAt(I), 0.1f);
		}
	}
	~FCsSenseData_DEPRECATED(){}

	FORCEINLINE FCsSenseData_DEPRECATED& operator=(const FCsSenseData_DEPRECATED& B)
	{
		bRadius = B.bRadius;
		Radius = B.Radius;
		RadiusSq = B.RadiusSq;
		Angle = B.Angle;
		Radians = B.Radians;
		Dot = B.Dot;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsSenseData_DEPRECATED& B) const
	{
		return bRadius == B.bRadius && Radius == B.Radius && RadiusSq == B.RadiusSq && Angle == B.Angle && Radians == B.Radians && Dot == B.Dot;
	}

	FORCEINLINE bool operator!=(const FCsSenseData_DEPRECATED& B) const
	{
		return !(*this == B);
	}
};

// PostEditChangeProperty FCsSenseData_DEPRECATED
#define CS_PECP_FCS_SENSE_DATA(PropertyName, MemberName)	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsSenseData_DEPRECATED, Radius)) \
															{ \
																MemberName.RadiusSq = MemberName.Radius * MemberName.Radius; \
															} \
															if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsSenseData_DEPRECATED, Angle)) \
															{ \
																MemberName.Radians = FMath::DegreesToRadians(MemberName.Angle); \
																MemberName.Dot = FMath::Cos(MemberName.Radians); \
															}

#pragma endregion FCsSenseData_DEPRECATED

// FCsSenseData_Override_DEPRECATED
#pragma region

USTRUCT(BlueprintType)
struct FCsSenseData_Override_DEPRECATED
{
	GENERATED_USTRUCT_BODY()

	/** Whether to Sense by Radius */
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "CsCore|Sense", meta = (InlineEditConditionToggle))
	bool bOverride_Radius;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "CsCore|Sense", meta = (editcondition = "bOverride_Radius", ClampMin = "0.0", UIMin = "0.0"))
	float Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float RadiusSq;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "CsCore|Sense", meta = (InlineEditConditionToggle))
	bool bOverride_Angle;
	/** Minimum View Angle for Sensing */
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "CsCore|Sense", meta = (editcondition = "bOverride_Angle", ClampMin = "0.0", UIMin = "0.0"))
	float Angle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float Radians;
	/** Minimum Dot to Target Actor for Sensing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Sense")
	float Dot;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "CsCore|Sense", meta = (InlineEditConditionToggle))
	bool bOverride_TraceIntervals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sense", meta = (editcondition = "bOverride_TraceIntervals"))
	TMap<FECsSenseActorType, float> TraceIntervals;

	FCsSenseData_Override_DEPRECATED()
	{
		bOverride_Radius = false;
		Radius = 3000.0f;
		RadiusSq = Radius * Radius;
		bOverride_Angle = false;
		Angle = 45.0f;
		Radians = FMath::DegreesToRadians(Angle);
		Dot = FMath::Cos(Radians);

		bOverride_TraceIntervals = false;

		const int32& Count = EMCsSenseActorType::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			TraceIntervals.Add(EMCsSenseActorType::Get().GetEnumAt(I), 0.1f);
		}
	}
	~FCsSenseData_Override_DEPRECATED() {}

	FORCEINLINE FCsSenseData_Override_DEPRECATED& operator=(const FCsSenseData_Override_DEPRECATED& B)
	{
		bOverride_Radius = B.bOverride_Radius;
		Radius = B.Radius;
		RadiusSq = B.RadiusSq;
		bOverride_Angle = B.bOverride_Angle;
		Angle = B.Angle;
		Radians = B.Radians;
		Dot = B.Dot;

		TArray<FECsSenseActorType> Keys;
		TraceIntervals.GetKeys(Keys);

		for (const FECsSenseActorType& Key : Keys)
		{
			TraceIntervals[Key] = B.TraceIntervals[Key];
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsSenseData_Override_DEPRECATED& B) const
	{
		if (bOverride_Radius != B.bOverride_Radius)
			return false;
		if (Radius != B.Radius)
			return false;
		if (RadiusSq != B.RadiusSq)
			return false;
		if (bOverride_Angle != B.bOverride_Angle)
			return false;
		if (Angle != B.Angle)
			return false;
		if (Radians != B.Radians)
			return false;
		if (Dot != B.Dot)
			return false;

		TArray<FECsSenseActorType> Keys;
		TraceIntervals.GetKeys(Keys);

		for (const FECsSenseActorType& Key : Keys)
		{
			if (TraceIntervals[Key] != B.TraceIntervals[Key])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsSenseData_Override_DEPRECATED& B) const
	{
		return !(*this == B);
	}
};

// PostEditChangeProperty FCsSenseData_Override_DEPRECATED
#define CS_PECP_FCS_SENSE_DATA_OVERRIDE(PropertyName, MemberName)	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsSenseData_Override_DEPRECATED, Radius)) \
																	{ \
																		MemberName.RadiusSq = MemberName.Radius * MemberName.Radius; \
																	} \
																	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsSenseData_Override_DEPRECATED, Angle)) \
																	{ \
																		MemberName.Radians = FMath::DegreesToRadians(MemberName.Angle); \
																		MemberName.Dot = FMath::Cos(MemberName.Radians); \
																	}

#pragma endregion FCsSenseData_Override_DEPRECATED