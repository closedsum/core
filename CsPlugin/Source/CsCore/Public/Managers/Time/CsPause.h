// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Types
#include "Containers/CsInterfaceObject.h"

#include "CsPause.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsPause : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class CSCORE_API ICsPause
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Pause(bool bPaused) = 0;
};

// FCsPause
#pragma region

struct CSCORE_API FCsPause : public TCsInterfaceObject<ICsPause>
{
private:

	typedef TCsInterfaceObject<ICsPause> Super;

public:

	static const FCsPause Empty;

// Script
#pragma region
public:

	/**
	* Delegate type for pausing.
	*  The object implements a script interface of type: ICsPause.
	*
	* @param Object		An object of type: ICsPause.
	* @param bPaused	Set whether to pause or un-pause.
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Pause, UObject* /*Object*/, bool /*bPaused*/);

	/** Delegate for pausing. 
		  The object implements a script interface of type: ICsPause. */
	FScript_Pause Script_Pause_Impl;


#pragma endregion Script

public:

	FCsPause() :
		Super(),
		Script_Pause_Impl()
	{
	}

	virtual ~FCsPause() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override 
	{
		Super::Reset();

		Script_Pause_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsPause
#pragma region
public:

	FORCEINLINE void Pause(bool bPaused)
	{
		if (bScript)
			Script_Pause_Impl.Execute(Object, bPaused);
		else
			Interface->Pause(bPaused);
	}

#pragma endregion ICsPause
};

#pragma endregion FCsPause