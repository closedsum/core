// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Containers/CsInterfaceObject.h"

#include "CsUpdate.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSTIME_API UCsUpdate : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSTIME_API ICsUpdate
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Update(const FCsDeltaTime& DeltaTime) = 0;
};

// FCsUpdate
#pragma region

struct CSTIME_API FCsUpdate : public TCsInterfaceObject<ICsUpdate>
{
private:

	typedef TCsInterfaceObject<ICsUpdate> Super;

public:

	static const FCsUpdate Empty;

// Script
#pragma region
public:

	/**
	* Delegate type for updating.
	*  The object implements a script interface of type: ICsUpdate.
	*
	* @param Object		An object of type: ICsUpdate.
	* @param DeltaTime	Delta time since last call to Update.
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Update, UObject* /*Object*/, const FCsDeltaTime& /*DeltaTime*/);

	/** Delegate for updating. 
		  The object implements a script interface of type: ICsUpdate. */
	FScript_Update Script_Update_Impl;


#pragma endregion Script

public:

	FCsUpdate() :
		Super(),
		Script_Update_Impl()
	{
	}

	virtual ~FCsUpdate() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override 
	{
		Super::Reset();

		Script_Update_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsUpdate
#pragma region
public:

	FORCEINLINE void Update(const FCsDeltaTime& DeltaTime)
	{
		if (bScript)
			Script_Update_Impl.Execute(Object, DeltaTime);
		else
			Interface->Update(DeltaTime);
	}

#pragma endregion ICsUpdate
};

#pragma endregion FCsUpdate