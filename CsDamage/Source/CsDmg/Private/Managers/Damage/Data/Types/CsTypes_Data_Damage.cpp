// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Data/CsLibrary_Data.h"
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsDmgLog.h"
#include "Utility/CsLibrary_EnumStruct.h"
// Data
#include "Data/CsDmgGetDataRootSet.h"

// DamageData
#pragma region

namespace NCsDamageData
{
	namespace NCached
	{
		namespace Str
		{
			const FString DamageData = TEXT("DamageData");
		}

		namespace Name
		{
			const FName Damages = FName("Damages");
		}
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsDamageData::NCached;

		const FCsDmgDataRootSet* DataRootSet = CsEnumStructPopulateLibrary::GetDataRootSet<FCsDmgDataRootSet, ICsDmgGetDataRootSet, &ICsDmgGetDataRootSet::GetCsDmgDataRootSet>(Context, ContextRoot);

		if (!DataRootSet)
			return;

		typedef CsEnumStructPopulateLibrary::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableSoftObject		 = DataRootSet->GetDataTableSoftObjectChecked(Context, Name::Damages);
		Payload.EnumName				 = Str::DamageData;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsDamage::FLog::Warning;

		CsEnumStructPopulateLibrary::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsDamageData::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion DamageData

// FCsData_ECsDamageData
#pragma region

bool FCsData_ECsDamageData::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, Value);
	return true;
}

bool FCsData_ECsDamageData::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageData, FECsDamageData, Value)
	return true;
}

#pragma endregion FCsData_ECsDamageData

// FCsData_DamagePtr
#pragma region

namespace NCsDataDamagePtr
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsData_DamagePtr, Unload);
		}
	}
}

#define USING_NS_CACHED using namespace NCsDataDamagePtr::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsDataDamagePtr::NCached; \
	const FString& Context = Str::__FunctionName

UObject* FCsData_DamagePtr::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
{
	CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(Data, UObject)

	UObject* O = Data.LoadSynchronous();

	if (!O)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Data at Path: %s."), *Context, *(Data.ToString())))
		return nullptr;
	}
	return O;
}

void FCsData_DamagePtr::Unload()
{
	SET_CONTEXT(Unload);

	if (IsValid(Data_Internal))
	{
		typedef NCsData::FLibrary DataLibrary;

		if (DataLibrary::SafeScriptImplements(Context, Data_Internal, nullptr))
			DataLibrary::Script_UnloadChecked(Context, Data_Internal);
		else
			DataLibrary::UnloadChecked(Context, Data_Internal);
	}

	Data_Internal = nullptr;
	Data_Class = nullptr;
}

#undef USING_NS_CACHED
#undef SET_CONTEXT

#pragma endregion FCsData_DamagePtr