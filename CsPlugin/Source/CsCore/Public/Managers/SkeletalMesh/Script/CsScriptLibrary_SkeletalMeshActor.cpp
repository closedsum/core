// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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

#define EnumMapType EMCsSkeletalMeshActor
#define EnumType FECsSkeletalMeshActor

EnumType UCsScriptLibrary_SkeletalMeshActor::Get(const FString& Name)
{
	using namespace NCsScriptLibrarySkeletalMeshActor::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_SkeletalMeshActor::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibrarySkeletalMeshActor::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, FECsSkeletalMeshActor>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_SkeletalMeshActor::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_SkeletalMeshActor::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_SkeletalMeshActor::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_SkeletalMeshActor::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_SkeletalMeshActor::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum