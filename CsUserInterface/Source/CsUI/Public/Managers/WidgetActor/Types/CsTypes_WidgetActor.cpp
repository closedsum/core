// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"
#include "CsUI.h"

// Library
	// Settings
#include "Settings/CsLibrary_UserInterfaceSettings.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsUIPopulateEnumMapFromSettings.h"

// WidgetActor
#pragma region

namespace NCsWidgetActor
{
	namespace NCached
	{
		namespace Str
		{
			const FString WidgetActor = TEXT("WidgetActor");
		}

		namespace Name
		{
			const FName WidgetActors = TEXT("WidgetActors");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsWidgetActor::NCached;

		typedef NCsUI::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_WidgetActor();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_WidgetActor();
		Payload.EnumName				 = Str::WidgetActor;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsUI::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsWidgetActor::NCached;

		typedef FCsUIPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::WidgetActors;
		Payload.EnumName				 = Str::WidgetActor;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsUI::FLog::Warning;

		FCsUIPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		typedef NCsUI::NSettings::FLibrary SettingsLibrary;

		EMCsWidgetActor::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsWidgetActor_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsWidgetActor_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion WidgetActor

// WidgetActorClass
#pragma region

namespace NCsWidgetActorClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString WidgetActorClass = TEXT("WidgetActorClass");
		}

		namespace Name
		{
			const FName WidgetActorClasses = FName("WidgetActorClasses");
		}
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsWidgetActorClass::NCached;

		typedef FCsUIPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::WidgetActorClasses;
		Payload.EnumName				 = Str::WidgetActorClass;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsUI::FLog::Warning;

		FCsUIPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsWidgetActorClass::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion WidgetActorClass

// WidgetActorDeallocateMethod
#pragma region

namespace NCsWidgetActorDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsWidgetActorDeallocateMethod EnumMapType;

		CSUI_API CS_ADD_TO_ENUM_MAP(Complete);
		CSUI_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSUI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsWidgetActorDeallocateMethod_MAX, "MAX");
	}

	CSUI_API const uint8 MAX = (uint8)Type::ECsWidgetActorDeallocateMethod_MAX;
}

#pragma endregion WidgetActorDeallocateMethod

// FCsWidgetActorPooled_CameraInfo
#pragma region

#define InfoType NCsWidgetActor::NCamera::FInfo

void FCsWidgetActorPooled_CameraInfo::CopyToInfo(InfoType* Info)
{
	Info->SetLerpRate(&LerpRate);
	Info->SetLockAxes(&LockAxes);
	Info->SetRotation(&Rotation);
}

void FCsWidgetActorPooled_CameraInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetLerpRate(LerpRate);
	Info->SetLockAxes(LockAxes);
	Info->SetRotation(Rotation);
}

#undef InfoType

bool FCsWidgetActorPooled_CameraInfo::IsValidChecked(const FString& Context) const
{
	checkf(LockAxes == 7, TEXT("%s: LockAxes == 7 (Pitch | Yaw | Row). All Axes can NOT be locked when orienting to the Player Camera."), *Context);
	return true;
}

bool FCsWidgetActorPooled_CameraInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	if (LockAxes == 7)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: LockAxes == 7 (Pitch | Yaw | Row). All Axes can NOT be locked when orienting to the Player Camera."), *Context));
		return false;
	}
	return true;
}

namespace NCsWidgetActor
{
	namespace NCamera
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			checkf(GetLockAxes() == 7, TEXT("%s: GetLockAxes() == 7 (Pitch | Yaw | Row). All Axes can NOT be locked when orienting to the Player Camera."), *Context);
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			if (GetLockAxes() == 7)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetLockAxes() == 7 (Pitch | Yaw | Row). All Axes can NOT be locked when orienting to the Player Camera"), *Context));
				return false;
			}
			return true;
		}
	}
}

#pragma endregion FCsWidgetActorPooled_CameraInfo

// FCsWidgetActorPooledInfo
#pragma region

bool FCsWidgetActorPooledInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWidgetActor, WidgetActor)
	CS_IS_ENUM_VALID_CHECKED(EMCsWidgetActorDeallocateMethod, DeallocateMethod)

	if (DeallocateMethod == ECsWidgetActorDeallocateMethod::LifeTime)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(LifeTime, 0.0f)
	}
	else
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(LifeTime, 0.0f)
	}
	if (bCameraInfo)
	{
		CS_IS_VALID_CHECKED(CameraInfo);
	}
	return true;
}

bool FCsWidgetActorPooledInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsWidgetActor, FECsWidgetActor, WidgetActor)
	CS_IS_ENUM_VALID(EMCsWidgetActorDeallocateMethod, ECsWidgetActorDeallocateMethod, DeallocateMethod)

	if (DeallocateMethod == ECsWidgetActorDeallocateMethod::LifeTime)
	{
		CS_IS_FLOAT_GREATER_THAN(LifeTime, 0.0f)
	}
	else
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(LifeTime, 0.0f)
	}

	if (bCameraInfo)
	{
		CS_IS_VALID(CameraInfo)
	}
	return true;
}

#pragma endregion FCsWidgetActorPooledInfo