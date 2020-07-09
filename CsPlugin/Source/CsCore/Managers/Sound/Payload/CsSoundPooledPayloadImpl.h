// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
#include "Managers/Sound/Payload/CsSoundPooledPayload.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
class USoundBase;

struct CSCORE_API FCsSoundPooledPayloadImpl final : public ICsPooledObjectPayload,
												    public ICsSoundPooledPayload
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

	bool bAllocated;

public:

	// ICsPooledObjectPayload

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;
	
	FCsTime Time;

	// ICsSoundPooledPayload

	USoundBase* Sound;

	USoundAttenuation* SoundAttenuation;

	ECsSoundDeallocateMethod DeallocateMethod;

	float LifeTime;
	
	ECsAttachmentTransformRules AttachmentTransformRules;

	FName Bone;

	int32 TransformRules;

	FTransform Transform;

public:

	FCsSoundPooledPayloadImpl();
	~FCsSoundPooledPayloadImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsPooledObjectPayload
#pragma region
public:

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator;
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner;
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent;
	}

	FORCEINLINE const FCsTime& GetTime() const
	{
		return Time;
	}

	FORCEINLINE void Allocate()
	{
		bAllocated = true;
	}

	void Reset();

#pragma endregion ICsPooledObjectPayload

public:

	template<typename T>
	FORCEINLINE T* GetInstigator() const
	{
		return Cast<T>(GetInstigator());
	}

	template<typename T>
	FORCEINLINE T* GetOwner() const
	{
		return Cast<T>(GetOwner());
	}

	template<typename T>
	FORCEINLINE T* GetParent() const
	{
		return Cast<T>(GetParent());
	}

// ICsSoundPooledPayload
#pragma region
public:

	FORCEINLINE USoundBase* GetSound() const 
	{
		return Sound;
	}

	FORCEINLINE USoundAttenuation* GetSoundAttenuation() const
	{
		return SoundAttenuation;
	}

	FORCEINLINE const ECsSoundDeallocateMethod& GetDeallocateMethod() const
	{
		return DeallocateMethod;
	}

	FORCEINLINE const float& GetLifeTime() const
	{
		return LifeTime;
	}

	FORCEINLINE const ECsAttachmentTransformRules& GetAttachmentTransformRule() const
	{
		return AttachmentTransformRules;
	}

	FORCEINLINE const FName& GetBone() const
	{
		return Bone;
	}

	FORCEINLINE const int32& GetTransformRules() const
	{
		return TransformRules;
	}

	FORCEINLINE const FTransform& GetTransform() const
	{
		return Transform;
	}

#pragma endregion ICsSoundPooledPayload
};