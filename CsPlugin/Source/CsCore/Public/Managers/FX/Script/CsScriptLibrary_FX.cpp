// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
			const FString ECsFX_Get = TEXT("ECsFX_Get");
			const FString ECsFX_GetByIndex = TEXT("ECsFX_GetByIndex");

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

FECsFX UCsScriptLibrary_FX::ECsFX_Get(const FString& Name)
{
	using namespace NCsScriptLibraryFX::NCached;

	const FString& Context = Str::ECsFX_Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EMCsFX, FECsFX>(Context, Str::FECsFX, Name);
}

FECsFX UCsScriptLibrary_FX::ECsFX_GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibraryFX::NCached;

	const FString& Context = Str::ECsFX_GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EMCsFX, FECsFX>(Context, Str::FECsFX, Index);
}

FString UCsScriptLibrary_FX::ECsFX_ToString(const FECsFX& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_FX::ECsFX_GetCount()
{
	return EMCsFX::Get().Num();
}

void UCsScriptLibrary_FX::ECsFX_GetAll(TArray<FECsFX>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EMCsFX, FECsFX>(OutTypes);
}

FECsFX UCsScriptLibrary_FX::ECsFX_GetMax()
{
	return EMCsFX::Get().GetMAX();
}

bool UCsScriptLibrary_FX::EqualEqual_FXFX(const FECsFX& A, const FECsFX& B)
{
	return A == B;
}

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

	Params.CopyToParams(Parms);

	return FXLibrary::SafeSpawn(Ctxt, WorldContextObject, ParmsContainer);
}