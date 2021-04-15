// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Script/CsScriptLibrary_SkeletalMeshActor.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cached
#pragma region

namespace NCsScriptLibrarySkeletalMeshActor
{
	namespace NCached
	{
		namespace Str
		{
			const FString FECsSkeletalMeshActor = TEXT("FECsSkeletalMeshActor");
			const FString ECsSkeletalMeshActor_Get = TEXT("ECsSkeletalMeshActor_Get");
			const FString ECsSkeletalMeshActor_GetByIndex = TEXT("ECsSkeletalMeshActor_GetByIndex");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SkeletalMeshActor, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SkeletalMeshActor, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SkeletalMeshActor, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_SkeletalMeshActor::UCsScriptLibrary_SkeletalMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

FECsSkeletalMeshActor UCsScriptLibrary_SkeletalMeshActor::ECsSkeletalMeshActor_Get(const FString& Name)
{
	using namespace NCsScriptLibrarySkeletalMeshActor::NCached;

	const FString& Context = Str::ECsSkeletalMeshActor_Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>(Context, Str::FECsSkeletalMeshActor, Name);
}

FECsSkeletalMeshActor UCsScriptLibrary_SkeletalMeshActor::ECsSkeletalMeshActor_GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibrarySkeletalMeshActor::NCached;

	const FString& Context = Str::ECsSkeletalMeshActor_GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>(Context, Str::FECsSkeletalMeshActor, Index);
}

FString UCsScriptLibrary_SkeletalMeshActor::ECsSkeletalMeshActor_ToString(const FECsSkeletalMeshActor& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_SkeletalMeshActor::ECsSkeletalMeshActor_GetCount()
{
	return EMCsSkeletalMeshActor::Get().Num();
}

void UCsScriptLibrary_SkeletalMeshActor::ECsSkeletalMeshActor_GetAll(TArray<FECsSkeletalMeshActor>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>(OutTypes);
}

FECsSkeletalMeshActor UCsScriptLibrary_SkeletalMeshActor::ECsSkeletalMeshActor_GetMax()
{
	return EMCsSkeletalMeshActor::Get().GetMAX();
}

bool UCsScriptLibrary_SkeletalMeshActor::EqualEqual_SkeletalMeshActorSkeletalMeshActor(const FECsSkeletalMeshActor& A, const FECsSkeletalMeshActor& B)
{
	return A == B;
}

#pragma endregion Enum