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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	uint8 Id;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	uint8 ObserveeId;

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

		// Sight

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActorByRadius;
	TCsBool_Ref bSeesActorByRadiusHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorByRadius, const uint8&, const uint8&, const bool&);
	FOnSeesActorByRadius OnSeesActorByRadius_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActorByDot;
	TCsBool_Ref bSeesActorByDotHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorByDot, const uint8&, const uint8&, const bool&);
	FOnSeesActorByRadius OnSeesActorByDot_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActor;
	TCsBool_Ref bSeesActorHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActor, const uint8&, const uint8&, const bool&);
	FOnSeesActor OnSeesActor_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActorBody;
	TCsBool_Ref bSeesActorBodyHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorBody, const uint8&, const uint8&, const bool&);
	FOnSeesActorBody OnSeesActorBody_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bSeesActorHead;
	TCsBool_Ref bSeesActorHeadHandle;
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSeesActorHead, const uint8&, const uint8&, const bool&);
	FOnSeesActorHead OnSeesActorHead_Event;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastTime_SeesActorByRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastTime_SeesActorByDot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float LastTime_SeesActor;
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
		Id = 255;
		ObserveeId = 255;
		MeToActorDir = FVector::ZeroVector;
		MeToActorDistance = 0.0f;;
		MeToActorDistanceSq = 0.0f;
		MeToActorDirXY = FVector::ZeroVector;
		MeToActorDistanceXY = 0.0f;
		MeToActorDistanceXYSq = 0.0f;
		MeToActorDot = 0.0f;;
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