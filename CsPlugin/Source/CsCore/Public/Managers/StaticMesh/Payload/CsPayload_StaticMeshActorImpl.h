// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActor.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
class UStaticMesh;

struct CSCORE_API FCsPayload_StaticMeshActorImpl final : public ICsPayload_PooledObject,
														 public ICsPayload_StaticMeshActor
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

	// ICsPayload_StaticMeshActor

	UStaticMesh* Mesh;

	ECsStaticMeshActorDeallocateMethod DeallocateMethod;

	float LifeTime;
	
	ECsAttachmentTransformRules AttachmentTransformRules;

	FName Bone;

	int32 TransformRules;

	FTransform Transform;

public:

	FCsPayload_StaticMeshActorImpl();
	~FCsPayload_StaticMeshActorImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsPayload_PooledObject
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

#pragma endregion ICsPayload_PooledObject

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

// ICsPayload_StaticMeshActor
#pragma region
public:

	FORCEINLINE UStaticMesh* GetStaticMesh() const 
	{
		return Mesh;
	}

	FORCEINLINE const ECsStaticMeshActorDeallocateMethod& GetDeallocateMethod() const
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

#pragma endregion ICsPayload_StaticMeshActor
};