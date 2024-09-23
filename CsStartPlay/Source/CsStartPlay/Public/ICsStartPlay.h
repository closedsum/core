// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Containers/CsInterfaceObject.h"

#include "ICsStartPlay.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSSTARTPLAY_API UCsStartPlay : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class CSSTARTPLAY_API ICsStartPlay
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void StartPlay() = 0;

	virtual bool HasStartedPlay() const = 0;
};

// FCsStartPlay
#pragma region

struct CSSTARTPLAY_API FCsStartPlay : public TCsInterfaceObject<ICsStartPlay>
{
private:

	typedef TCsInterfaceObject<ICsStartPlay> Super;

public:

	static const FCsStartPlay Empty;

// Script
#pragma region
public:

	/**
	* Delegate type for.
	*  The object implements a script interface of type: ICsStartPlay.
	*
	* @param Object		An object of type: ICsStartPlay.
	*/
	DECLARE_DELEGATE_OneParam(FScript_StartPlay, UObject* /*Object*/);

	/** Delegate for. 
		  The object implements a script interface of type: ICsStartPlay. */
	FScript_StartPlay Script_StartPlay_Impl;

	/**
	* Delegate type for.
	*  The object implements a script interface of type: ICsStartPlay.
	*
	* @param Object		An object of type: ICsStartPlay.
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(bool, FScript_HasStartedPlay, UObject* /*Object*/);

	/** Delegate for. 
		  The object implements a script interface of type: ICsStartPlay. */
	FScript_HasStartedPlay Script_HasStartedPlay_Impl;

#pragma endregion Script

public:

	FCsStartPlay();

	virtual ~FCsStartPlay() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsStartPlay
#pragma region
public:

	FORCEINLINE void StartPlay()
	{
		if (bScript)
			Script_StartPlay_Impl.Execute(Object);
		else
			Interface->StartPlay();
	}

	FORCEINLINE bool HasStartedPlay()
	{
		if (bScript)
			return Script_HasStartedPlay_Impl.Execute(Object);
		return Interface->HasStartedPlay();
	}

#pragma endregion ICsStartPlay
};

#pragma endregion FCsStartPlay