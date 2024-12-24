// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsLibrary_Data.h"

// Types
#include "CsMacro_Misc.h"
#include "Types/CsTypes_Load.h"
// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
	// Common
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Class.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Data/CsScriptData.h"

namespace NCsData
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSDATA_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::FLibrary, SafeLoad);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::FLibrary, SafeImplements);
			}

			namespace Name
			{
				const FName Script_Load = FName("Script_Load");
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsData::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsData::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define LogLevel void(*Log)(const FString&) /*=&NCsData::FLog::Warning*/

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
		return FString::Printf(TEXT("%s (Non-UObject)"), *(Data->GetInterfaceMap()->GetRootName().ToString()));
	}

	FString FLibrary::PrintDataAndClass(UObject* Object)
	{
		return FString::Printf(TEXT("Data: %s with Class: %s"), *(Object->GetName()), *(Object->GetClass()->GetName()));
	}

	FString FLibrary::PrintDataAndClass(ICsData* Data)
	{
		if (UObject* O = Data->_getUObject())
			return PrintDataAndClass(O);
		return FString::Printf(TEXT("%s (Non-UObject)"), *(Data->GetInterfaceMap()->GetRootName().ToString()));
	}

	// Convert
	#pragma region

	CsDataType* FLibrary::ConvertChecked(const FString& Context, UObject* Object)
	{
		ICsData* UData   = CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsData);
		CsDataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));
		return Data;
	}

	CsDataType* FLibrary::SafeConvert(const FString& Context, UObject* Object, LogLevel)
	{
		if (ICsData* UData = CS_INTERFACE_CAST(Object, UObject, ICsData))
		{
			CsDataType* Data = UData->_getIData();

			if (!Data)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
				return nullptr;
			}
			return Data;
		}
		return nullptr;
	}

	#pragma endregion Convert

	// Load
	#pragma region

	CsDataType* FLibrary::SafeLoad(const FString& Context, UObject* Object, LogLevel)
	{
		ICsData* UData = CS_INTERFACE_CAST(Object, UObject, ICsData);

		if (!UData)
			return nullptr;

		UData->Load(NCsLoadFlags::All);

		CsDataType* Data = UData->_getIData();

		if (!Data)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
			return nullptr;
		}
		return Data;
	}

	CsDataType* FLibrary::SafeLoad(UObject* Object)
	{
		SET_CONTEXT(SafeLoad);

		return SafeLoad(Context, Object, nullptr);
	}

	const CsDataType* FLibrary::TopLoadChecked(const FString& Context, UObject* Object)
	{
		ICsData* UData = CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsData);

		UData->TopLoad();

		CsDataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));
		return Data;
	}

	const CsDataType* FLibrary::SafeTopLoad(const FString& Context, UObject* Object, LogLevel)
	{
		ICsData* UData = CS_INTERFACE_CAST(Object, UObject, ICsData);

		if (!UData)
			return nullptr;

		UData->TopLoad();

		CsDataType* Data = UData->_getIData();

		if (!Data)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
			return nullptr;
		}
		return Data;
	}

	void FLibrary::UnloadChecked(const FString& Context, UObject* Object)
	{
		CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsData)->Unload();
	}

	void FLibrary::Script_UnloadChecked(const FString& Context, UObject* Object)
	{
		check(ScriptImplementsChecked(Context, Object));

		bool OutSuccess = false;
		ICsScriptData::Execute_Script_Unload(Object, OutSuccess);
		checkf(OutSuccess, TEXT("%s: %s does NOT implement the function: Unload (Script_Unload) properly."), *Context, *PrintDataAndClass(Object));
	}

	#pragma endregion Load

	// ICsScriptData
	#pragma region
	
	bool FLibrary::SafeScript_Load(const FString& Context, UObject* Object, const int32& LoadFlags, bool& OutSuccess, LogLevel)
	{
		USING_NS_CACHED

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
			
			const bool Result = ICsScriptData::Execute_Script_Load(Object, LoadFlags, OutSuccess);

			if (!OutSuccess)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the Function: %s."), *Context, *PrintObjectAndClass(Object), *(Name::Script_Load.ToString())));
			}
			return Result;
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the interface: ICsScriptData."), *Context, *PrintObjectAndClass(Object)));
		return true;
	}

	UObject* FLibrary::SafeScript_Load(const FString& Context, const FString& Path, const int32& LoadFlags, bool& OutSuccess, LogLevel)
	{
		OutSuccess = false;

		if (UObject* DOb = CsClassLibrary::SafeLoadDefaultObject(Context, Path, OutSuccess, Log))
		{
			if (SafeScript_Load(Context, DOb, LoadFlags, OutSuccess, Log))
				return DOb;
		}
		return nullptr;
	}

	#pragma endregion ICsScriptData

	// Implement
	#pragma region

	bool FLibrary::ScriptImplementsChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		UClass* Class = Object->GetClass();

		checkf(Class, TEXT("%s: Failed to get class from Object: %s."), *Context, *(Object->GetName()));
		checkf(Class->ImplementsInterface(UCsScriptData::StaticClass()), TEXT("%s: %s does NOT implement the interface: ICsScriptData."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object));
		return true;
	}

	bool FLibrary::SafeScriptImplements(const FString& Context, const UObject* Object, LogLevel)
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
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the interface: ICsScriptData."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object)));
		}
		return Success;
	}

	bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		UClass* Class = Object->GetClass();

		checkf(Class, TEXT("%s: Failed to get class from Object: %s."), *Context, *(Object->GetName()));
		checkf(Class->ImplementsInterface(UCsData::StaticClass()), TEXT("%s: %s does NOT implement the interface: ICsData."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object));
		return true;
	}

	bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, LogLevel)
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
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the interface: ICsData."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object)));
		}
		return Success;
	}

	bool FLibrary::SafeImplements(const UObject* Object)
	{
		SET_CONTEXT(SafeImplements);

		return SafeImplements(Context, Object, nullptr);
	}

	#pragma endregion Implment

	// Get
	#pragma region

	CsDataType* FLibrary::GetSafe(const FString& Context, UObject* Object, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(Object)

		ICsData* UData = CS_INTERFACE_CAST(Object, UObject, ICsData);

		if (!UData)
			return nullptr;

		CsDataType* Data = UData->_getIData();

		if (!Data)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
			return nullptr;
		}
		return Data;
	}

	CsDataType* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const FName& DataName)
	{
		ICsData* UData   = CsDataManagerLibrary::GetDataChecked(Context, WorldContext, DataName);
		CsDataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));
		return Data;
	}

	CsDataType* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const FName& DataName, LogLevel)
	{
		if (ICsData* UData = CsDataManagerLibrary::GetSafeData(Context, WorldContext, DataName, Log))
		{
			CsDataType* Data = UData->_getIData();

			if (!Data)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData))));
			}
			return Data;
		}
		return nullptr;
	}

	CsDataType* FLibrary::GetChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

		ICsData* UData = CS_INTERFACE_CAST_CHECKED(Object, UObject, ICsData);

		return GetChecked(Context, UData);
	}

	CsDataType* FLibrary::GetChecked(const FString& Context, ICsData* UData)
	{
		CS_IS_PTR_NULL_CHECKED(UData)

		CsDataType* Data = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: CsDataType (NCsData::IData) from %s."), *Context, *(PrintObjectAndClass(UData)));
		return Data;
	}

		// Script
	#pragma region

	UObject* FLibrary::GetScriptChecked(const FString& Context, const UObject* WorldContext, const FName& DataName)
	{
		UObject* UData = CsDataManagerLibrary::GetScriptDataObjectChecked(Context, WorldContext, DataName);
		
		check(ScriptImplementsChecked(Context, UData));
		return UData;
	}

	UObject* FLibrary::GetSafeScript(const FString& Context, const UObject* WorldContext, const FName& DataName, LogLevel)
	{
		if (UObject* UData = CsDataManagerLibrary::GetSafeScriptDataObject(Context, WorldContext, DataName, Log))
		{
			if (!SafeScriptImplements(Context, UData, Log))
				return nullptr;
			return UData;
		}
		return nullptr;
	}

	#pragma endregion Script

	#pragma endregion Get

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef LogLevel
}