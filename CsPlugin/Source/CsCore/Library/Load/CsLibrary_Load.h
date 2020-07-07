// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Library/Load/CsTypes_Library_Load.h"
#include "CsLibrary_Load.generated.h"

class ULevel;
class UDataTable;

UCLASS()
class CSCORE_API UCsLibrary_Load : public UObject
{
	GENERATED_UCLASS_BODY()

// Class
#pragma region

	template<typename T>
	static UClass* LoadAssetClass(const FString& AssetPath)
	{
		const FStringAssetReference AssetRef = FStringAssetReference(AssetPath);
		TSoftClassPtr<T> AssetClass			 = TSoftClassPtr<T>(AssetRef);

		if (UClass* Class = AssetClass.LoadSynchronous())
		{
			return Class;
		}

		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Load::GetAssetClass: Failed to find Asset at: %s. It is possible it was deleted or moved."), *AssetPath);
		return nullptr;
	}

	template<typename T>
	static void LoadTSoftClassPtr(const FString& MemberName, TSoftClassPtr<T>& SoftClassPtr, T*& Internal, const FString& AssetErrorMessageType)
	{
		const FString& AssetName = SoftClassPtr.ToString();

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

		// (AssetName == TEXT(""))
		if (AssetName == NCsCached::Str::Empty)
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

	static bool GetSoftObjectPaths_SoftObjectPath(UProperty* Property, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetSoftObjectPaths& Result);
	static bool GetSoftObjectPaths_Array_SoftObjectPath(UArrayProperty* ArrayProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetSoftObjectPaths& Result);

	static void GetSoftObjectPaths(const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetSoftObjectPaths& Result);

#pragma endregion Soft

#pragma endregion ObjectPath

// Load
#pragma region
public:

	static bool CanLoad(void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadSoftClassProperty(USoftClassProperty* SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArraySoftClassProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadSoftObjectProperty(USoftObjectProperty* SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArraySoftObjectProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadClassProperty(UClassProperty* ClassProperty, void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArrayClassProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArrayObjectProperty(UArrayProperty* ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes);

	static void LoadArrayStructProperty(UArrayProperty* ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes);

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

#pragma endregion Load

// Unload
#pragma region
public:

	static void UnloadSoftClassProperty(USoftClassProperty* SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes);

	static void UnloadArraySoftClassProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes);

	static void UnloadSoftObjectProperty(USoftObjectProperty* SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes);

	static void UnloadArraySoftObjectProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes);

	static void UnloadArrayObjectProperty(UArrayProperty* ArrayProperty, void* StructValue, const int32& UnloadCodes);

	static void UnloadArrayStructProperty(UArrayProperty* ArrayProperty, void* StructValue, const int32& UnloadCodes);


	/**
	*
	*
	* @param StructValue
	* @param Struct
	* @param UnloadCodes
	*/
	static void UnloadStruct(void* StructValue, UStruct* const& Struct, const int32& UnloadCodes);

	/**
	*
	*
	* @param DataTable
	* @param UnloadCodes
	*/
	static void UnloadDataTable(UDataTable* DataTable, const int32& UnloadCodes);

#pragma endregion Unload

// References
#pragma region
public:

	static void GetReferencesReport_ClassProperty(UClassProperty* ClassProperty, const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);
	static void GetReferencesReport_ObjectProperty(UObjectProperty* ObjectProperty, const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);
	static void GetReferencesReport_SoftClassProperty(USoftClassProperty* SoftClassProperty, const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);
	static void GetReferencesReport_SoftObjectProperty(USoftObjectProperty* SoftObjectProperty, const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);

	static void GetReferencesReport(const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport);

#pragma endregion References
};