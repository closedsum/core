// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Script/CsScriptLibrary_Sound.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Enum.h"
#include "Managers/Sound/CsLibrary_Sound.h"

// Cached
#pragma region

namespace NCsScriptLibrarySound
{ 
	namespace NCached
	{
		namespace Str
		{
			const FString FECsSound = TEXT("FECsSound");
			const FString Get = TEXT("Get");
			const FString GetByIndex = TEXT("GetByIndex");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Sound, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Sound, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Sound, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Sound::UCsScriptLibrary_Sound(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Enum
#pragma region

#define EnumMapType EMCsSound
#define EnumType FECsSound

EnumType UCsScriptLibrary_Sound::Get(const FString& Name)
{
	using namespace NCsScriptLibrarySound::NCached;

	const FString& Context = Str::Get;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafe<EnumMapType, EnumType>(Context, Str::EnumType, Name);
}

EnumType UCsScriptLibrary_Sound::GetByIndex(const int32& Index)
{
	using namespace NCsScriptLibrarySound::NCached;

	const FString& Context = Str::GetByIndex;

	typedef NCsEnum::FLibrary EnumLibrary;

	return EnumLibrary::GetSafeByIndex<EnumMapType, EnumType>(Context, Str::EnumType, Index);
}

FString UCsScriptLibrary_Sound::ToString(const EnumType& Enum)
{
	return Enum.ToString();
}

uint8 UCsScriptLibrary_Sound::GetCount()
{
	return EnumMapType::Get().Num();
}

void UCsScriptLibrary_Sound::GetAll(TArray<EnumType>& OutTypes)
{
	typedef NCsEnum::FLibrary EnumLibrary;

	EnumLibrary::GetAll<EnumMapType, EnumType>(OutTypes);
}

EnumType UCsScriptLibrary_Sound::GetMax()
{
	return EnumMapType::Get().GetMAX();
}

bool UCsScriptLibrary_Sound::EqualEqual(const EnumType& A, const EnumType& B)
{
	return A == B;
}

#undef EnumMapType
#undef EnumType

#pragma endregion Enum

USoundBase* UCsScriptLibrary_Sound::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	typedef NCsSound::FLibrary SoundLibrary;

	return SoundLibrary::SafeLoad(Context, Path);
}

USoundBase* UCsScriptLibrary_Sound::LoadByStringPath(const FString& Context, const FString& Path)
{
	typedef NCsSound::FLibrary SoundLibrary;

	return SoundLibrary::SafeLoad(Context, Path);
}

FCsRoutineHandle UCsScriptLibrary_Sound::Spawn(const FString& Context, UObject* WorldContextObject, const FCsSound_Spawn_Params& Params)
{
	using namespace NCsScriptLibrarySound::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	if (!Params.IsValid(Ctxt))
		return FCsRoutineHandle::Invalid;

	// Copy the script params to the native params.
	typedef NCsSound::FLibrary SoundLibrary;
	typedef NCsSound::NSpawn::NParams::FResource ParamsResourceType;
	typedef NCsSound::NSpawn::NParams::FParams ParamsType;

	ParamsResourceType* ParmsContainer = SoundLibrary::Get().AllocateSpawnParams();
	ParamsType* Parms				   = ParmsContainer->Get();

	Params.CopyToParams(Parms);

	return SoundLibrary::SafeSpawn(Ctxt, WorldContextObject, ParmsContainer);
}