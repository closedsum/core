// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Sense.h"
#include "Types/CsTypes_Trace.h"
#include "CsManager_Sense.generated.h"

// SeesAnyBody
	// First Sees
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerSense_OnbFirstSeesAnyBody, const FECsSenseActorType&, ActorType, bool, Value);
	// First UnSees
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerSense_OnbFirstUnSeesAnyBody, const FECsSenseActorType&, ActorType, bool, Value);

UCLASS()
class CSCORE_API ACsManager_Sense : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	
	virtual void PostActorCreated() override;
	virtual void Destroyed() override;

	UPROPERTY()
	uint64 UniqueObjectId;

protected:

	TWeakObjectPtr<AActor> MyOwner;

	AActor* GetMyOwner();
	template<typename T>
	T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

public:

	void Init(AActor* InOwner);

	TMap<FECsSenseActorType, TMap<uint64, FCsSenseInfo>> SenseMap;
	TMap<uint8, FCsSenseInfo*> SenseTraceRequestMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	bool bRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float RadiusSq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float ViewMinDot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float ViewMinAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	float ViewMinRadians;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	TMap<FECsSenseActorType, float> TraceToActorIntervals;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	TMap<FECsSenseActorType, bool> bSeesAnyByRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	TMap<FECsSenseActorType, bool> bSeesAnyByDot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	TMap<FECsSenseActorType, bool> bSeesAnyBody;
	TMap<FECsSenseActorType, TCsBool_Ref> bSeesAndBodyHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	TMap<FECsSenseActorType, bool> bFirstSeesAnyBody;
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnbFirstSeesAnyBody, const FECsSenseActorType&, const bool&);
	FOnbFirstSeesAnyBody OnbFirstSeesAnyBody_Event;
	UPROPERTY(BlueprintAssignable, Category = "Sense")
	FBindableDynEvent_CsManagerSense_OnbFirstSeesAnyBody OnbFirstSeesAnyBody_ScriptEvent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	TMap<FECsSenseActorType, bool> bFirstUnSeesAnyBody;
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnbFirstUnSeesAnyBody, const FECsSenseActorType&, const bool&);
	FOnbFirstUnSeesAnyBody OnbFirstUnSeesAnyBody_Event;
	UPROPERTY(BlueprintAssignable, Category = "Sense")
	FBindableDynEvent_CsManagerSense_OnbFirstUnSeesAnyBody OnbFirstUnSeesAnyBody_ScriptEvent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	TMap<FECsSenseActorType, float> SeesAnyBodyTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sense")
	TMap<FECsSenseActorType, float> NotSeesAnyBodyTime;

// Debug
#pragma region
public:

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	bool bDrawRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	bool bDrawAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	bool bLogSeesActorByDot;
#endif // #if WITH_EDITORONLY_DATA

#if !UE_BUILD_SHIPPING

	void Log_bOnSeesActorByDot(const uint64& Observer, const uint64& Observee, const bool& Value);

#endif // #if !UE_BUILD_SHIPPING

#pragma endregion Debug

	const FECsSenseActorType& GetActorType(AActor* Actor);

	virtual FCsSenseInfo* Add(AActor* Actor, const TCsSenseTeam& Team);
	FCsSenseInfo* GetInfo(AActor* Actor);

	virtual bool CanSense(AActor* Actor);
	virtual bool IsSensing(AActor* Actor);

	virtual void OnTick(const float &DeltaSeconds);
	virtual void CheckMeToActorDot(FCsSenseInfo& Info);
	virtual void TraceViewToActorBody(FCsSenseInfo& Info);
	virtual void Async_TraceViewToActorBody_Response(const uint8 &RequestId, FCsTraceResponse* Response);
	virtual void TraceViewToActorHead(FCsSenseInfo& Info);
	virtual void Async_TraceViewToActorHead_Response(const uint8 &RequestId, FCsTraceResponse* Response);
};