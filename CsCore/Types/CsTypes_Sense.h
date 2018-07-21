// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Sense.generated.h"
#pragma once

// SenseActorType

USTRUCT(BlueprintType)
struct CSCORE_API FECsSenseActorType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsSenseActorType() {}
	FECsSenseActorType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsSenseActorType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsSenseActorType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsSenseActorType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsSenseActorType : public TCsEnumStructMap<FECsSenseActorType, uint8>
{
protected:
	EMCsSenseActorType() {}
	EMCsSenseActorType(const EMCsSenseActorType &) = delete;
	EMCsSenseActorType(EMCsSenseActorType &&) = delete;
public:
	~EMCsSenseActorType() {}
private:
	static EMCsSenseActorType* Instance;

public:
	static EMCsSenseActorType& Get();
};

namespace ECsSenseActorType
{
	extern CSCORE_API const FECsSenseActorType Player;
	extern CSCORE_API const FECsSenseActorType AI;
}

// SenseTeam

UENUM(BlueprintType)
namespace ECsSenseTeam
{
	enum Type
	{
		Friendly			UMETA(DisplayName = "Friendly"),
		Enemy				UMETA(DisplayName = "Enemy"),
		Neutral				UMETA(DisplayName = "Neutral"),
		ECsSenseTeam_MAX	UMETA(Hidden),
	};
}

typedef ECsSenseTeam::Type TCsSenseTeam;

struct CSCORE_API EMCsSenseTeam : public TCsEnumMap<ECsSenseTeam::Type>
{
protected:
	EMCsSenseTeam() {}
	EMCsSenseTeam(const EMCsSenseTeam &) = delete;
	EMCsSenseTeam(EMCsSenseTeam &&) = delete;
public:
	~EMCsSenseTeam() {}
private:
	static EMCsSenseTeam* Instance;

public:
	static EMCsSenseTeam& Get();
};

namespace ECsSenseTeam
{
	namespace Ref
	{
		extern CSCORE_API const Type Friendly;
		extern CSCORE_API const Type Enemy;
		extern CSCORE_API const Type Neutral;
		extern CSCORE_API const Type ECsSenseTeam_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsSenseInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	FECsSenseActorType ActorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	TEnumAsByte<ECsSenseTeam::Type> Team;

	/** TODO: Need to update UniqueObjectId to be FGuid in GameInstance */
	UPROPERTY()
	uint64 Id;
	UPROPERTY()
	uint64 ObserveeId;

	// Me to Actor

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FVector MeToActorDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToActorDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToActorDistanceSq;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FVector MeToActorDirXY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToActorDistanceXY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToActorDistanceXYSq;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToActorDot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float MeToActorAbsDeltaAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FRotator MeToActorBodyRotation;

	// View to Actor

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FVector ViewToActorDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FRotator ViewToActorBodyRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float ViewToActorDot;

	// Sight

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActorByRadius;
	TCsBool_Ref bSeesActorByRadiusHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorByRadius, const uint64&, const uint64&, const bool&);
	FOnSeesActorByRadius OnSeesActorByRadius_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActorByDot;
	TCsBool_Ref bSeesActorByDotHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorByDot, const uint64&, const uint64&, const bool&);
	FOnSeesActorByRadius OnSeesActorByDot_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActor;
	TCsBool_Ref bSeesActorHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActor, const uint64&, const uint64&, const bool&);
	FOnSeesActor OnSeesActor_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActorBody;
	TCsBool_Ref bSeesActorBodyHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorBody, const uint64&, const uint64&, const bool&);
	FOnSeesActorBody OnSeesActorBody_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActorHead;
	TCsBool_Ref bSeesActorHeadHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorHead, const uint64&, const uint64&, const bool&);
	FOnSeesActorHead OnSeesActorHead_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastTime_SeesActorByRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastTime_SeesActorByDot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastTime_SeesActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float SeesActorBodyTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float NotSeesActorBodyTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastTime_SeesActorBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastTime_SeesActorHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float StartTime_TraceMeToActorBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float StartTime_TraceMeToActorHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	uint8 TraceRequestId_MeToActorBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	uint8 TraceRequestId_MeToActorHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastKnown_DistanceToActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FVector LastKnown_ActorLocation;

	FCsSenseInfo()
	{
		ActorType = EMCsSenseActorType::Get().GetMAX();
		Team = ECsSenseTeam::Friendly;
		Id = MAX_uint64;
		ObserveeId = MAX_uint64;
		MeToActorDir = FVector::ZeroVector;
		MeToActorDistance = 0.0f;;
		MeToActorDistanceSq = 0.0f;
		MeToActorDirXY = FVector::ZeroVector;
		MeToActorDistanceXY = 0.0f;
		MeToActorDistanceXYSq = 0.0f;
		MeToActorDot = 0.0f;
		MeToActorBodyRotation = FRotator::ZeroRotator;
		// Sight
		bSeesActorByRadius= false;
		bSeesActorByDot= false;
		bSeesActor = false;
		bSeesActorBody = false;
		bSeesActorHead = false;
		LastTime_SeesActorByRadius = 0.0f;
		LastTime_SeesActorByDot = 0.0f;
		LastTime_SeesActor = 0.0f;
		LastTime_SeesActorBody = 0.0f;
		LastTime_SeesActorHead = 0.0f;
		StartTime_TraceMeToActorBody = 0.0f;
		StartTime_TraceMeToActorHead = 0.0f;
		TraceRequestId_MeToActorBody = 255;
		TraceRequestId_MeToActorHead = 255;
		LastKnown_DistanceToActor = 0.0f;
		LastKnown_ActorLocation = FVector::ZeroVector;
	}

	~FCsSenseInfo() 
	{
		bSeesActorByRadiusHandle.Reset();
		bSeesActorByDotHandle.Reset();
		bSeesActorHandle.Reset();
		bSeesActorBodyHandle.Reset();
		bSeesActorHeadHandle.Reset();
	}

