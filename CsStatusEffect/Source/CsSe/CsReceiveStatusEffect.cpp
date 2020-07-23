// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsReceiveStatusEffect.h"
#include "CsSe.h"

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
		UClass* Class = Object->GetClass();

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

#pragma endregion FCsReceiveStatusEffect