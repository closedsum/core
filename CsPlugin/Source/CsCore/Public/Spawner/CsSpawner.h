// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
#include "CsSpawner.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsSpawner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsSpawner;

/**
* OnStart
*
* @param Spawner
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FCsSpawner_OnStart, ICsSpawner* /*Spawner*/);
/**
* OnStop
*
* @param Spawner
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FCsSpawner_OnStop, ICsSpawner* /*Spawner*/);
/**
* OnSpawn
*
* @param Spawner
* @param SpawnedObject
*/
DECLARE_MULTICAST_DELEGATE_TwoParams(FCsSpawner_OnSpawn, ICsSpawner* /*Spawner*/, UObject* /*SpawnedObject*/);

class CSCORE_API ICsSpawner
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*/
	virtual void Start() = 0;

	/**
	*
	*
	* return
	*/
	virtual FCsSpawner_OnStart& GetOnStart_Event() = 0;

	/**
	*
	*/
	virtual void Stop() = 0;

	/**
	*
	*
	* return
	*/
	virtual FCsSpawner_OnStop& GetOnStop_Event() = 0;

	/**
	*
	*
	* return
	*/
	virtual UObject* Spawn() = 0;

	/**
	*
	*
	* return
	*/
	virtual FCsSpawner_OnSpawn& GetOnSpawn_Event() = 0;
};

// FCsSpawner
#pragma region

class UObject;

struct CSCORE_API FCsSpawner : public TCsInterfaceObject<ICsSpawner>
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
	* return			UObject.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*SpawnedObject*/, FScript_Spawn, UObject* /*Object*/);

	/** Delegate type for an object spawning a UObject.
		  The object implements a script interface of type: ICsSpawner. */
	FScript_Spawn Script_Spawn_Impl;

	//FCsSpawner_OnSpawn OnSpawn_Event;

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

	FORCEINLINE FCsSpawner_OnStart& GetOnStart_Event()
	{
		return Interface->GetOnStart_Event();
	}

	FORCEINLINE void Stop()
	{
		if (bScript)
			Script_Stop_Impl.Execute(Object);
		else
			Interface->Stop();
	}

	FORCEINLINE FCsSpawner_OnStop& GetOnStop_Event()
	{
		return Interface->GetOnStop_Event();
	}

	FORCEINLINE UObject* Spawn()
	{
		if (bScript)
			return Script_Spawn_Impl.Execute(Object);
		return Interface->Spawn();
	}

	FORCEINLINE FCsSpawner_OnSpawn& GetOnSpawn_Event() 
	{
		return Interface->GetOnSpawn_Event();
	}

#pragma endregion ICsSpawner
};

#pragma endregion FCsSpawner