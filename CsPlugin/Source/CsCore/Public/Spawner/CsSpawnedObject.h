// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
#include "CsSpawnedObject.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsSpawnedObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class CSCORE_API ICsSpawnedObject
{
	GENERATED_IINTERFACE_BODY()

public:
};

// FCsSpawnedObject
#pragma region

struct CSCORE_API FCsSpawnedObject : public TCsInterfaceObject<ICsSpawnedObject>
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