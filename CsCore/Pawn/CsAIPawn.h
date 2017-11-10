// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Pawn/CsPawn.h"
#include "Types/CsTypes.h"
#include "CsAIPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsAIPawn_Override_OnTick, const int32&, Index, const float&, DeltaSeconds);

USTRUCT(BlueprintType)
struct FCsAIPawnCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<class ACsAIPawn> Pawn;

	// TODO: LifeTime

	FCsAIPawnCache()
	{
		Reset();
	}

	~FCsAIPawnCache(){}

	void Set(const uint16 &InIndex, ACsAIPawn* InPawn)
	{
		Index = InIndex;
		Pawn  = InPawn;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
		Owner = InOwner;
		Parent = InParent;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;

		if (InObject && OnDeAllocate)
		{
			DelegateInvoker = (UObject*)InObject;
#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.AddUObject(InObject, OnDeAllocate);
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.AddUObject(InObject, OnDeAllocate);
		}
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
	{
		Init(InActiveIndex, InTime, InRealTime, InFrame, nullptr, nullptr, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
	{
		ActiveIndex = InActiveIndex;
		ActiveIndex_Script = (int32)ActiveIndex;
		Owner = InOwner;
		Parent = InParent;
		Time = InTime;
		RealTime = InRealTime;
		Frame = InFrame;
	}

	void Init(const uint16& InActiveIndex, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, InTime, InRealTime, InFrame, nullptr, nullptr);
	}

	virtual void Reset() override
	{
		Super::Reset();

		Pawn.Reset();
		Pawn = nullptr;
	}

	ACsAIPawn* GetPawn() { return Pawn.IsValid() ? Pawn.Get() : nullptr; }
};

UCLASS()
class CSCORE_API ACsAIPawn : public ACsPawn
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	int32 PoolIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	bool IsAllocated;

	TCsAIType Type;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AI")
	uint8 Type_Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	struct FCsAIPawnCache Cache;

	void Init(const int32 &Index, const TCsAIType &InType);

	virtual void OnCreatePool();
	virtual void OnPostCreatePool();

	template<typename T>
	void Allocate(const uint16 &ActiveIndex, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	template<typename T>
	void Allocate(const uint16 &ActiveIndex, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&));

	void Allocate(const uint16 &ActiveIndex, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent);
	void Allocate(const uint16 &ActiveIndex, const float &Time, const float &RealTime, const uint64 &Frame);

	virtual void Allocate_Internal();

	virtual void DeAllocate();

	UPROPERTY(BlueprintAssignable, Category = "AI")
	FBindableDynEvent_CsAIPawn_Override_OnTick Override_OnTick_ScriptEvent;

	virtual void OnTick_CheckCVars(const float &DeltaSeconds);
};