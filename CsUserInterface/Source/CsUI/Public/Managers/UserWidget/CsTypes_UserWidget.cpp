// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/CsTypes_UserWidget.h"

// Types
#include "CsMacro_Misc.h"
// Library
	// Settings
#include "Settings/CsLibrary_UserInterfaceSettings.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// UI
#include "Blueprint/UserWidget.h"
// Utility
#include "Utility/CsUIPopulateEnumMapFromSettings.h"
#include "Utility/CsUILog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_UserWidget)

// UserWidget
#pragma region

namespace NCsUserWidget
{
	namespace NCached
	{
		namespace Str
		{
			const FString UserWidget = TEXT("UserWidget");
		}

		namespace Name
		{
			const FName UserWidgets = FName("UserWidgets");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsUserWidget::NCached;

		typedef NCsUI::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_UserWidget();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_UserWidget();
		Payload.EnumName				 = Str::UserWidget;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsUI::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsUserWidget::NCached;

		typedef FCsUIPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::UserWidgets;
		Payload.EnumName				 = Str::UserWidget;
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

		EMCsUserWidget::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsUserWidget_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsUserWidget_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion UserWidget

// UserWidgetClass
#pragma region

namespace NCsUserWidgetClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString UserWidgetClass = TEXT("UserWidgetClass");
		}

		namespace Name
		{
			const FName UserWidgetClasses = FName("UserWidgetClasses");
		}
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsUserWidgetClass::NCached;

		typedef FCsUIPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::UserWidgetClasses;
		Payload.EnumName				 = Str::UserWidgetClass;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsUI::FLog::Warning;

		FCsUIPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsUserWidgetClass::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion UserWidgetClass

// UserWidgetData
#pragma region

namespace NCsUserWidgetData
{
}

#pragma endregion UserWidgetData

// UserWidgetPooled
#pragma region

namespace NCsUserWidgetPooled
{
	namespace NCached
	{
		namespace Str
		{
			const FString UserWidgetPooled = TEXT("UserWidgetPooled");
		}

		namespace Name
		{
			const FName UserWidgetPooled = FName("UserWidgetPooled");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsUserWidgetPooled::NCached;

		typedef NCsUI::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_UserWidgetPooled();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_UserWidgetPooled();
		Payload.EnumName				 = Str::UserWidgetPooled;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsUI::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsUserWidgetPooled::NCached;

		typedef FCsUIPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::UserWidgetPooled;
		Payload.EnumName				 = Str::UserWidgetPooled;
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

		EMCsUserWidgetPooled::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsUserWidgetPooled_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsUserWidgetPooled_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion UserWidgetPooled

// UserWidgetPooledClass
#pragma region

namespace NCsUserWidgetPooledClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString UserWidgetPooledClass = TEXT("UserWidgetPooledClass");
		}

		namespace Name
		{
			const FName UserWidgetPooledClasses = FName("UserWidgetPooledClasses");
		}
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsUserWidgetPooledClass::NCached;

		typedef FCsUIPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::UserWidgetPooledClasses;
		Payload.EnumName				 = Str::UserWidgetPooledClass;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsUI::FLog::Warning;

		FCsUIPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsUserWidgetPooledClass::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion UserWidgetPooledClass

// FCsUserWidgetPtr
#pragma region

UClass* FCsUserWidgetPtr::LoadChecked(const FString& Context)
{
	checkf(Widget.ToSoftObjectPath().IsValid(), TEXT("FCsUserWidgetPtr::LoadChecked: Widget's Path: %s is NOT Valid."), *(Widget.ToSoftObjectPath().ToString()));

	Widget_Class = Widget.LoadSynchronous();

	checkf(Widget_Class, TEXT("FCsUserWidgetPtr::LoadChecked: Widget has NOT been loaded from Path @ %s."), *(Widget.ToSoftObjectPath().ToString()));

	Widget_SubclassOf = Widget_Class;
	UObject* DOb	  = Widget_Class->GetDefaultObject();

	checkf(DOb, TEXT("FCsUserWidgetPtr::LoadChecked: Failed to get DefaultObject from Widget_Class: %s."), *(Widget_Class->GetName()));

	Widget_Internal = CS_CAST_CHECKED(DOb, UObject, UUserWidget);
	return Widget_Class;
}

UClass* FCsUserWidgetPtr::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
{
	if (!Widget.ToSoftObjectPath().IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%: FCsUserWidgetPtr.Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString())));
		return nullptr;
	}

