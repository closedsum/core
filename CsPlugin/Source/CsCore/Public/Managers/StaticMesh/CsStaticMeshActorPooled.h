// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"

// FCsStaticMeshActorPooled
#pragma region

class ICsStaticMeshActor;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

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

	/**
	* Delegate type for getting the Material Instance Dynamic(s) or MIDs
	* associated with the Static Mesh on GetMeshComponent() (GetMeshComponent()->GetStaticMesh()).
	*  The Object implements a script interface of type: ICsStaticMeshActor.
	*
	* @param Object					An object of type: ICsStaticMeshActor.
	* return MIDs					Array of Material Instance Dynamic.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(const TArray<UMaterialInstanceDynamic*>& /*MIDs*/, FScript_GetMIDs, UObject* /*Object*/);

	/** Delegate for getting the Material Instance Dynamic(s) or MIDs
		associated with the Static Mesh on GetMeshComponent() (GetMeshComponent()->GetStaticMesh()).
		 The Object implements a script interface of type: ICsStaticMeshActor. */
	FScript_GetMIDs Script_GetMIDs_Impl;

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

	const TArray<UMaterialInstanceDynamic*>& GetMIDs() const;

#pragma endregion ICsStaticMeshActor

	FORCEINLINE void SetScriptStaticMeshActor() { bScriptStaticMeshActor = true; }
	FORCEINLINE const bool& IsScriptStaticMeshActor() const { return bScriptStaticMeshActor; }
	FORCEINLINE ICsStaticMeshActor* GetStaticMeshActor() const { return StaticMeshActor; }
	FORCEINLINE void SetStaticMeshActorPooled(ICsStaticMeshActor* InStaticMeshActor) { StaticMeshActor = InStaticMeshActor; }

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);
};

#pragma endregion FCsStaticMeshActorPooled