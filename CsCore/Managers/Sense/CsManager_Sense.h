// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Sense.h"
#include "Types/CsTypes_Trace.h"
#include "CsManager_Sense.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	TMap<FECsSenseActorType, float> TraceToActorIntervals;

	virtual void OnTick(const float &DeltaSeconds);
	virtual void Sense_CheckMeToActorDot(FCsSenseInfo& Info);
	virtual void Sense_TraceViewToActorBody(FCsSenseInfo& Info);
	virtual void Async_Sense_TraceViewToActorBody_Response(const uint8 &RequestId, FCsTraceResponse* Response);
	virtual void Sense_TraceViewToActorHead(FCsSenseInfo& Info);
	virtual void Async_Sense_TraceViewToActorHead_Response(const uint8 &RequestId, FCsTraceResponse* Response);
};