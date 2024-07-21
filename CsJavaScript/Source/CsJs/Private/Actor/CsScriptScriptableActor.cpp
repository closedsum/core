// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Actor/CsScriptScriptableActor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptScriptableActor)

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
