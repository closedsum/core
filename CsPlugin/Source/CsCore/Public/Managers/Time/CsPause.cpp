// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsPause.h"
#include "CsCore.h"

UCsPause::UCsPause(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// FCsPause
#pragma region

const FCsPause FCsPause::Empty;

void FCsPause::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsUpdate
		{
			// Interface
			if (ICsPause* O = Cast<ICsPause>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsPause::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsPause:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsPause."), *(Object->GetName()));
			}
		}
	}
}

#pragma endregion FCsPause