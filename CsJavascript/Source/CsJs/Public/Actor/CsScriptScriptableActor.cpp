// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Actor/CsScriptScriptableActor.h"
#include "CsJs.h"

UCsScriptScriptableActor::UCsScriptScriptableActor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ICsScriptableActor
#pragma region

const FCsScriptableActorInfo& ICsScriptScriptableActor::GetScriptableActorInfo() const
{
	static FCsScriptableActorInfo Info;
	ICsScriptScriptableActor::Execute_Script_GetScriptableActorInfo(_getUObject(), Info);
	return Info;
}

#pragma endregion ICsScriptableActor
