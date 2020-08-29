// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_UserWidget.generated.h"
#pragma once

// UserWidget
#pragma region

/**
* Enum for UserWidget types, objects that extend from the class:
* UUserWidget.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidget : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidget)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidget)

struct CSUI_API EMCsUserWidget final : public TCsEnumStructMap<FECsUserWidget, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidget, FECsUserWidget, uint8)
};

class UObject;
struct FCsUIDataRootSet;

namespace NCsUserWidget
{
	typedef FECsUserWidget Type;

	CSUI_API void FromEnumSettings(const FString& Context);

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion UserWidget

// UserWidgetClass
#pragma region

/**
* Enum for UserWidget class types, classes that extend from the class:
* UUserWidget.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidgetClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidgetClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidgetClass)

struct CSUI_API EMCsUserWidgetClass : public TCsEnumStructMap<FECsUserWidgetClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidgetClass, FECsUserWidgetClass, uint8)
};

namespace NCsUserWidgetClass
{
	typedef FECsUserWidgetClass Type;

	CSUI_API void FromEnumSettings(const FString& Context);

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion UserWidgetClass

// UserWidgetPooled
#pragma region

/**
* Enum for UserWidgetPooled types, objects that implement the interface:
* ICsUserWidgetPooled.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidgetPooled : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidgetPooled)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidgetPooled)

struct CSUI_API EMCsUserWidgetPooled final : public TCsEnumStructMap<FECsUserWidgetPooled, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidgetPooled, FECsUserWidgetPooled, uint8)
};

class UObject;

namespace NCsUserWidgetPooled
{
	typedef FECsUserWidgetPooled Type;

	CSUI_API void FromEnumSettings(const FString& Context);

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion UserWidget

// UserWidgetPooledClass
#pragma region

/**
* Enum for UserWidgetPooled class types, classes that implement the interface:
* ICsUserWidgetPooled.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidgetPooledClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidgetPooledClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidgetPooledClass)

struct CSUI_API EMCsUserWidgetPooledClass : public TCsEnumStructMap<FECsUserWidgetPooledClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass, uint8)
};

namespace NCsUserWidgetPooledClass
{
	typedef FECsUserWidgetPooledClass Type;

	CSUI_API void FromEnumSettings(const FString& Context);

	CSUI_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion UserWidgetPooledClass