// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Script/CsScriptLibrary_StaticMeshActor.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibraryStaticMeshActor
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsStaticMeshActor = TEXT("FECsStaticMeshActor");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_StaticMeshActor::UCsScriptLibrary_StaticMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

FECsStaticMeshActor UCsScriptLibrary_StaticMeshActor::Get(const FString& Name)
{
	using namespace NCsScriptLibraryStaticMeshActor::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EMCsStaticMeshActor, FECsStaticMeshActor>(Context, Str::FECsStaticMeshActor, Name);
}

FECsStaticMeshActor UCsScriptLibrary_StaticMeshActor::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryStaticMeshActor::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EMCsStaticMeshActor, FECsStaticMeshActor>(Context, Str::FECsStaticMeshActor, Index);
}

FString UCsScriptLibrary_StaticMeshActor::ToString(const FECsStaticMeshActor& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_StaticMeshActor::GetCount()
{
	return EMCsStaticMeshActor::Get().Num();
}

void UCsScriptLibrary_StaticMeshActor::GetAll(TArray<FECsStaticMeshActor>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EMCsStaticMeshActor, FECsStaticMeshActor>(OutTypes);
}

FECsStaticMeshActor UCsScriptLibrary_StaticMeshActor::GetMax()
{
	return EMCsStaticMeshActor::Get().GetMAX();
}

bool UCsScriptLibrary_StaticMeshActor::EqualEqual(const FECsStaticMeshActor& A, const FECsStaticMeshActor& B)
{
	return A == B;
}

#pragma endregion Enum