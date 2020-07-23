// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
#include "CsReceiveDamage.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsReceiveDamage : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

struct ICsDamageEvent;

/**
*/
class CSCORE_API ICsReceiveDamage
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Damage(const ICsDamageEvent* Event) = 0;
};

// FCsReceiveDamage
#pragma region

class ICsReceiveDamage;

struct CSCORE_API FCsReceiveDamage : public TCsInterfaceObject<ICsReceiveDamage>
{
private:

	typedef TCsInterfaceObject<ICsReceiveDamage> Super;

public:

	static const FCsReceiveDamage Empty;

// Script
#pragma region
public:

	// ICsReceiveDamage
#pragma region
public:

	/**
	* Delegate type for
	*  The Object implements a script interface of type: ICsReceiveDamage.
	*
	* @param Object		A Object of type: ICsReceiveDamage.
	* @param Event
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Damage, UObject* /*Object*/, const ICsDamageEvent* /*Event*/);

	/** Delegate for .
		 The Object implements a script interface of type: ICsReceiveDamage. */
	FScript_Damage Script_Damage_Impl;

#pragma endregion ICsReceiveDamage

#pragma endregion Script

	FCsReceiveDamage() :
		Super(),
		Script_Damage_Impl()
	{
	}

	// TCsInterfaceObject
#pragma region
public:

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsReceiveDamage
#pragma region
public:

	void Damage(const ICsDamageEvent* Event)
	{
		if (bScript)
			Script_Damage_Impl.Execute(Object, Event);
		else
			Interface->Damage(Event);
	}

#pragma endregion ICsReceiveDamage
};

#pragma endregion FCsReceiveDamage