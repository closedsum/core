// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"

// FCsSkeletalMeshActorPooled
#pragma region

class ICsSkeletalMeshActor;

struct CSCORE_API FCsSkeletalMeshActorPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsSkeletalMeshActorPooled Empty;

protected:

	/** Reference to interface of type: ICsSkeletalMeshActor. */
	ICsSkeletalMeshActor* SkeletalMeshActor;

	/** Does the Sound implement a script interface of type: ICsSkeletalMeshActor. */
	bool bScriptSkeletalMeshActor;

// Script
#pragma region
public:

	// ICsSkeletalMeshActor
#pragma region
public:

	/**
	* Delegate type for getting the pooled SkeletalMeshComponent.
	*  The Object implements a script interface of type: ICsSkeletalMeshActor.
	*
	* @param Object					An object of type: ICsSkeletalMeshActor.
	* return SkeletalMeshComponent	Component of type USkeletalMeshComponent.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(USkeletalMeshComponent* /*SkeletalMeshComponent*/, FScript_GetMeshComponent, UObject* /*Object*/);

	/** Delegate for getting the pooled SkeletalMeshComponent. 
		 The Object implements a script interface of type: ICsSkeletalMeshActor. */
	FScript_GetMeshComponent Script_GetMeshComponent_Impl;

#pragma endregion ICsSkeletalMeshActor

#pragma endregion Script

public:

	FCsSkeletalMeshActorPooled();

	virtual ~FCsSkeletalMeshActorPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsSkeletalMeshActor
#pragma region
public:

	USkeletalMeshComponent* GetMeshComponent() const;

#pragma endregion ICsSkeletalMeshActor

	FORCEINLINE void SetScriptSkeletalMeshActor()
	{
		bScriptSkeletalMeshActor = true;
	}

	FORCEINLINE const bool& IsScriptSkeletalMeshActor() const
	{
		return bScriptSkeletalMeshActor;
	}

	FORCEINLINE ICsSkeletalMeshActor* GetSkeletalMeshActor() const
	{
		return SkeletalMeshActor;
	}

	FORCEINLINE void SetSkeletalMeshActorPooled(ICsSkeletalMeshActor* InSkeletalMeshActor)
	{
		SkeletalMeshActor = InSkeletalMeshActor;
	}

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);
};

#pragma endregion FCsSkeletalMeshActorPooled