	Widget_Class = Widget.LoadSynchronous();

	if (!Widget_Class)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget has NOT been loaded from Path @ %s."), *Context, *(Widget.ToSoftObjectPath().ToString())));
		return nullptr;
	}

	Widget_SubclassOf = Widget_Class;
	UObject* DOb	  = Widget_Class->GetDefaultObject();

	if (!DOb)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DefaultObject from Widget_Class: %s."), *Context, *(Widget_Class->GetName())));
		return nullptr;
	}

	Widget_Internal = CS_CAST(DOb, UObject, UUserWidget);

	if (!Widget_Internal)
		return nullptr;
	return Widget_Class;
}

void FCsUserWidgetPtr::SetObject(UObject* InWidget)
{
	checkf(InWidget, TEXT("FCsUserWidgetPtr::SetObject: InWidget is NULL."));
	checkf(Cast<UUserWidget>(InWidget), TEXT("FCsUserWidgetPtr::SetObject: InWidget is NOT a UUserWidget."));

	Widget			  = Cast<UUserWidget>(InWidget);
	Widget_Internal	  = Cast<UUserWidget>(InWidget);
	Widget_Class	  = InWidget->GetClass();
	Widget_SubclassOf = Widget_Class;
}

UObject* FCsUserWidgetPtr::GetObject() const
{
	return Widget_Internal;
}

#pragma endregion FCsUserWidgetPtr

// UserWidgetDeallocateMethod
#pragma region

namespace NCsUserWidgetDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsUserWidgetDeallocateMethod EnumMapType;

		CSUI_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSUI_API CS_ADD_TO_ENUM_MAP(Complete);
		CSUI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsUserWidgetDeallocateMethod_MAX, "MAX");
	}

	CSUI_API const uint8 MAX = (uint8)Type::ECsUserWidgetDeallocateMethod_MAX;
}

namespace NCsUserWidget
{
	namespace NDeallocateMethod
	{
		namespace Ref
		{
			typedef EMDeallocateMethod EnumMapType;

			CSUI_API CS_ADD_TO_ENUM_MAP(LifeTime);
			CSUI_API CS_ADD_TO_ENUM_MAP(Complete);
		}
	}
}

#pragma endregion UserWidgetDeallocateMethod

// UserWidgetPosition
#pragma region

namespace NCsUserWidgetPosition
{
	namespace Ref
	{
		typedef EMCsUserWidgetPosition EnumMapType;

		CSUI_API CS_ADD_TO_ENUM_MAP(Screen);
		CSUI_API CS_ADD_TO_ENUM_MAP(World);
		CSUI_API CS_ADD_TO_ENUM_MAP(Parent);
		CSUI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsUserWidgetPosition_MAX, "MAX");
	}

	CSUI_API const uint8 MAX = (uint8)Type::ECsUserWidgetPosition_MAX;
}

namespace NCsUserWidget
{
	namespace NPosition
	{
		namespace Ref
		{
			typedef EMPosition EnumMapType;

			CSUI_API CS_ADD_TO_ENUM_MAP(Screen);
			CSUI_API CS_ADD_TO_ENUM_MAP(World);
			CSUI_API CS_ADD_TO_ENUM_MAP(Parent);
			CSUI_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPosition_MAX, "MAX");
		}
	}
}

#pragma endregion UserWidgetPosition