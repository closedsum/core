// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data.h"
#include "CsCore.h"

// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsData
{
	namespace NCached
	{
		namespace Str
		{
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::FLibrary, SafeLoad);
		}
	}

	FString FLibrary::PrintObjectAndClass(UObject* Object)
	{
		return FString::Printf(TEXT("Object: %s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	FString FLibrary::PrintObjectAndClass(ICsData* Data, const FString& MemberName)
	{
		return FString::Printf(TEXT("%s: %s with Class: %s"), *MemberName, *(Data->_getUObject()->GetName()), *(Data->_getUObject()->GetClass()->GetName()));
	}

	FString FLibrary::PrintObjectAndClass(ICsData* Data)
	{
		if (UObject* O = Data->_getUObject())
			return PrintObjectAndClass(O);
		return FString::Printf(TEXT("INVALID (Non-UObject)"));
	}

	// Load
	#pragma region
	#define DataType NCsData::IData

	DataType* FLibrary::SafeLoad(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(Object)

		ICsData* UData = CS_INTERFACE_CAST(Object, UObject, ICsData);

		if (!UData)
			return nullptr;

		UData->Load(NCsLoadFlags::All);

		DataType* Data = UData->_getIData();

		if (!Data)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
			return nullptr;
		}
		return Data;
	}

	DataType* FLibrary::SafeLoad(UObject* Object)
	{
		using namespace NCached;

		const FString& Context = Str::SafeLoad;

		return SafeLoad(Context, Object, nullptr);
	}

	#undef DataType
	#pragma endregion Load

	#define DataType NCsData::IData

	DataType* FLibrary::GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(Object)

		ICsData* UData = CS_INTERFACE_CAST(Object, UObject, ICsData);

		if (!UData)
			return nullptr;

		DataType* Data = UData->_getIData();

		if (!Data)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
			return nullptr;
		}
		return Data;
	}

	DataType* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const FName& DataName)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		ICsData* UData = DataManagerLibrary::GetChecked(Context, WorldContext)->GetDataChecked(Context, DataName);
		DataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));

		return Data;
	}

	DataType* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const FName& DataName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		if (UCsManager_Data* Manager_Data = DataManagerLibrary::GetSafe(Context, WorldContext, Log))
		{
			if (ICsData* UData = Manager_Data->GetSafeData(Context, DataName, Log))
			{
				DataType* Data = UData->_getIData();

				if (!Data)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
				}
				return Data;
			}
		}
		return nullptr;
	}

	DataType* FLibrary::GetChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

		ICsData* UData = CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsData);

		return GetChecked(Context, UData);
	}

	DataType* FLibrary::GetChecked(const FString& Context, ICsData* UData)
	{
		CS_IS_PTR_NULL_CHECKED(UData)

		DataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));

		return Data;
	}

	#undef DataType
}