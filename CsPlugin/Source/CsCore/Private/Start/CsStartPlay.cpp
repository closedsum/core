// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Start/CsStartPlay.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsStartPlay)

UCsStartPlay::UCsStartPlay(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// FCsStartPlay
#pragma region

const FCsStartPlay FCsStartPlay::Empty;

FCsStartPlay::FCsStartPlay() :
	Super(),
	Script_StartPlay_Impl(),
	Script_HasStartedPlay_Impl()
{
}

void FCsStartPlay::SetObject(UObject* InObject)
{
	Super::SetObject(InObject);

	if (Object)
	{
		// ICsStartPlay
		{
			// Interface
			if (ICsStartPlay* O = Cast<ICsStartPlay>(Object))
			{
				SetInterface(O);
			}
			// Script Interface
			else
			if (Class->ImplementsInterface(UCsStartPlay::StaticClass()))
			{
				SetScript();
			}
			else
			{
				checkf(false, TEXT("FCsStartPlay:SetObject: Object: %s with Class: %s does NOT implement the interface: ICsStartPlay."), *(Object->GetName()));
			}
		}
	}
}

void FCsStartPlay::Reset()
{
	Super::Reset();

	Script_StartPlay_Impl.Unbind();
	Script_HasStartedPlay_Impl.Unbind();
}

#pragma endregion FCsStartPlay