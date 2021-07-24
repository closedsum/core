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

#define EnumMapType EMCsStaticMeshActor
#define EnumType FECsStaticMeshActor

EnumType UCsScriptLibrary_StaticMeshActor::Get(const FString& Name)
{
	using namespace NCsScriptLibraryStaticMeshActor::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_StaticMeshActor::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryStaticMeshActor::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_StaticMeshActor::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_StaticMeshActor::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_StaticMeshActor::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_StaticMeshActor::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_StaticMeshActor::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum