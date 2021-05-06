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
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");
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

FECsSkeletalMeshActor UCsScriptLibrary_SkeletalMeshActor::Get(const FString& Name)
{
	using namespace NCsScriptLibrarySkeletalMeshActor::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>(Context, Str::FECsSkeletalMeshActor, Name);
}

FECsSkeletalMeshActor UCsScriptLibrary_SkeletalMeshActor::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibrarySkeletalMeshActor::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>(Context, Str::FECsSkeletalMeshActor, Index);
}

FString UCsScriptLibrary_SkeletalMeshActor::ToString(const FECsSkeletalMeshActor& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_SkeletalMeshActor::GetCount()
{
	return EMCsSkeletalMeshActor::Get().Num();
}

void UCsScriptLibrary_SkeletalMeshActor::GetAll(TArray<FECsSkeletalMeshActor>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>(OutTypes);
}

FECsSkeletalMeshActor UCsScriptLibrary_SkeletalMeshActor::GetMax()
{
	return EMCsSkeletalMeshActor::Get().GetMAX();
}

bool UCsScriptLibrary_SkeletalMeshActor::EqualEqual(const FECsSkeletalMeshActor& A, const FECsSkeletalMeshActor& B)
{
	return A == B;
}

#pragma endregion Enum