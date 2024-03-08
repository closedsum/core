// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Font.generated.h"

// FCsFont
#pragma region

class UFont;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFont
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataTable)
	TSoftObjectPtr<UFont> Font;

	UPROPERTY()
	int32 Font_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UFont* Font_Internal;

	FCsFont() :
		Font(nullptr),
		Font_LoadFlags(0),
		Font_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UFont asset.
	*
	* return Font
	*/
	FORCEINLINE UFont* Get() const { return Font_Internal; }

	/**
	* Get the pointer to the Hard reference to the UFont asset.
	*
	* return Font
	*/
	FORCEINLINE UFont** GetPtr() { return &Font_Internal; }

	/**
	* Get the Hard reference to the UFont asset.
	*
	* @param Context	The calling context.
	* return			Font
	*/
	FORCEINLINE UFont* GetChecked(const FString& Context) const
	{
		checkf(Font.ToSoftObjectPath().IsValid(), TEXT("%s: Font is NULL."), *Context);

		checkf(Font_Internal, TEXT("%s: Font has NOT been loaded from Path @ %s."), *Context, *(Font.ToSoftObjectPath().ToString()));

		return Font_Internal;
	}

	/**
	* Get the Hard reference to the UFont asset.
	*
	* return Font
	*/
	FORCEINLINE UFont* GetChecked() const
	{
		checkf(Font.ToSoftObjectPath().IsValid(), TEXT("FCsFont::GetChecked: Mesh is NULL."));

		checkf(Font_Internal, TEXT("FCsFont::GetChecked: Font has NOT been loaded from Path @ %s."), *(Font.ToSoftObjectPath().ToString()));

		return Font_Internal;
	}

	/**
	* Safely get the Hard reference to the UFont asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Font
	*/
	UFont* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Font.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Font is NULL."), *Context));
			return nullptr;
		}

		if (!Font_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Font has NOT been loaded from Path @ %s."), *Context, *(Font.ToSoftObjectPath().ToString())));
		}
		return Font_Internal;
	}

	/**
	* Safely get the Hard reference to the UFont asset.
	*
	* return Font
	*/
	UFont* GetSafe()
	{
		if (!Font.ToSoftObjectPath().IsValid())
			return nullptr;
		return Font_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsFont