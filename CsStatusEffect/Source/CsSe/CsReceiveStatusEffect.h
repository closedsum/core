// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
#include "CsReceiveStatusEffect.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSSE_API UCsReceiveStatusEffect : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

struct ICsStatusEffectEvent;

/**
*/
class CSSE_API ICsReceiveStatusEffect
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void ApplyStatusEffect(const ICsStatusEffectEvent* Event) = 0;
};

struct CSSE_API FCsReceiveStatusEffect : public TCsInterfaceObject<ICsReceiveStatusEffect>
{
private:

	typedef TCsInterfaceObject<ICsReceiveStatusEffect> Super;

public:

	static const FCsReceiveStatusEffect Empty;

// Script
#pragma region
public:

	// ICsReceiveStatusEffect
#pragma region
public:

	/**
	* Delegate type for
	*  The Object implements a script interface of type: ICsReceiveStatusEffect.
	*
	* @param Object			A Object of type: ICsReceiveStatusEffect.
	* @param Event
	*/
	DECLARE_DELEGATE_TwoParams(FScript_ApplyStatusEffect, UObject* /*Object*/, const ICsStatusEffectEvent* /*Event*/);

	/** Delegate for .
		 The Object implements a script interface of type: ICsReceiveStatusEffect. */
	FScript_ApplyStatusEffect Script_ApplyStatusEffect_Impl;

#pragma endregion ICsReceiveStatusEffect

#pragma endregion Script

	FCsReceiveStatusEffect() :
		Super(),
		Script_ApplyStatusEffect_Impl()
	{

	}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsReceiveStatusEffect
#pragma region
public:

	void ApplyStatusEffect(const ICsStatusEffectEvent* Event)
	{
		if (bScript)
			Script_ApplyStatusEffect_Impl.Execute(Object, Event);
		else
			Interface->ApplyStatusEffect(Event);
	}

#pragma endregion ICsReceiveStatusEffects
};