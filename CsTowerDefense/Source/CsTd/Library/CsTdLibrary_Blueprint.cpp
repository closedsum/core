// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsTdLibrary_Blueprint.h"

UCsTdLibrary_Blueprint::UCsTdLibrary_Blueprint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// TSoftObjectPtr
#pragma region

	// Container
#pragma region

UObject* UCsTdLibrary_Blueprint::Conv_CsTdCreepRefContainerToInternal(const FCsTdCreepRefContainer& Container)
{
	return Container.Get();
}

UClass* UCsTdLibrary_Blueprint::Conv_CsTdCreepRefContainerToClass(const FCsTdCreepRefContainer& Container)
{
	return Container.GetClass();
}

TSubclassOf<UObject> UCsTdLibrary_Blueprint::Conv_CsTdCreepRefContainerToSubclassOf(const FCsTdCreepRefContainer& Container)
{
	return Container.GetSubclassOf();
}

#pragma endregion Container

#pragma endregion TSoftObjectPtr