// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Start/CsLibrary_StartPlay.h"
#include "CsCore.h"

// Start
#include "Start/CsStartPlay.h"

namespace NCsStartPlay
{
	void FLibrary::StartPlayChecked(const FString& Context, UObject* Object)
	{
		checkf(Object, TEXT("%s: Object is NULL."), *Context);

		ICsStartPlay* Interface = Cast<ICsStartPlay>(Object);

		checkf(Interface, TEXT("%s: Object: %s with Class: %s does NOT implement interface: ICsStartPlay."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName()));

		Interface->StartPlay();
	}
}