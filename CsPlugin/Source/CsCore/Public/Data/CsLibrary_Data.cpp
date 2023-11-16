// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsLibrary_Data.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Load.h"
// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
	// Common
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Data/CsScriptData.h"

namespace NCsData
{
	namespace NCached
	{
		namespace Str
		{
			CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::FLibrary, SafeLoad);
		}

		namespace Name
		{
			const FName Script_Load = FName("Script_Load");
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

	// ICsScriptData
	#pragma region
	
	bool FLibrary::SafeScript_Load(const FString& Context, UObject* Object, const int32& LoadFlags, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		using namespace NCsData::NCached;

		OutSuccess = false;

		CS_IS_PENDING_KILL(Object)
		
		if (Object->GetClass()->ImplementsInterface(UCsScriptData::StaticClass()))
		{
			UFunction* Function = Object->FindFunction(Name::Script_Load);

			if (!Function ||
				!Function->IsInBlueprint())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the Function: %s."), *Context, *PrintObjectAndClass(Object), *(Name::Script_Load.ToString())));
				return false;
			}
			return ICsScriptData::Execute_Script_Load(Object, LoadFlags, OutSuccess);
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the interface: ICsScriptData."), *Context, *PrintObjectAndClass(Object)));
		return true;
	}

	#pragma endregion ICsScriptData

	// Implement
	#pragma region

	#define ObjectLibrary NCsObject::FLibrary

	bool FLibrary::ScriptImplementsChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		UClass* Class = Object->GetClass();

		checkf(Class, TEXT("%s: Failed to get class from Object: %s."), *Context, *(Object->GetName()));
		checkf(Class->ImplementsInterface(UCsScriptData::StaticClass()), TEXT("%s: %s does NOT implement the interface: ICsScriptData."), *Context, *ObjectLibrary::PrintObjectAndClass(Object));
		return true;
	}

	bool FLibrary::SafeScriptImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PENDING_KILL(Object)

		UClass* Class = Object->GetClass();

		if (!Class)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get class from Object: %s."), *Context, *(Object->GetName())));
			return false;
		}

		const bool Success = Class->ImplementsInterface(UCsScriptData::StaticClass());

		if (!Success)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the interface: ICsScriptData."), *Context, *ObjectLibrary::PrintObjectAndClass(Object)));
		}
		return Success;
	}

	bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		UClass* Class = Object->GetClass();

		checkf(Class, TEXT("%s: Failed to get class from Object: %s."), *Context, *(Object->GetName()));
		checkf(Class->ImplementsInterface(UCsData::StaticClass()), TEXT("%s: %s does NOT implement the interface: ICsData."), *Context, *ObjectLibrary::PrintObjectAndClass(Object));
		return true;
	}

	bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PENDING_KILL(Object)

		UClass* Class = Object->GetClass();

		if (!Class)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get class from Object: %s."), *Context, *(Object->GetName())));
			return false;
		}

		const bool Success = Class->ImplementsInterface(UCsData::StaticClass());

		if (!Success)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the interface: ICsData."), *Context, *ObjectLibrary::PrintObjectAndClass(Object)));
		}
		return Success;
	}

	#undef ObjectLibrary

	#pragma endregion Implment

	// Get
	#pragma region

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

		ICsData* UData = DataManagerLibrary::GetDataChecked(Context, WorldContext, DataName);
		DataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));

		return Data;
	}

	DataType* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const FName& DataName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		if (ICsData* UData = DataManagerLibrary::GetSafeData(Context, WorldContext, DataName, Log))
		{
			DataType* Data = UData->_getIData();

			if (!Data)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: DataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
			}
			return Data;
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

	#pragma endregion Get
}