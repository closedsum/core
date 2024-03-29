// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"

#include "CsSensedObject.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsSensedObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class ICsSensedObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FVector3f GetLocation() = 0;

	virtual FVector3f GetCustomLocation(const FName& InName) = 0;
};

// Delegates
#pragma region

	// Script
#pragma region

DECLARE_DELEGATE_RetVal_OneParam(FVector3f, FCsSensedObject_Script_GetLocation, UObject*);

DECLARE_DELEGATE_RetVal_TwoParams(FVector3f, FCsSensedObject_Script_GetCustomLocation, UObject*, const FName&);

#pragma endregion Script

#pragma endregion Delegates

// FCsSensedObject
#pragma region

struct CSSENSE_API FCsSensedObject : public TCsInterfaceObject<ICsSensedObject>
{
private:

	typedef TCsInterfaceObject<ICsSensedObject> Super;

public:

	static const FCsSensedObject Empty;

	// Script
#pragma region
public:

	FCsSensedObject_Script_GetLocation Script_GetLocation_Impl;
	FCsSensedObject_Script_GetCustomLocation Script_GetCustomLocation_Impl;

#pragma endregion Script

	FCsSensedObject() :
		Super(),
		Script_GetLocation_Impl(),
		Script_GetCustomLocation_Impl()
	{
	}

	virtual ~FCsSensedObject() {}

	// ICsSensedObject
#pragma region

	FVector3f GetLocation()
	{
		if (bScript)
			return Script_GetLocation_Impl.Execute(Object);
		return Interface->GetLocation();
	}

	FVector3f GetCustomLocation(const FName& InName)
	{
		if (bScript)
			return Script_GetCustomLocation_Impl.Execute(Object, InName);
		return Interface->GetCustomLocation(InName);
	}

#pragma endregion ICsSensedObject
};

#pragma endregion FCsSensedObject