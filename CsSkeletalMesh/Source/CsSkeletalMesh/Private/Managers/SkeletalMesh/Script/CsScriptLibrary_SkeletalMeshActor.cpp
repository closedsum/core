// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/SkeletalMesh/Script/CsScriptLibrary_SkeletalMeshActor.h"

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

#define USING_NS_CACHED using namespace NCsScriptLibrarySkeletalMeshActor::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsScriptLibrarySkeletalMeshActor::NCached; \
	const FString& Context = Str::__FunctionName
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibrarySkeletalMeshActor::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define CLASS_TYPE UCsScriptLibrary_SkeletalMeshActor
#define EnumLibrary NCsEnum::FLibrary
#define EnumMapType EMCsSkeletalMeshActor
#define EnumType FECsSkeletalMeshActor

// Enum
#pragma region

EnumType CLASS_TYPE::Get(const FString& Name)
{
	SET_CONTEXT(Get);

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType CLASS_TYPE::GetByIndex(const int32& Index)
{
	SET_CONTEXT(GetByIndex);

	return EnumLibrary::GetSafeByIndex<EnumMapType, FECsSkeletalMeshActor>(Context, Str::EnumType, Index);
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
	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
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
#undef CONDITIONAL_SET_CTXT
#undef CLASS_TYPE
#undef EnumMapType
#undef EnumType