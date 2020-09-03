// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActor.h"
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorUserWidget.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
class UUserWidget;
struct ICsPayload_UserWidget;

/**
*/
struct CSUI_API FCsPayload_WidgetActorImpl final : public ICsPayload_PooledObject,
												   public ICsPayload_WidgetActor,
												   public ICsPayload_WidgetActorUserWidget
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

	bool bAllocated;

public:

	// ICsPayload_PooledObject

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;
	
	FCsTime Time;

	// ICsPayload_WidgetActor

	UUserWidget* UserWidget;

	ECsWidgetActorDeallocateMethod DeallocateMethod;

	float LifeTime;
	
	ECsAttachmentTransformRules AttachmentTransformRules;

	FName Bone;

	int32 TransformRules;

	FTransform Transform;

	// ICsPayload_WidgetActorUserWidget

	FECsUserWidgetPooled UserWidgetPooledType;

	ICsPayload_UserWidget* UserWidgetPayload;

public:

	FCsPayload_WidgetActorImpl();
	~FCsPayload_WidgetActorImpl();

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

// ICsPayload_WidgetActor
#pragma region
public:

	FORCEINLINE UUserWidget* GetUserWidget() const
	{
		return UserWidget;
	}

	FORCEINLINE const ECsWidgetActorDeallocateMethod& GetDeallocateMethod() const
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

#pragma endregion ICsPayload_WidgetActor

// ICsPayload_WidgetActorUserWidget
#pragma region
public:

	FORCEINLINE const FECsUserWidgetPooled& GetUserWidgetPooledType() const
	{
		return UserWidgetPooledType;
	}

	FORCEINLINE ICsPayload_UserWidget* GetUserWidgetPayload() const
	{
		return UserWidgetPayload;
	}

#pragma endregion ICsPayload_WidgetActorUserWidget
};