public:

	void Init()
	{
		bSeesActorByRadiusHandle.Set(&bSeesActorByRadius);
		bSeesActorByRadiusHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo::OnChange_bSeesActorByRadius);
		OnSeesActorByRadius_Event.Clear();
		bSeesActorByDotHandle.Set(&bSeesActorByDot);
		bSeesActorByDotHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo::OnChange_bSeesActorByDot);
		OnSeesActorByDot_Event.Clear();
		bSeesActorHandle.Set(&bSeesActor);
		bSeesActorHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo::OnChange_bSeesActor);
		OnSeesActor_Event.Clear();
		bSeesActorBodyHandle.Set(&bSeesActorBody);
		bSeesActorBodyHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo::OnChange_bSeesActorBody);
		OnSeesActorBody_Event.Clear();
		bSeesActorHeadHandle.Set(&bSeesActorHead);
		bSeesActorHeadHandle.OnChange_Event.AddRaw(this, &FCsSenseInfo::OnChange_bSeesActorHead);
		OnSeesActorHead_Event.Clear();
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
};

USTRUCT(BlueprintType)
struct FCsSenseData
{
	GENERATED_USTRUCT_BODY()

	/** Whether to Sense by Radius */
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Sense", meta = (InlineEditConditionToggle))
	bool bRadius;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Sense", meta = (editcondition = "bRadius", ClampMin = "0.0", UIMin = "0.0"))
	float Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	float RadiusSq;

	/** Minimum View Angle for Sensing */
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Sense", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Angle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	float Radians;
	/** Minimum Dot to Target Actor for Sensing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	float Dot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	TMap<FECsSenseActorType, float> TraceIntervals;

	FCsSenseData()
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
	~FCsSenseData(){}

	FORCEINLINE FCsSenseData& operator=(const FCsSenseData& B)
	{
		bRadius = B.bRadius;
		Radius = B.Radius;
		RadiusSq = B.RadiusSq;
		Angle = B.Angle;
		Radians = B.Radians;
		Dot = B.Dot;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsSenseData& B) const
	{
		return bRadius == B.bRadius && Radius == B.Radius && RadiusSq == B.RadiusSq && Angle == B.Angle && Radians == B.Radians && Dot == B.Dot;
	}

	FORCEINLINE bool operator!=(const FCsSenseData& B) const
	{
		return !(*this == B);
	}
};

// PostEditChangeProperty FCsSenseData
#define CS_PECP_FCS_SENSE_DATA(PropertyName, MemberName)	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsSenseData, Radius)) \
															{ \
																MemberName.RadiusSq = MemberName.Radius * MemberName.Radius; \
															} \
															if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsSenseData, Angle)) \
															{ \
																MemberName.Radians = FMath::DegreesToRadians(MemberName.Angle); \
																MemberName.Dot = FMath::Cos(MemberName.Radians); \
															}

USTRUCT(BlueprintType)
struct FCsSenseData_Override
{
	GENERATED_USTRUCT_BODY()

	/** Whether to Sense by Radius */
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Sense", meta = (InlineEditConditionToggle))
	bool bOverride_Radius;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Sense", meta = (editcondition = "bOverride_Radius", ClampMin = "0.0", UIMin = "0.0"))
	float Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	float RadiusSq;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Sense", meta = (InlineEditConditionToggle))
	bool bOverride_Angle;
	/** Minimum View Angle for Sensing */
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Sense", meta = (editcondition = "bOverride_Angle", ClampMin = "0.0", UIMin = "0.0"))
	float Angle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	float Radians;
	/** Minimum Dot to Target Actor for Sensing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	float Dot;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Sense", meta = (InlineEditConditionToggle))
	bool bOverride_TraceIntervals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense", meta = (editcondition = "bOverride_TraceIntervals"))
	TMap<FECsSenseActorType, float> TraceIntervals;

	FCsSenseData_Override()
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
	~FCsSenseData_Override() {}

	FORCEINLINE FCsSenseData_Override& operator=(const FCsSenseData_Override& B)
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

	FORCEINLINE bool operator==(const FCsSenseData_Override& B) const
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

	FORCEINLINE bool operator!=(const FCsSenseData_Override& B) const
	{
		return !(*this == B);
	}
};

// PostEditChangeProperty FCsSenseData
#define CS_PECP_FCS_SENSE_DATA_OVERRIDE(PropertyName, MemberName)	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsSenseData_Override, Radius)) \
																	{ \
																		MemberName.RadiusSq = MemberName.Radius * MemberName.Radius; \
																	} \
																	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsSenseData_Override, Angle)) \
																	{ \
																		MemberName.Radians = FMath::DegreesToRadians(MemberName.Angle); \
																		MemberName.Dot = FMath::Cos(MemberName.Radians); \
																	}