// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Data
#include "Data/CsTableRowBase_Data.h"
// Log
#include "Utility/CsUILog.h"

#include "CsTypes_UI.generated.h"

// FCsUserWidget
#pragma region

class UUserWidget;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidget : public FCsTableRowBase_Data
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UUserWidget> Widget;

	UPROPERTY()
	int32 Widget_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UUserWidget* Widget_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Widget_Class;

	UPROPERTY(Transient, BlueprintReadOnly)
	TSubclassOf<UUserWidget> Widget_SubclassOf;

	FCsUserWidget() :
		Widget(nullptr),
		Widget_LoadFlags(0),
		Widget_Internal(nullptr),
		Widget_Class(nullptr),
		Widget_SubclassOf(nullptr)
	{
	}

// FCsTableRowBase_Data
#pragma region
public:

	virtual void Unload() override 
	{
		Widget_Internal = nullptr;
		Widget_Class = nullptr;
	}

#pragma endregion FCsTableRowBase_Data

public:

	FORCEINLINE UUserWidget* Get() const { return Widget_Internal; }
	
	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Widget_Class; }

	template<typename T>
	FORCEINLINE T* GetClass() const { return Cast<T>(GetClass()); }

	FORCEINLINE UClass* GetClassChecked() const
	{
		checkf(Widget.ToSoftObjectPath().IsValid(), TEXT("FCsUserWidgetPtr::GetClassChecked: Widget's Path: %s is NOT Valid."), *(Widget.ToSoftObjectPath().ToString()));
		checkf(Widget_Class, TEXT("FCsUserWidgetPtr::GetClassChecked: Widget has NOT been loaded from Path @ %s."), *(Widget.ToSoftObjectPath().ToString()));
		return Widget_Class;
	}

	FORCEINLINE UClass* GetClassChecked(const FString& Context) const
	{
		checkf(Widget.ToSoftObjectPath().IsValid(), TEXT("%s: Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString()));
		checkf(Widget_Class, TEXT("%s: Widget has NOT been loaded from Path @ %s."), *Context, *(Widget.ToSoftObjectPath().ToString()));
		return Widget_Class;
	}

	FORCEINLINE UClass* GetSafeClass(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const
	{
		if (!Widget.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString())));
			return nullptr;
		}

		if (!Widget_Class)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Widget has NOT been loaded from Path @ %s."), *Context, *(Widget.ToSoftObjectPath().ToString())));
			return nullptr;
		}
		return Widget_Class;
	}

	FORCEINLINE UClass* GetSafeClass(const FString& Context, bool& OutSuccess, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const
	{
		OutSuccess = false;

		if (!Widget.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString())));
			return nullptr;
		}

		if (!Widget_Class)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Widget has NOT been loaded from Path @ %s."), *Context, *(Widget.ToSoftObjectPath().ToString())));
			return nullptr;
		}

		OutSuccess = true;
		return Widget_Class;
	}

	FORCEINLINE UClass** GetClassPtr() { return &Widget_Class; }

	FORCEINLINE const TSubclassOf<UUserWidget>& GetSubclassOf() const { return Widget_SubclassOf; }

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		checkf(Widget.ToSoftObjectPath().IsValid(), TEXT("%s: FCsUserWidgetPtr.Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString()));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const
	{
		if (!Widget.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: FCsUserWidgetPtr.Widget's Path: %s is NOT Valid."), *Context, *(Widget.ToSoftObjectPath().ToString())));
			return false;
		}
		return true;
	}


};

#pragma endregion FCsUserWidget