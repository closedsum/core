// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Load.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Load.h"
#include "Library/CsLibrary_Math.h"

#include "Sound/SoundCue.h"

namespace ECsLoadCached
{
	namespace Str
	{
		CSCORE_API const FString _Internal = TEXT("_Internal");
		CSCORE_API const FString _LoadFlags = TEXT("_LoadFlags");
		CSCORE_API const FString _1P_LoadFlags = TEXT("1P_LoadFlags");
		CSCORE_API const FString _3P_LoadFlags = TEXT("3P_LoadFlags");
		CSCORE_API const FString _3P_Low_LoadFlags = TEXT("3P_Low_LoadFlags");
		CSCORE_API const FString VR_LoadFlags = TEXT("VR_LoadFlags");
		CSCORE_API const FString _C = TEXT("_C");
	}
}

// LoadFlags
EMCsLoadFlags* EMCsLoadFlags::Instance;

EMCsLoadFlags& EMCsLoadFlags::Get()
{
	if (!Instance)
		Instance = new EMCsLoadFlags();
	return *Instance;
}

namespace NCsLoadFlags
{
	namespace Ref
	{
		CSCORE_API const Type Game = EMCsLoadFlags::Get().Add(Type::Game, TEXT("Game"));
		CSCORE_API const Type Game1P = EMCsLoadFlags::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSCORE_API const Type Game3P = EMCsLoadFlags::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSCORE_API const Type Game3PLow = EMCsLoadFlags::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
		CSCORE_API const Type GameVR = EMCsLoadFlags::Get().Add(Type::GameVR, TEXT("GameVR"), TEXT("Game VR"));
		CSCORE_API const Type UI = EMCsLoadFlags::Get().Add(Type::UI, TEXT("UI"));
		CSCORE_API const Type All = EMCsLoadFlags::Get().Add(Type::All, TEXT("All"));
	}
}

// LoadFlags_Editor
EMCsLoadFlags_Editor* EMCsLoadFlags_Editor::Instance;

EMCsLoadFlags_Editor& EMCsLoadFlags_Editor::Get()
{
	if (!Instance)
		Instance = new EMCsLoadFlags_Editor();
	return *Instance;
}

namespace ECsLoadFlags_Editor
{
	namespace Ref
	{
		CSCORE_API const Type Game = EMCsLoadFlags_Editor::Get().Add(Type::Game, TEXT("Game"));
		CSCORE_API const Type Game1P = EMCsLoadFlags_Editor::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSCORE_API const Type Game3P = EMCsLoadFlags_Editor::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSCORE_API const Type Game3PLow = EMCsLoadFlags_Editor::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
		CSCORE_API const Type GameVR = EMCsLoadFlags_Editor::Get().Add(Type::GameVR, TEXT("GameVR"), TEXT("Game VR"));
		CSCORE_API const Type UI = EMCsLoadFlags_Editor::Get().Add(Type::UI, TEXT("UI"));
		CSCORE_API const Type All = EMCsLoadFlags_Editor::Get().Add(Type::All, TEXT("All"));
		CSCORE_API const Type ECsLoadFlags_Editor_MAX = EMCsLoadFlags_Editor::Get().Add(Type::ECsLoadFlags_Editor_MAX, TEXT("ECsLoadFlags_Editor_MAX"), TEXT("MAX"));
	}
}

// AssetType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsAssetType)

// LoadAssetsType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsLoadAssetsType)

// LoadAsyncOrder
#pragma region

namespace NCsLoadAsyncOrder
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsLoadAsyncOrder, None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsLoadAsyncOrder, FirstToLast, "First to Last");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsLoadAsyncOrder, Bulk);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsLoadAsyncOrder, ECsLoadAsyncOrder_MAX, "MAX");
	}
}

#pragma endregion ECsLoadAsyncOrder

// Payload
#pragma region

	// FCsPayload_Data
#pragma region

