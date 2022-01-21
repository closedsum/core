// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsReceiveDamage.h"
#include "CsDmg.h"

UCsReceiveDamage::UCsReceiveDamage(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// FCsReceiveDamage
#pragma region

const FCsReceiveDamage FCsReceiveDamage::Empty;

// TCsInterfaceObject
#pragma region

void FCsReceiveDamage::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsReceiveStatusEffect
		{
			// Interface
			if (ICsReceiveDamage* O = Cast<ICsReceiveDamage>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsReceiveDamage::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsReceiveDamage:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsReceiveDamage."), *(Object->GetName()));
			}
		}
	}
}

void FCsReceiveDamage::Reset()
{
	Super::Reset();

	Script_Damage_Impl.Unbind();
}

#pragma endregion TCsInterfaceObject

#pragma endregion FCsReceiveDamage