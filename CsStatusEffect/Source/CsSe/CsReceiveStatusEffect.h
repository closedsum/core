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

// FCsReceiveStatusEffect
#pragma region

class ICsGetManagerStatusEffect;
class UCsManager_StatusEffect;

struct CSSE_API FCsReceiveStatusEffect : public TCsInterfaceObject<ICsReceiveStatusEffect>
{
private:

	typedef TCsInterfaceObject<ICsReceiveStatusEffect> Super;

public:

	static const FCsReceiveStatusEffect Empty;

protected:

	ICsGetManagerStatusEffect* GetManagerStatusEffect;

	bool bScriptGetManagerStatusEffect;

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

	// ICsGetManagerStatusEffect
#pragma region
public:

	/**
	* Delegate type for
	*  The Object implements a script interface of type: ICsGetManagerStatusEffect.
	*
	* @param Object			A Object of type: ICsGetManagerStatusEffect.
	* return Manager
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UCsManager_StatusEffect* /*Manager*/, FScript_GetManager_StatusEffect, UObject* /*Object*/);

	/** Delegate for .
		 The Object implements a script interface of type: ICsReceiveStatusEffect. */
	FScript_GetManager_StatusEffect Script_GetManager_StatusEffect_Impl;

	/**
	* Delegate type for
	*  The Object implements a script interface of type: ICsGetManagerStatusEffect.
	*
	* @param Object			A Object of type: ICsGetManagerStatusEffect.
	* @oaran InManager
	*/
	DECLARE_DELEGATE_TwoParams(FScript_SetManager_StatusEffect, UObject* /*Object*/, UCsManager_StatusEffect* /*InManager*/);

	/** Delegate for .
		 The Object implements a script interface of type: ICsReceiveStatusEffect. */
	FScript_SetManager_StatusEffect Script_SetManager_StatusEffect_Impl;

#pragma endregion ICsGetManagerStatusEffect

#pragma endregion Script

	FCsReceiveStatusEffect() :
		Super(),
		GetManagerStatusEffect(nullptr),
		bScriptGetManagerStatusEffect(false),
		Script_ApplyStatusEffect_Impl(),
		Script_GetManager_StatusEffect_Impl(),
		Script_SetManager_StatusEffect_Impl()
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

#pragma endregion ICsReceiveStatusEffect

// ICsGetManagerStatusEffect
#pragma region
public:

	UCsManager_StatusEffect* GetManager_StatusEffect();

	void SetManager_StatusEffect(UCsManager_StatusEffect* InManager);

#pragma endregion ICsGetManagerStatusEffect

public:

	FORCEINLINE bool Implements_ICsGetManagerStatusEffect() const
	{
		return GetManagerStatusEffect != nullptr || bScriptGetManagerStatusEffect;
	}

	FORCEINLINE void SetScriptGetManagerStatusEffect()
	{
		bScriptGetManagerStatusEffect = true;
	}

	FORCEINLINE const bool& IsScriptGetManagerStatusEffect() const
	{
		return bScriptGetManagerStatusEffect;
	}

	FORCEINLINE ICsGetManagerStatusEffect* Get_GetManagerStatusEffect() const
	{
		return GetManagerStatusEffect;
	}

	FORCEINLINE void Set_GetManagerStatusEffect(ICsGetManagerStatusEffect* O)
	{
		GetManagerStatusEffect = O;
	}
};

#pragma endregion FCsReceiveStatusEffect