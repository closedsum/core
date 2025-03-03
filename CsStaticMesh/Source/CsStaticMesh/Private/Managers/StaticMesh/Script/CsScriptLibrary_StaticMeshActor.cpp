// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Script/CsScriptLibrary_StaticMeshActor.h"

// Library
#include "Library/CsLibrary_Enum.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_StaticMeshActor)

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
			const FString EnumType = TEXT("FECsStaticMeshActor");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_StaticMeshActor::UCsScriptLibrary_StaticMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryStaticMeshActor::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsScriptLibraryStaticMeshActor::NCached; \
	const FString& Context = Str::__FunctionName
using CLASS_TYPE = UCsScriptLibrary_StaticMeshActor;
using EnumMapType = EMCsStaticMeshActor;
using EnumType = FECsStaticMeshActor;

// Enum
#pragma region

EnumType CLASS_TYPE::Get(const FString& Name)
{
	SET_CONTEXT(Get);

	return CsEnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType CLASS_TYPE::GetByIndex(const int32& Index)
{
	SET_CONTEXT(GetByIndex);

	return CsEnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString CLASS_TYPE::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 CLASS_TYPE::GetCount()
{
	return EnumMapType::Get().Num();
}

void CLASS_TYPE::GetAll(TArray<EnumType>& OutTypes)
{
	CsEnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType CLASS_TYPE::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool CLASS_TYPE::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#pragma endregion Enum

#undef USING_NS_CACHED
#undef SET_CONTEXT