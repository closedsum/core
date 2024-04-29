// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Container
#include "Containers/CsInterfaceObject.h"
// Types
#include "CsMacro_Namespace.h"

#include "ICsSpawner.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSSPAWNER_API UCsSpawner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsSpawner;

// NCsSpawner::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, IParams)

namespace NCsSpawner
{
	/**
	* OnStart
	*
	* @param Spawner
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStart, ICsSpawner* /*Spawner*/);
	/**
	* OnStop
	*
	* @param Spawner
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStop, ICsSpawner* /*Spawner*/);
	/**
	* OnSpawn
	*
	* @param Spawner
	* @param SpawnedObject
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSpawn, ICsSpawner* /*Spawner*/);
	/**
	* OnSpawnObject
	*
	* @param Spawner
	* @param SpawnedObject
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawnObject, ICsSpawner* /*Spawner*/, UObject* /*SpawnedObject*/);
	/**
	* OnSpawnObjects
	*
	* @param Spawner
	* @param SpawnedObjects
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawnObjects, ICsSpawner* /*Spawner*/, const TArray<UObject*>& /*SpawnedObjects*/);
	/**
	* OnFinish
	*
	* @param Spawner
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnFinish, ICsSpawner* /*Spawner*/);
}

class CSSPAWNER_API ICsSpawner
{
	GENERATED_IINTERFACE_BODY()

public:

#define ParamsType NCsSpawner::NParams::IParams

	/**
	*/
	virtual const ParamsType* GetParams() const = 0;

	/**
	*
	*/
	virtual void Start() = 0;

	/**
	*
	*
	* return
	*/
	virtual NCsSpawner::FOnStart& GetOnStart_Event() = 0;

	/**
	*
	*/
	virtual void Stop() = 0;

	/**
	*
	*
	* return
	*/
	virtual NCsSpawner::FOnStop& GetOnStop_Event() = 0;

	/**
	*
	*/
	virtual void Spawn() = 0;

	/**
	*
	*
	* return
	*/
	virtual NCsSpawner::FOnSpawn& GetOnSpawn_Event() = 0;

	/**
	*
	*
	* return
	*/
	virtual NCsSpawner::FOnSpawnObject& GetOnSpawnObject_Event() = 0;

	/**
	*
	*
	* return
	*/
	virtual NCsSpawner::FOnSpawnObjects& GetOnSpawnObjects_Event() = 0;

	/**
	*
	*
	* return
	*/
	virtual NCsSpawner::FOnFinish& GetOnFinish_Event() = 0;

#undef ParamsType
};

// FCsSpawner
#pragma region

class UObject;

struct CSSPAWNER_API FCsSpawner : public TCsInterfaceObject<ICsSpawner>
{
private:

	typedef TCsInterfaceObject<ICsSpawner> Super;

public:

	static const FCsSpawner Empty;

// Script
#pragma region
public:

	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*SpawnedObject*/, FScript_Start, UObject* /*Object*/);

	FScript_Start Script_Start_Impl;

	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*SpawnedObject*/, FScript_Stop, UObject* /*Object*/);

	FScript_Stop Script_Stop_Impl;

	/**
	* Delegate type for an object spawning a UObject.
	*  The object implements a script interface of type: ICsSpawner.
	*
	* @param Object		An object of type: ICsSpawner.
	*/
	DECLARE_DELEGATE_OneParam(FScript_Spawn, UObject* /*Object*/);

	/** Delegate type for an object spawning a UObject.
		  The object implements a script interface of type: ICsSpawner. */
	FScript_Spawn Script_Spawn_Impl;

	//NCsSpawner::FOnSpawn OnSpawn_Event;

#pragma endregion Script

public:

	FCsSpawner() :
		Super(),
		Script_Start_Impl(),
		Script_Stop_Impl(),
		Script_Spawn_Impl()
	{
	}

	virtual ~FCsSpawner() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override 
	{
		Super::Reset();
	
		Script_Start_Impl.Unbind();
		Script_Stop_Impl.Unbind();
		Script_Spawn_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsSpawner
#pragma region
public:

	FORCEINLINE void Start()
	{
		if (bScript)
			Script_Start_Impl.Execute(Object);
		else
			Interface->Start();
	}

	FORCEINLINE NCsSpawner::FOnStart& GetOnStart_Event() { return Interface->GetOnStart_Event(); }

	FORCEINLINE void Stop()
	{
		if (bScript)
			Script_Stop_Impl.Execute(Object);
		else
			Interface->Stop();
	}

	FORCEINLINE NCsSpawner::FOnStop& GetOnStop_Event() { return Interface->GetOnStop_Event(); }

	FORCEINLINE void Spawn()
	{
		if (bScript)
			Script_Spawn_Impl.Execute(Object);
		else
			Interface->Spawn();
	}

	FORCEINLINE NCsSpawner::FOnSpawn& GetOnSpawn_Event() { return Interface->GetOnSpawn_Event(); }

#pragma endregion ICsSpawner
};

#pragma endregion FCsSpawner