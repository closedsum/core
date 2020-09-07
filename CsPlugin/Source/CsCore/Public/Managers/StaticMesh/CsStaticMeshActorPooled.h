// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"

// FCsStaticMeshActorPooled
#pragma region

class ICsStaticMeshActor;

struct CSCORE_API FCsStaticMeshActorPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsStaticMeshActorPooled Empty;

protected:

	/** Reference to interface of type: ICsStaticMeshActor. */
	ICsStaticMeshActor* StaticMeshActor;

	/** Does the Sound implement a script interface of type: ICsStaticMeshActor. */
	bool bScriptStaticMeshActor;

// Script
#pragma region
public:

	// ICsStaticMeshActor
#pragma region
public:

	/**
	* Delegate type for getting the pooled StaticMeshComponent.
	*  The Object implements a script interface of type: ICsStaticMeshActor.
	*
	* @param Object					An object of type: ICsStaticMeshActor.
	* return StaticMeshComponent	Component of type UStaticMeshComponent.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UStaticMeshComponent* /*StaticMeshComponent*/, FScript_GetMeshComponent, UObject* /*Object*/);

	/** Delegate for getting the pooled StaticMeshComponent. 
		 The Object implements a script interface of type: ICsStaticMeshActor. */
	FScript_GetMeshComponent Script_GetMeshComponent_Impl;

#pragma endregion ICsStaticMeshActor

#pragma endregion Script

public:

	FCsStaticMeshActorPooled();

	virtual ~FCsStaticMeshActorPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsStaticMeshActor
#pragma region
public:

	UStaticMeshComponent* GetMeshComponent() const;

#pragma endregion ICsStaticMeshActor

	FORCEINLINE void SetScriptStaticMeshActor()
	{
		bScriptStaticMeshActor = true;
	}

	FORCEINLINE const bool& IsScriptStaticMeshActor() const
	{
		return bScriptStaticMeshActor;
	}

	FORCEINLINE ICsStaticMeshActor* GetStaticMeshActor() const
	{
		return StaticMeshActor;
	}

	FORCEINLINE void SetStaticMeshActorPooled(ICsStaticMeshActor* InStaticMeshActor)
	{
		StaticMeshActor = InStaticMeshActor;
	}

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);
};

#pragma endregion FCsStaticMeshActorPooled