// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"

#include "CsSpawnedObject.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsSpawnedObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class CSSPAWNER_API ICsSpawnedObject
{
	GENERATED_IINTERFACE_BODY()

public:
};

// FCsSpawnedObject
#pragma region

struct CSSPAWNER_API FCsSpawnedObject : public TCsInterfaceObject<ICsSpawnedObject>
{
private:

	typedef TCsInterfaceObject<ICsSpawnedObject> Super;

public:

	static const FCsSpawnedObject Empty;

// Script
#pragma region
public:

#pragma endregion Script

public:

	FCsSpawnedObject() :
		Super()
	{
	}

	virtual ~FCsSpawnedObject() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override 
	{
		Super::Reset();
	}

#pragma endregion TCsInterfaceObject

// ICsSpline
#pragma region
public:

#pragma endregion ICsSpline
};

#pragma endregion FCsSpawnedObject