// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsReceiveStatusEffect.h"
#include "CsSe.h"

// Managers
#include "Managers/StatusEffect/CsGetManagerStatusEffect.h"

UCsReceiveStatusEffect::UCsReceiveStatusEffect(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// FCsReceiveStatusEffect
#pragma region

const FCsReceiveStatusEffect FCsReceiveStatusEffect::Empty;

	// TCsInterfaceObject
#pragma region

void FCsReceiveStatusEffect::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsReceiveStatusEffect
		{
			// Interface
			if (ICsReceiveStatusEffect* O = Cast<ICsReceiveStatusEffect>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsReceiveStatusEffect::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsReceiveStatusEffect:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsReceiveStatusEffect."), *(Object->GetName()));
			}
		}
	}
}

void FCsReceiveStatusEffect::Reset()
{
	Super::Reset();

	Script_ApplyStatusEffect_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

// ICsGetManagerStatusEffect
#pragma region

UCsManager_StatusEffect* FCsReceiveStatusEffect::GetManager_StatusEffect()
{
	if (bScriptGetManagerStatusEffect)
		return Script_GetManager_StatusEffect_Impl.Execute(Object);
	return GetManagerStatusEffect->GetManager_StatusEffect();
}

void FCsReceiveStatusEffect::SetManager_StatusEffect(UCsManager_StatusEffect* InManager)
{
	if (bScriptGetManagerStatusEffect)
		Script_SetManager_StatusEffect_Impl.Execute(Object, InManager);
	else
		GetManagerStatusEffect->SetManager_StatusEffect(InManager);
}

#pragma endregion ICsGetManagerStatusEffect

#pragma endregion FCsReceiveStatusEffect