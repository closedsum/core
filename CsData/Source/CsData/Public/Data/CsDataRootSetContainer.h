// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsDataLog.h"

#include "CsDataRootSetContainer.generated.h"

// FCsDataRootSetContainer
#pragma region

class UObject;
class UClass;
class ICsGetDataRootSet;

USTRUCT(BlueprintType)
struct CSDATA_API FCsDataRootSetContainer
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "CsData|Load", EditAnywhere, meta = (MustImplement = "/Script/CsData.CsGetDataRootSet"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsData|Load")
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsData|Load")
	UClass* Data_Class;

	ICsGetDataRootSet* Interface;

	FCsDataRootSetContainer() :
		Data(nullptr),
		Data_Internal(nullptr),
		Data_Class(nullptr),
		Interface(nullptr)
	{
	}

	FORCEINLINE UObject* GetObject() const { return Data_Internal;}

	template<typename T>
	FORCEINLINE T* GetObject() const { return Cast<T>(GetObject()); }

	FORCEINLINE UObject* GetObjectChecked(const FString& Context) const
	{
		checkf(Data_Internal, TEXT("%s: Data_Internal is NULL."), *Context);
		return Data_Internal;
	}

	template<typename T>
	FORCEINLINE UObject* GetObjectChecked(const FString& Context) const
	{
		UObject* O = GetObjectChecked(Context);
		T* Other   = Cast<T>(O);

		checkf(Other, TEXT("%s: Data_Internal is NOT of type: %s."), *Context, *(T::StaticClass()->GetName()));
		return Other;
	}

	FORCEINLINE UObject* GetSafeObject(const FString& Context, void(*Log)(const FString&) = &NCsData::FLog::Warning) const
	{
		if (!Data_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%: Data_Internal is NULL."), *Context));
			return nullptr;
		}
		return Data_Internal;
	}

	FORCEINLINE UClass* GetClass() const { return Data_Class; }

	FORCEINLINE ICsGetDataRootSet* Get() const { return Interface; }

	FORCEINLINE ICsGetDataRootSet* GetChecked(const FString& Context) const 
	{
		checkf(Interface, TEXT("%s: Interface is NULL."), *Context);
		return Interface;
	}

	template<typename T>
	FORCEINLINE T* GetChecked(const FString& Context) const
	{
		T* Slice = Cast<T>(Data_Internal);

		checkf(Slice, TEXT("%s: Failed to cast Data_Internal to type: T."), *Context);

		return Slice;
	}

	FORCEINLINE ICsGetDataRootSet* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsData::FLog::Warning) const 
	{
		if (!Interface)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Interface is NULL. Class: %s does NOT implement the interface: ICsGetDataRootSet."), *Context));
			return nullptr;
		}
		return Interface;
	}
};

#pragma endregion FCsDataRootSetContainer