// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Script/CsScriptLibrary_FX.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"
#include "Managers/FX/CsLibrary_FX.h"

// Cached
#pragma region

namespace NCsScriptLibraryFX
{ 
	namespace NCached
	{
		namespace Str
		{
			const FString FECsFX = TEXT("FECsFX");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_FX, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_FX, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_FX, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_FX::UCsScriptLibrary_FX(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsFX
#define EnumType FECsFX

EnumType UCsScriptLibrary_FX::Get(const FString& Name)
{
	using namespace NCsScriptLibraryFX::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_FX::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryFX::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_FX::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_FX::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_FX::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_FX::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_FX::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum

UNiagaraSystem* UCsScriptLibrary_FX::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	typedef NCsFX::FLibrary FXLibrary;

	return FXLibrary::SafeLoad(Context, Path);
}

UNiagaraSystem* UCsScriptLibrary_FX::LoadByStringPath(const FString& Context, const FString& Path)
{
	typedef NCsFX::FLibrary FXLibrary;

	return FXLibrary::SafeLoad(Context, Path);
}

FCsRoutineHandle UCsScriptLibrary_FX::Spawn(const FString& Context, UObject* WorldContextObject, const FCsFX_Spawn_Params& Params)
{
	using namespace NCsScriptLibraryFX::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy the script params to the native params.
	typedef NCsFX::FLibrary FXLibrary;
	typedef NCsFX::NSpawn::NParams::FResource ParamsResourceType;
	typedef NCsFX::NSpawn::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = FXLibrary::Get().AllocateSpawnParams();
	ParamsType* Parms				   = ParmsContainer->Get();

	Params.CopyToParamsAsValue(Parms);

	return FXLibrary::SafeSpawn(Ctxt, WorldContextObject, ParmsContainer);
}