// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Load.h"
// Log
#include "Utility/CsDataLog.h"

#include "CsLibrary_Load.generated.h"

namespace NCsLoad
{
	struct CSDATA_API FLibrary
	{
	public:

	// SoftObjectPath
	#pragma region
	public:

		static FName GetAssetPathName(const FSoftObjectPath& Path);

	#pragma endregion SoftObjectPath
	};
}
	
class ULevel;
class UDataTable;

UCLASS()
class CSDATA_API UCsLibrary_Load : public UObject
{
	GENERATED_UCLASS_BODY()

// Class
#pragma region

	template<typename T>
	static UClass* LoadAssetClass(const FString& AssetPath)
	{
		const FSoftObjectPath AssetRef = FSoftObjectPath(AssetPath);
		TSoftClassPtr<T> AssetClass	   = TSoftClassPtr<T>(AssetRef);

		if (UClass* Class = AssetClass.LoadSynchronous())
		{
			return Class;
		}

		//UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Load::GetAssetClass: Failed to find Asset at: %s. It is possible it was deleted or moved."), *AssetPath);
		return nullptr;
	}

	template<typename T>
	static void LoadTSoftClassPtr(const FString& MemberName, TSoftClassPtr<T>& SoftClassPtr, T*& Internal, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = SoftClassPtr.ToString();

		if (AssetName  == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal &&
			SoftClassPtr.IsValid() && SoftClassPtr.Get() &&
			Internal == SoftClassPtr.Get()->template GetDefaultObject<T>())
		{
			//UE_LOG(LogLoad, Warning, TEXT("URsLibrary_Load::LoadTSoftClassPtr (%s): Possibly trying to load: %s and it is already loaded."), *MemberName, *AssetErrorMessageType);
			return;
		}

		if (SoftClassPtr.IsValid() && SoftClassPtr.Get())
		{
			Internal = SoftClassPtr.Get()->template GetDefaultObject<T>();
		}
		else
		{
			if (UClass* DataClass = SoftClassPtr.LoadSynchronous())
			{
				Internal = DataClass->GetDefaultObject<T>();
			}
			else
			{
				const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Failed to load: %s at: %s."), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTSoftClassPtr(const FString& MemberName, TSoftClassPtr<T>*& SoftClassPtr, T*& Internal, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = SoftClassPtr->ToString();

		if (AssetName == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal &&
			SoftClassPtr->IsValid() && SoftClassPtr->Get() &&
			Internal == SoftClassPtr->Get()->template GetDefaultObject<T>())
		{
			//UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Possibly trying to load: %s and it is already loaded."), *MemberName, *AssetErrorMessageType);
			return;
		}

		if (SoftClassPtr->IsValid() && SoftClassPtr->Get())
		{
			Internal = SoftClassPtr->Get()->template GetDefaultObject<T>();
		}
		else
		{
			if (UClass* DataClass = SoftClassPtr->LoadSynchronous())
			{
				Internal = DataClass->GetDefaultObject<T>();
			}
			else
			{
				const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Failed to load: %s at: %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTSoftClassPtr(const FString &MemberName, TSoftClassPtr<T> &AssetSubclassOf, TWeakObjectPtr<T> &Internal, const FString &AssetErrorMessageType)
	{
		const FString& AssetName = AssetSubclassOf.ToString();

		if (AssetName == TEXT(""))
		{
			Internal = nullptr;
			return;
		}

		if (Internal.IsValid() && Internal.Get() &&
			AssetSubclassOf.IsValid() && AssetSubclassOf.Get() &&
			Internal == AssetSubclassOf.Get()->template GetDefaultObject<T>())
		{
			UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Possibly trying to load %s and it is already loaded"), *MemberName, *AssetErrorMessageType);
			return;
		}

		if (AssetSubclassOf.IsValid() && AssetSubclassOf.Get())
		{
			Internal = AssetSubclassOf.Get()->template GetDefaultObject<T>();
		}
		else
		{
			if (UClass* DataClass = AssetSubclassOf.LoadSynchronous())
			{
				Internal = DataClass->GetDefaultObject<T>();
			}
			else
			{
				const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Failed to load %s at %s"), *MemberName, *AssetErrorMessageType, *AssetDescription);

				Internal = nullptr;
			}
		}
	}

	template<typename T>
	static void LoadTSoftClassPtr(TSoftClassPtr<T> &AssetSubclassOf, T* &OutAsset, const FString &AssetErrorMessageType)
	{
		OutAsset = nullptr;

		const FString& AssetName = AssetSubclassOf.ToString();

		if (AssetName == TEXT(""))
			return;

		if (AssetSubclassOf.IsValid() && AssetSubclassOf.Get())
		{
			OutAsset = AssetSubclassOf.Get()->template GetDefaultObject<T>();
		}
		else
		{
			if (UClass* DataClass = AssetSubclassOf.LoadSynchronous())
			{
				OutAsset = DataClass->GetDefaultObject<T>();
			}
			else
			{
				const FString AssetDescription = TEXT("Blueprint'") + AssetName + TEXT("'");

				UE_LOG(LogLoad, Warning, TEXT("UCsLibrary_Load::LoadTSoftClassPtr (%s): Failed to load %s at %s"), *AssetErrorMessageType, *AssetDescription);
			}
		}
	}

#pragma endregion Class

// Object
#pragma region

	template<typename T>
	static T* LoadAssetObject(const FString& AssetPath)
	{

	}

#pragma endregion Object

// DataTable
#pragma region
public:

	static void GetDataTables(const void* StructValue, UStruct* const& Struct, TMap<FName, UDataTable*>& OutDataTableMap);
	static void GetDataTables(ULevel* Level, TMap<FName, UDataTable*>& OutDataTableMap);

#pragma endregion DataTable

// ObjectPath
#pragma region
public:

	// Soft
#pragma region
public:

	static void GetSoftObjectPaths(const void* StructValue, UStruct* const& Struct, TArray<FSoftObjectPath>& OutObjectPaths);
	static void GetSoftObjectPaths(const void* StructValue, UStruct* const& Struct, TMap<FName, FSoftObjectPath>& OutObjectPathMap);
	static void GetSoftObjectPaths(ULevel* Level, TMap<FName, FSoftObjectPath>& OutObjectPathMap);

#pragma endregion Soft

#pragma endregion ObjectPath

// Load
#pragma region
public:

	static bool CanLoad(void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadSoftClassProperty(FSoftClassProperty* SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArraySoftClassProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadSoftObjectProperty(FSoftObjectProperty* SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArraySoftObjectProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadClassProperty(FClassProperty* ClassProperty, void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArrayClassProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArrayObjectProperty(FArrayProperty* ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArrayStructProperty(FArrayProperty* ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes);

	/**
	*
	*
	* @param StructValue
	* @param Struct
	* @param LoadFlags
	* @param LoadCodes
	*/
	static void LoadStruct(void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes);

	/**
	*
	*
	* @param DataTable
	* @param LoadFlags
	* @param LoadCodes
	*/
	static void LoadDataTable(UDataTable* DataTable, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadDataTableRowChecked(const FString& Context, UDataTable* DataTable, const FName& RowName, const int32& LoadFlags, const int32& LoadCodes);

	static bool SafeLoadDataTableRow(const FString& Context, UDataTable* DataTable, const FName& RowName, const int32& LoadFlags, const int32& LoadCodes, void(*Log)(const FString&) = &NCsData::FLog::Warning);

	static UObject* LoadSoftClassPtrChecked(const FString& Context, const TSoftClassPtr<UObject>& SoftClass, const int32& LoadFlags, const int32& LoadCodes);

#pragma endregion Load

// Unload
#pragma region
public:

	static void UnloadSoftClassProperty(FSoftClassProperty* SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes);

	static void UnloadArraySoftClassProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes);

	static void UnloadSoftObjectProperty(FSoftObjectProperty* SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes);

	static void UnloadArraySoftObjectProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes);

	static void UnloadArrayObjectProperty(FArrayProperty* ArrayProperty, void* StructValue, const int32& UnloadCodes);

	static void UnloadArrayStructProperty(FArrayProperty* ArrayProperty, void* StructValue, const int32& UnloadCodes);

	/**
	*
	*
	* @param StructValue
	* @param Struct
	* @param UnloadCodes
	*/
	static void UnloadStruct(void* StructValue, UStruct* const& Struct, const int32& UnloadCodes);

	static void UnloadStruct(void* StructValue, UStruct* const& Struct);

	/**
	*
	*
	* @param DataTable
	* @param UnloadCodes
	*/
	static void UnloadDataTable(UDataTable* DataTable, const int32& UnloadCodes);

#pragma endregion Unload

// Default Object
#pragma region

	static UObject* GetDefaultObjectChecked(const FString& Context, const TSubclassOf<UObject>& SubclassOf);

	template<typename T>
	static T* GetDefaultObjectChecked(const FString& Context, const TSubclassOf<UObject>& SubclassOf)
	{
		UObject* DOb = GetDefaultObjectChecked(Context, SubclassOf);

		T* O = Cast<T>(DOb);

		checkf(O, TEXT("%s: Failed to cast DefaultObject: %s to type T."), *Context, *(DOb->GetName()));

		return O;
	}

#pragma endregion Default Object
};