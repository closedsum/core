// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsUpdate.h"
#include "CsCore.h"

UCsUpdate::UCsUpdate(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// FCsUpdate
#pragma region

const FCsUpdate FCsUpdate::Empty;

void FCsUpdate::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsUpdate
		{
			// Interface
			if (ICsUpdate* O = Cast<ICsUpdate>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsUpdate::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsUpdate:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsUpdate."), *(Object->GetName()));
			}
		}
	}
}

#pragma endregion FCsUpdate