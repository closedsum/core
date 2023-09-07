// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsReceiveDamage.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSDMG_API UCsReceiveDamage : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)

/**
*/
class CSDMG_API ICsReceiveDamage
{
	GENERATED_IINTERFACE_BODY()

#define EventType NCsDamage::NEvent::IEvent

public:

	virtual void Damage(const EventType* Event) = 0;

#undef EventType
};

// FCsReceiveDamage
#pragma region

class ICsReceiveDamage;

struct CSDMG_API FCsReceiveDamage : public TCsInterfaceObject<ICsReceiveDamage>
{
private:

	typedef TCsInterfaceObject<ICsReceiveDamage> Super;

public:

	static const FCsReceiveDamage Empty;

#define EventType NCsDamage::NEvent::IEvent

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
	DECLARE_DELEGATE_TwoParams(FScript_Damage, UObject* /*Object*/, const EventType* /*Event*/);

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

	void Damage(const EventType* Event)
	{
		if (bScript)
			Script_Damage_Impl.Execute(Object, Event);
		else
			Interface->Damage(Event);
	}

#pragma endregion ICsReceiveDamage

#undef EventType
};

#pragma endregion FCsReceiveDamage