void FCsPayload_Data::Populate()
{
	Paths.Reset();

	if (!Data.IsValid())
	{
		//UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate:"));
		return;
	}

	UClass* Class = Data.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate:"));
		return;
	}
	
	UObject* Object = Class->GetDefaultObject();

	const FString ClassName = Class->GetName();

	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate:"));
		return;
	}

	// Add Data Path
	{
		FCsSoftObjectPath Path;
		Path.Path = Data.ToSoftObjectPath();
		int32 Size = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
		Path.Size.SetBytes(Size);

		Paths.Add(Path);
	}

	TArray<FSoftObjectPath>& Paths_Internal = Paths.Paths_Internal;

	UCsLibrary_Load::GetUniqueObjectPaths(Object, Class, Paths_Internal);

	// Log Paths (number and name)
	const int32 Count = Paths_Internal.Num();

	if (Count > CS_SINGLETON)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate: Populating Paths with %d Paths from %s."), Count, *ClassName);

		for (int32 I = 1; I < Count; ++I)
		{
			const FSoftObjectPath& Path = Paths_Internal[I];

			UE_LOG(LogCs, Warning, TEXT("-- [%d] [%s] has %s."), I, *ClassName, *(Path.ToString()));

			Paths.Paths.AddDefaulted();
			FCsSoftObjectPath& P = Paths.Paths.Last();

			P.Path = Path;

			UObject* O = Path.TryLoad();

			if (!O)
			{
				// LOG
				continue;
			}

			int32 Size = O->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
			P.Size.SetBytes(Size);
		}

		Paths.CalculateSize();

		UE_LOG(LogCs, Warning, TEXT("FCsPayload_Data::Populate: Populated %d Paths from %s [%s]."), Paths_Internal.Num(), *ClassName, *(Paths.Size.ToString()));
	}
}

#pragma endregion FCsPayload_Data

	// FCsPayload_DataTable
#pragma region

void FCsPayload_DataTable::Populate()
{
	Paths.Reset();

	if (!DataTable.IsValid())
	{
		//UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate:"));
		return;
	}

	UDataTable* DT = DataTable.LoadSynchronous();

	if (!DT)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate:"));
		return;
	}

	const UScriptStruct* ScriptStruct = DT->GetRowStruct();
	UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct			  = Temp;
	
	const FString StructName    = Struct->GetName();
	const FString DataTableName = DT->GetName();

	TArray<FSoftObjectPath>& Paths_Internal = Paths.Paths_Internal;

	// Add DataTable Path
	{
		FCsSoftObjectPath Path;
		Path.Path = DataTable.ToSoftObjectPath();
		int32 Size = DT->GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
		Path.Size.SetBytes(Size);

		Paths.Add(Path);
	}

	TArray<FName> RowNames;

	// All Rows
	if (bAllRows)
	{
		RowNames = DT->GetRowNames();
	}
	// Specified Rows
	else
	{
		RowNames = Rows;
	}

	// Get Paths for appropriate rows
	TArray<FSoftObjectPath> TableArray;
	TArray<FSoftObjectPath> RowArray;

	for (const FName& RowName : RowNames)
	{
		uint8* RowPtr = DT->FindRowUnchecked(RowName);

		RowArray.Reset(RowArray.Max());
		UCsLibrary_Load::GetUniqueObjectPaths(RowPtr, Struct, RowArray);

		const int32 Count = RowArray.Num();

		if (Count != CS_EMPTY)
		{
			// Log Paths (number and name)
			const FString RowNameAsString = RowName.ToString();

			UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate: Found %d Paths from %s.%s."), Count, *DataTableName, *RowNameAsString);

			FCsResourceSize Size;

			for (int32 I = 0; I < Count; ++I)
			{
				const FSoftObjectPath& Path = RowArray[I];
				UObject* Object				= Path.TryLoad();

				int32 Bytes     = 0;
				float Kilobytes = 0.0f;
				float Megabytes = 0.0f;

				if (Object)
				{
					Bytes	  = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
					Kilobytes = UCsLibrary_Math::BytesToKilobytes(Bytes);
					Megabytes = UCsLibrary_Math::BytesToMegabytes(Bytes);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate:"));
				}

				UE_LOG(LogCs, Warning, TEXT("-- [%d] [%f mb, %f kb, %d b] has %s."), I, Megabytes, Kilobytes, Bytes, *(Path.ToString()));

				Size.SetBytes(Bytes);
			}

			UE_LOG(LogCs, Warning, TEXT("-- Total: %s ."), *(Size.ToString()));

			for (const FSoftObjectPath& Path : RowArray)
			{
				const int32 Index = TableArray.AddUnique(Path);
			}
		}
	}

	// Add to master list of Paths
	for (FSoftObjectPath& Path : TableArray)
	{
		FCsSoftObjectPath P;

		P.Path = Path;

		UObject* Object = Path.TryLoad();

		if (Object)
		{
			int32 Size = Object->GetResourceSizeBytes(EResourceSizeMode::Exclusive);
			P.Size.SetBytes(Size);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate:"));
		}
		Paths.Add(P);
	}

	Paths.CalculateSize();

	UE_LOG(LogCs, Warning, TEXT("FCsPayload_DataTable::Populate: Populated %d Paths from %s [%s]."), Paths_Internal.Num(), *DataTableName, *(Paths.Size.ToString()));
}

#pragma endregion FCsPayload_DataTable

#pragma endregion Payload