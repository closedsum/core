// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
#include "CsSpawner.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsSpawner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsSpawner;
class ICsSpawnedObject;

/**
*
*
* @param Spawner
* @param SpawnedObject
*/
DECLARE_DELEGATE_TwoParams(FCsSpawner_OnSpawn, ICsSpawner* /*Spawner*/, ICsSpawnedObject* /*SpawnedObject*/);

class CSCORE_API ICsSpawner
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual ICsSpawnedObject* Spawn() = 0;

	/**
	*
	*
	* return
	*/
	virtual FCsSpawner_OnSpawn& GetOnSpawn_Event() = 0;
};

// FCsSpawner
#pragma region

class ICsSpawnedObject;

struct CSCORE_API FCsSpawner : public TCsInterfaceObject<ICsSpawner>
{
private:

	typedef TCsInterfaceObject<ICsSpawner> Super;

public:

	static const FCsSpawner Empty;

// Script
#pragma region
public:

	/**
	* Delegate type for spawning an object that implements the interface of type: ICsSpawnedObject.
	*  The object implements a script interface of type: ICsSpawner.
	*
	* @param Object		An object of type: ICsSpawner.
	* return			Object that implements the interface: ICsSpawnedObject.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(ICsSpawnedObject* /*SpawnedObject*/, FScript_Spawn, UObject* /*Object*/);

	/** Delegate type for spawning an object that implements the interface of type: ICsSpawnedObject.
		  The object implements a script interface of type: ICsSpline. */
	FScript_Spawn Script_Spawn_Impl;


#pragma endregion Script

public:

	FCsSpawner() :
		Super(),
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

		Script_Spawn_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsSpawner
#pragma region
public:

	FORCEINLINE ICsSpawnedObject* Spawn()
	{
		if (bScript)
			return Script_Spawn_Impl.Execute(Object);
		return Interface->Spawn();
	}

#pragma endregion ICsSpawner
};

#pragma endregion FCsSpawner