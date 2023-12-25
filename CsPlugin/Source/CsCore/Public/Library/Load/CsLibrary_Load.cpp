// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Load/CsLibrary_Load.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Sound
#include "Sound/SoundCue.h"
// FX
#include "Particles/ParticleSystem.h"
// Data
#include "Data/CsData.h"
#include "Data/CsScriptData.h"
#include "Engine/DataTable.h"
// Material
#include "Materials/Material.h"
#include "Materials/MaterialExpression.h"
#include "Materials/MaterialFunction.h"
// Animation
#include "Animation/AnimNotifies/AnimNotify.h"
// Graph
#include "EdGraph/EdGraphNode.h"
// Blueprint
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/BlueprintCore.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
// Class
#include "UObject/Class.h"

namespace NCsLoad
{
	// SoftObjectPath
	#pragma region

	FName FLibrary::GetAssetPathName(const FSoftObjectPath& Path)
	{
		return *(Path.ToString());
	}

	#pragma endregion SoftObjectPath
}

UCsLibrary_Load::UCsLibrary_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// DataTable
#pragma region

void UCsLibrary_Load::GetDataTables(const void* StructValue, UStruct* const& Struct, TMap<FName, UDataTable*>& OutDataTableMap)
{
	// Iterate through Properties
	for (TPropertyValueIterator<FProperty> It(Struct, StructValue); It; ++It)
	{
		FProperty* Property		  = It.Key();
		const void* PropertyValue = It.Value();

		// TSoftObjectPtr
		if (const FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
		{
			if (const TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<const TSoftObjectPtr<UObject>*>(PropertyValue))
			{
				const FSoftObjectPath& Path = Ptr->ToSoftObjectPath();

				if (Path.IsValid())
				{
					UObject* Object = Path.TryLoad();

					if (UDataTable* DataTable = Cast<UDataTable>(Object))
					{
						OutDataTableMap.FindOrAdd(DataTable->GetFName()) = DataTable;
					}
				}
			}
			continue;
		}
		// ObjectProperty
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			void* Value = const_cast<void*>(PropertyValue);

			if (UObject** Ptr = reinterpret_cast<UObject**>(Value))
			{
				if (UDataTable* DataTable = Cast<UDataTable>(*Ptr))
				{
					OutDataTableMap.FindOrAdd(DataTable->GetFName()) = DataTable;

					GetDataTables(DataTable, UDataTable::StaticClass(), OutDataTableMap);
				}
			}
			continue;
		}
	}
	// Iterate through Functions
	for (UFunction* Function : TFieldRange<UFunction>(Struct))
	{
		if (Function->GetName().StartsWith(TEXT("ExecuteUbergraph")))
			continue;

		GetDataTables(Function, Function->GetClass(), OutDataTableMap);
	}
}

void UCsLibrary_Load::GetDataTables(ULevel* Level, TMap<FName, UDataTable*>& OutDataTableMap)
{
	for (AActor* Actor : Level->Actors)
	{
		if (!Actor)
			continue;

		GetDataTables(Actor, Actor->GetClass(), OutDataTableMap);
	}
}

#pragma endregion DataTable

// ObjectPath
#pragma region

	// Soft
#pragma region

void UCsLibrary_Load::GetSoftObjectPaths(const void* StructValue, UStruct* const& Struct, TArray<FSoftObjectPath>& OutObjectPaths)
{
	for (TPropertyValueIterator<FProperty> It(Struct, StructValue); It; ++It)
	{
		FProperty* Property		  = It.Key();
		const void* PropertyValue = It.Value();

		// TSoftClassPtr
		if (const FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			if (const TSoftClassPtr<UObject>* Ptr = reinterpret_cast<const TSoftClassPtr<UObject>*>(PropertyValue))
			{
				const FSoftObjectPath& Path = Ptr->ToSoftObjectPath();

				if (Path.IsValid())
				{
					OutObjectPaths.Add(Path);

					// TODO: Load SoftClassPtr and GetObjectPaths from that. Have an optional enum for recursive look up with load
				}
			}
			continue;
		}
		// TSoftObjectPtr
		if (const FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
		{
			if (const TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<const TSoftObjectPtr<UObject>*>(PropertyValue))
			{
				const FSoftObjectPath& Path = Ptr->ToSoftObjectPath();

				if (Path.IsValid())
					OutObjectPaths.Add(Path);
			}
			continue;
		}
		// Struct
		if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			// SoftClassPath
			if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
			{
				if (const FSoftClassPath* Ptr = reinterpret_cast<const FSoftClassPath*>(PropertyValue))
				{
					if (Ptr->IsValid())
						OutObjectPaths.Add(*Ptr);
				}
				continue;
			}
			// SoftObjectPath
			if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
			{
				if (const FSoftObjectPath* Ptr = reinterpret_cast<const FSoftObjectPath*>(PropertyValue))
				{
					if (Ptr->IsValid())
						OutObjectPaths.Add(*Ptr);
				}
				continue;
			}
			continue;
		}
		// Array
		if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
		{
			// TODO: Look at FScriptArray, FScriptArrayHelper
			continue;
		}
		// Map
		if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
		{
			// TODO: Look at FScriptArray, FScriptArrayHelper
			continue;
		}
	}

	/*
	for (TFieldIterator<UProperty> It(InClass); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(*It))
		{
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(*It))
		{
			// USouncCue
			if (TryGetObjectPathFromSoftObjectProperty<USoundCue>(SoftObjectProperty, InObject, InClass, OutObjectPaths))
				continue;
			// UParticleSystem
			if (TryGetObjectPathFromSoftObjectProperty<UParticleSystem>(SoftObjectProperty, InObject, InClass, OutObjectPaths))
				continue;
			// UDataTable
			if (TryGetObjectPathFromSoftObjectProperty<UDataTable>(SoftObjectProperty, InObject, InClass, OutObjectPaths))
				continue;
			continue;
		}
	}
	*/
}

void UCsLibrary_Load::GetSoftObjectPaths(const void* StructValue, UStruct* const& Struct, TMap<FName, FSoftObjectPath>& OutObjectPathMap)
{
	// Iterate through Properties
	for (TPropertyValueIterator<FProperty> It(Struct, StructValue); It; ++It)
	{
		FProperty* Property		  = It.Key();
		const void* PropertyValue = It.Value();

		// TSoftClassPtr
		if (const FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			if (const TSoftClassPtr<UObject>* Ptr = reinterpret_cast<const TSoftClassPtr<UObject>*>(PropertyValue))
			{
				const FSoftObjectPath& Path = Ptr->ToSoftObjectPath();

				if (Path.IsValid())
				{
					OutObjectPathMap.FindOrAdd(NCsLoad::FLibrary::GetAssetPathName(Path)) = Path;
					// TODO: Load SoftClassPtr and GetObjectPaths from that. Have an optional enum for recursive look up with load
				}
			}
			continue;
		}
		// TSoftObjectPtr
		if (const FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
		{
			if (const TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<const TSoftObjectPtr<UObject>*>(PropertyValue))
			{
				const FSoftObjectPath& Path = Ptr->ToSoftObjectPath();

				if (Path.IsValid())
					OutObjectPathMap.FindOrAdd(NCsLoad::FLibrary::GetAssetPathName(Path)) = Path;
			}
			continue;
		}
		// Struct
		if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			// SoftClassPath
			if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
			{
				if (const FSoftClassPath* Ptr = reinterpret_cast<const FSoftClassPath*>(PropertyValue))
				{
					if (Ptr->IsValid())
						OutObjectPathMap.FindOrAdd(NCsLoad::FLibrary::GetAssetPathName(*Ptr)) = *Ptr;
				}
				continue;
			}
			// SoftObjectPath
			if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
			{
				if (const FSoftObjectPath* Ptr = reinterpret_cast<const FSoftObjectPath*>(PropertyValue))
				{
					if (Ptr->IsValid())
						OutObjectPathMap.FindOrAdd(NCsLoad::FLibrary::GetAssetPathName(*Ptr)) = *Ptr;
				}
				continue;
			}
			continue;
		}
		// Array
		if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
		{
			// TODO: Look at FScriptArray, FScriptArrayHelper
			continue;
		}
		// Map
		if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
		{
			// TODO: Look at FScriptArray, FScriptArrayHelper
			continue;
		}
	}
	// Iterate through Functions
	for (UFunction* Function : TFieldRange<UFunction>(Struct))
	{
		if (Function->GetName().StartsWith(TEXT("ExecuteUbergraph")))
			continue;

		GetSoftObjectPaths(Function, Function->GetClass(), OutObjectPathMap);
	}
}

void UCsLibrary_Load::GetSoftObjectPaths(ULevel* Level, TMap<FName, FSoftObjectPath>& OutObjectPathMap)
{
	for (AActor* Actor : Level->Actors)
	{
		if (!Actor)
			continue;

		GetSoftObjectPaths(Actor, Actor->GetClass(), OutObjectPathMap);
	}
}

bool UCsLibrary_Load::GetSoftObjectPaths_SoftObjectPath(FProperty* Property, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetSoftObjectPaths& Result)
{
	FSoftObjectPath Path;
	FString StructName = TEXT("");
	bool DoRecursion = false;

	// TSoftClassPtr
	if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
	{
		if (const FSoftObjectPtr* Member = SoftClassProperty->GetPropertyValuePtr_InContainer(StructValue))
		{
			Path = Member->ToSoftObjectPath();
		}
		StructName  = SoftClassProperty->MetaClass->GetName();
		DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetClass);
	}
	// TSoftObjectPtr
	else
	if (FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
	{
		if (const FSoftObjectPtr* Member = SoftObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
		{
			Path = Member->ToSoftObjectPath();
		}
		StructName = SoftObjectProperty->PropertyClass->GetName();
		DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetObject);
	}
	// Struct
	else
	if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
	{
		// SoftClassPath
		if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
		{
			const FSoftClassPath* Ptr = StructProperty->ContainerPtrToValuePtr<FSoftClassPath>(StructValue);
			Path = *Ptr;
			DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetClass);
		}
		// SoftObjectPath
		else
		if (StructProperty->Struct == TBaseStructure<FSoftObjectPath>::Get())
		{
			const FSoftObjectPath* Ptr = StructProperty->ContainerPtrToValuePtr<FSoftObjectPath>(StructValue);
			Path = *Ptr;
			DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetObject);
		}
		StructName = StructProperty->Struct->GetName();
	}

	if (!Path.IsValid())
		return false;

	const FString PropertyName = Property->GetName();
	const FString MemberPath   = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

	FCsLibraryLoad_MemberInfo MemberInfo;

	MemberInfo.SetName(PropertyName);
	MemberInfo.SetPath(MemberPath);
	MemberInfo.SetType(StructName);

	Result.Paths.Add(Path);
	Result.PathByMemberInfoMap.Add(MemberInfo, Path);
	Result.MemberInfosByPathMap.FindOrAdd(Path).Add(MemberInfo);

	if (DoRecursion)
	{
		if (UObject* Object = Path.TryLoad())
		{
			GetSoftObjectPaths(Object, Object->GetClass(), PropertyName, Result);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("GetSoftObjectPaths_SoftObjectPath: Failed to Load Object."));
			UE_LOG(LogCs, Warning, TEXT("- Asset: %s @ %s"), *(Path.GetAssetName()), *(Path.GetAssetPathString()));
			UE_LOG(LogCs, Warning, TEXT("- Member: %s"), *(MemberInfo.ToString()));
		}
	}
	return true;
}

bool UCsLibrary_Load::GetSoftObjectPaths_Array_SoftObjectPath(FArrayProperty* ArrayProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetSoftObjectPaths& Result)
{
	FString StructName = TEXT("");
	bool DoRecursion = false;

	// TSoftClassPtr
	if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
	{
		StructName  = SoftClassProperty->MetaClass->GetName();
		DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetClass);
	}
	// TSoftObjectPtr
	else
	if (FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner))
	{
		StructName  = SoftObjectProperty->PropertyClass->GetName();
		DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetObject);
	}
	// Struct
	else
	if (FStructProperty* StructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
	{
		// SoftClassPath
		if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
		{
			StructName  = StructProperty->Struct->GetName();
			DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetClass);
		}
		// SoftObjectPath
		else
		if (StructProperty->Struct == TBaseStructure<FSoftObjectPath>::Get())
		{
			StructName  = StructProperty->Struct->GetName();
			DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetObject);
		}
		else
		{
			return false;
		}
	}

	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FSoftObjectPath Path;

		// TSoftClassPtr
		if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
		{
			TSoftClassPtr<UObject>* Ptr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));
			Path						= Ptr->ToSoftObjectPath();
		}
		// TSoftObjectPtr
		else
		if (FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner))
		{
			TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<TSoftObjectPtr<UObject>*>(Helper.GetRawPtr(I));
			Path						 = Ptr->ToSoftObjectPath();
		}
		// Struct
		else
		if (FStructProperty* StructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
		{
			// SoftClassPath
			if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
			{
				FSoftClassPath* Ptr = reinterpret_cast<FSoftClassPath*>(Helper.GetRawPtr(I));
				Path				= *Ptr;
			}
			// SoftObjectPath
			else
			if (StructProperty->Struct == TBaseStructure<FSoftObjectPath>::Get())
			{
				FSoftClassPath* Ptr = reinterpret_cast<FSoftClassPath*>(Helper.GetRawPtr(I));
				Path				= *Ptr;
			}
		}

		if (!Path.IsValid())
			continue;

		const FString PropertyName = ArrayProperty->GetName();
		const FString MemberPath   = FString::Printf(TEXT("%s.%s[%d]"), *OuterName, *PropertyName, I);

		FCsLibraryLoad_MemberInfo MemberInfo;

		MemberInfo.SetName(PropertyName);
		MemberInfo.SetPath(MemberPath);
		MemberInfo.SetType(StructName);

		Result.Paths.Add(Path);
		Result.PathByMemberInfoMap.Add(MemberInfo, Path);
		Result.MemberInfosByPathMap.FindOrAdd(Path).Add(MemberInfo);

		if (DoRecursion)
		{
			if (UObject* Object = Path.TryLoad())
			{
				GetSoftObjectPaths(Object, Object->GetClass(), PropertyName, Result);
			}
		}
	}
	return true;
}

void UCsLibrary_Load::GetSoftObjectPaths(const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetSoftObjectPaths& Result)
{
	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		FProperty* Property = CastField<FProperty>(*It);

		const FString PropertyName = Property->GetName();

		// TSoftClassPtr | TSoftObjectPtr | FSoftClassPath | FSoftObjectPath
		if (GetSoftObjectPaths_SoftObjectPath(Property, StructValue, OuterName, Result))
			continue;

		// Class
		if (FClassProperty* ClassProperty = CastField<FClassProperty>(Property))
		{
			if (CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetClass))
			{
				UObject* const* Object = ClassProperty->ContainerPtrToValuePtr<UObject*>(StructValue);

				GetSoftObjectPaths(*Object, (*Object)->GetClass(), PropertyName, Result);
			}
			continue;
		}
		// Object
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			if (CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetObject))
			{
				UObject* const* Object = ObjectProperty->ContainerPtrToValuePtr<UObject*>(StructValue);

				GetSoftObjectPaths(*Object, (*Object)->GetClass(), PropertyName, Result);
			}
			continue;
		}
		// Struct
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			if (StructProperty->ArrayDim == CS_SINGLETON)
			{
				const uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue);

				const FString MemberPath = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

				GetSoftObjectPaths(Value, StructProperty->Struct, MemberPath, Result);
			}
			else
			{
				for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
				{
					const uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I);

					const FString ArrayPropertyPath = FString::Printf(TEXT("%s.%s[%d]"), *OuterName, *PropertyName, I);

					GetSoftObjectPaths(Value, StructProperty->Struct, ArrayPropertyPath, Result);
				}
			}
			continue;
		}
		// Array
		if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*It))
		{
			// TSoftClassPtr | TSoftObjectPtr | FSoftClassPath | FSoftObjectPath
			if (GetSoftObjectPaths_Array_SoftObjectPath(ArrayProperty, StructValue, OuterName, Result))
				continue;

			// Struct
			if (FStructProperty* StructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
			{
				FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

				const int32 Count = Helper.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					uint8* Ptr = Helper.GetRawPtr(I);

					const FString ArrayPropertyPath = FString::Printf(TEXT("%s.%s[%d]"), *OuterName, *PropertyName, I);

					GetSoftObjectPaths(Ptr, StructProperty->Struct, ArrayPropertyPath, Result);
				}
				continue;
			}
			continue;
		}	
	}
}

#pragma endregion Soft

void UCsLibrary_Load::GetObjectPaths_Class_Internal(UClass* Class, NCsLoad::FGetObjectPaths& OutPaths)
{
	const bool ValidClass = Class->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint);

	FSoftClassPath ClassPath(Class);
	ClassPath.SetPath(ClassPath.GetAssetPathString());
	
	const bool ValidName = !ClassPath.GetAssetName().StartsWith(TEXT("Default__"));

	const bool ValidPathRoot = !ClassPath.GetAssetPathString().StartsWith(TEXT("/Temp")) &&
							   !ClassPath.GetAssetPathString().StartsWith(TEXT("/Script"));

	if (ValidClass &&
		ValidName &&
		ValidPathRoot)
	{
		OutPaths.AddPath(ClassPath);
	}

	if (ValidClass)
	{
		if (!OutPaths.HasVisitedPointer(Class->GetFName(), Class))
		{
			OutPaths.VisitPointer(Class->GetFName(), Class);

			GetObjectPaths_Internal(Class->GetDefaultObject(), Class, OutPaths);
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_ClassProperty(FClassProperty* ClassProperty, const void* StructValue, NCsLoad::FGetObjectPaths& OutPaths)
{
	if (UObject* const* Ptr = ClassProperty->ContainerPtrToValuePtr<UObject*>(StructValue))
	{
		if (const UObject* Object = *Ptr)
		{
			UClass* Class = const_cast<UClass*>(Cast<UClass>(Object));

			GetObjectPaths_ClassProperty_Internal(Class, Class, OutPaths);
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_ClassProperty_Internal(UClass* MetaClass, const UObject* Object, NCsLoad::FGetObjectPaths& OutPaths)
{
	const bool ValidClass = MetaClass->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint);

	const UClass* Class = Cast<UClass>(Object);

	if (ValidClass)
	{
		FSoftClassPath ClassPath(Class);
		ClassPath.SetPath(ClassPath.GetAssetPathString());

		const bool ValidPathRoot = !ClassPath.GetAssetPathString().StartsWith(TEXT("/Temp")) &&
								   !ClassPath.GetAssetPathString().StartsWith(TEXT("/Script"));

		if (ValidPathRoot)
		{
			OutPaths.AddPath(ClassPath);
		}
	}

	if (!MetaClass->HasAnyClassFlags(EClassFlags::CLASS_Abstract))
	{
		if (!OutPaths.HasVisitedPointer(MetaClass->GetFName(), Class))
		{
			OutPaths.VisitPointer(MetaClass->GetFName(), Class);

			GetObjectPaths_Internal(Class->GetDefaultObject(), const_cast<UClass*>(Class), OutPaths);
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_ObjectProperty(FObjectProperty* ObjectProperty, const void* StructValue, NCsLoad::FGetObjectPaths& OutPaths)
{
	if (UObject* const* Ptr = ObjectProperty->ContainerPtrToValuePtr<UObject*>(StructValue))
	{
		if (const UObject* Object = *Ptr)
		{
			GetObjectPaths_ObjectProperty_Internal(ObjectProperty->PropertyClass, Object, OutPaths);
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_ObjectProperty_Internal(UClass* PropertyClass, const UObject* Object, NCsLoad::FGetObjectPaths& OutPaths)
{
	const bool ValidClass = PropertyClass->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint) ||
							PropertyClass == UDataTable::StaticClass() ||
							PropertyClass->IsChildOf<USoundBase>() ||
							PropertyClass->IsChildOf<UAnimNotify>() ||
							PropertyClass->ImplementsInterface(UInterface_AssetUserData::StaticClass());
		
	if (ValidClass)
	{
		FSoftObjectPath ObjectPath(Object);
		ObjectPath.SetPath(ObjectPath.GetAssetPathString());

		const bool ValidName = !ObjectPath.GetAssetName().StartsWith(TEXT("Default__"));

		const bool ValidPathRoot = !ObjectPath.GetAssetPathString().StartsWith(TEXT("/Temp")) &&
									!ObjectPath.GetAssetPathString().StartsWith(TEXT("/Script"));

		if (ValidName &&
			ValidPathRoot)
		{
			OutPaths.AddPath(ObjectPath);
		}
	}
			
	// Subobjects

		// Ignore UFunction and UMaterialFunctionInterface as getting subobjects have some thread / resource contention issues
	if (!PropertyClass->IsChildOf<UFunction>() &&
		!PropertyClass->IsChildOf<UMaterialFunctionInterface>())
	{
		TArray<UObject*> OutDefaultSubobjects;
		const_cast<UObject*>(Object)->GetDefaultSubobjects(OutDefaultSubobjects);

		for (UObject* O : OutDefaultSubobjects)
		{
			if (!OutPaths.HasVisitedPointer(O->GetClass()->GetFName(), O))
			{
				OutPaths.VisitPointer(O->GetClass()->GetFName(), O);

				GetObjectPaths_Internal(O, O->GetClass(), OutPaths);
			}
		}
	}

	if (ValidClass ||
		!PropertyClass->HasAnyClassFlags(EClassFlags::CLASS_Abstract))
	{
		// DataTable
		if (PropertyClass == UDataTable::StaticClass())
		{
			const UDataTable* DataTable = Cast<UDataTable>(Object);
					
			// Check each row for any Object Paths
			const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
			UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
			UStruct* const Struct			  = Temp;

			TArray<FName> RowNames = DataTable->GetRowNames();

			for (const FName& RowName : RowNames)
			{
				uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

				GetObjectPaths_Internal(RowPtr, Struct, OutPaths);
			}
		}
		else
		{
			if (!OutPaths.HasVisitedPointer(PropertyClass->GetFName(), Object))
			{
				OutPaths.VisitPointer(PropertyClass->GetFName(), Object);

				GetObjectPaths_Internal(Object, Object->GetClass(), OutPaths);
			}
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_SoftClassProperty(FSoftClassProperty* SoftClassProperty, const void* StructValue, NCsLoad::FGetObjectPaths& OutPaths)
{
	if (const FSoftObjectPtr* Ptr = SoftClassProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		const FSoftObjectPath ObjectPath = Ptr->ToSoftObjectPath();

		if (ObjectPath.IsValid())
		{
			UObject* O = Ptr->LoadSynchronous();

			if (UClass* Class = Cast<UClass>(O))
			{
				GetObjectPaths_ClassProperty_Internal(Class, Class, OutPaths);
			}
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_SoftObjectProperty(FSoftObjectProperty* SoftObjectProperty, const void* StructValue, NCsLoad::FGetObjectPaths& OutPaths)
{
	if (const FSoftObjectPtr* Ptr = SoftObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		const FSoftObjectPath ObjectPath = Ptr->ToSoftObjectPath();

		if (ObjectPath.IsValid())
		{
			if (UObject* O = Ptr->LoadSynchronous())
			{
				GetObjectPaths_ObjectProperty_Internal(SoftObjectProperty->PropertyClass, O, OutPaths);
			}
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_Struct(UStruct* Struct, NCsLoad::FGetObjectPaths& OutPaths)
{
	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		FProperty* Property = CastField<FProperty>(*It);

		UClass* Class = nullptr;
		
		// Class
		if (FClassProperty* ClassProperty = CastField<FClassProperty>(Property))
		{
			Class = ClassProperty->MetaClass;
		}
		// Object
		else
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			 Class = ObjectProperty->PropertyClass;
		}
		// SoftClass
		else
		if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			Class = SoftClassProperty->MetaClass;
		}
		// SoftObject
		else
		if (FSoftClassProperty* SoftObjectProperty = CastField<FSoftClassProperty>(Property))
		{
			Class = SoftObjectProperty->PropertyClass;
		}

		if (Class)
		{
			GetObjectPaths_Class_Internal(Class, OutPaths);
			continue;
		}

		// Struct
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			GetObjectPaths_Struct(StructProperty->Struct, OutPaths);
			continue;
		}
		// Array
		if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
		{
			Class = nullptr;
		
			// Class
			if (FClassProperty* InnerClassProperty = CastField<FClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerClassProperty->MetaClass;
			}
			// Object
			else
			if (FObjectProperty* InnerObjectProperty = CastField<FObjectProperty>(ArrayProperty->Inner))
			{
				 Class = InnerObjectProperty->PropertyClass;
			}
			// SoftClass
			else
			if (FSoftClassProperty* InnerSoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerSoftClassProperty->MetaClass;
			}
			// SoftObject
			else
			if (FSoftClassProperty* InnerSoftObjectProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerSoftObjectProperty->PropertyClass;
			}

			if (Class)
			{
				GetObjectPaths_Class_Internal(Class, OutPaths);
				continue;
			}

			// Struct
			if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
			{
				GetObjectPaths_Struct(InnerStructProperty->Struct, OutPaths);
				continue;
			}
			continue;
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_Function(UFunction* Function, NCsLoad::FGetObjectPaths& OutPaths)
{
	for (UObject* Object : Function->ScriptAndPropertyObjectReferences)
	{
		UClass* Class = Object->GetClass();

		const bool ValidClass = Class->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint);

		FSoftClassPath ClassPath(Class);
		ClassPath.SetPath(ClassPath.GetAssetPathString());

		const bool ValidName = !ClassPath.GetAssetName().StartsWith(TEXT("Default__"));
		/*
		const bool ValidName = ClassPath.GetAssetName() != OutPaths.RootName &&
							   ClassPath.GetAssetName() != OutPaths.RootDefaultName &&
							   !ClassPath.GetAssetName().StartsWith(TEXT("Default__"));
							   */
		const bool ValidPathRoot = !ClassPath.GetAssetPathString().StartsWith(TEXT("/Temp")) &&
								   !ClassPath.GetAssetPathString().StartsWith(TEXT("/Script"));

		if (ValidClass &&
			ValidName &&
			ValidPathRoot)
		{
			OutPaths.AddPath(ClassPath);
		}

		if (ValidClass)
		{
			if (!OutPaths.HasVisitedPointer(Class->GetFName(), Class))
			{
				OutPaths.VisitPointer(Class->GetFName(), Class);

				GetObjectPaths_Internal(Object, Class, OutPaths);
			}
		}
	}

	for (FProperty* Property = (FProperty*)Function->Children; Property; Property = (FProperty*)Property->Next)
	{
		const FString PropertyName = Property->GetName();

		UClass* Class = nullptr;
		
		// Class
		if (FClassProperty* ClassProperty = CastField<FClassProperty>(Property))
		{
			Class = ClassProperty->MetaClass;
		}
		// Object
		else
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			 Class = ObjectProperty->PropertyClass;
		}
		// SoftClass
		else
		if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			Class = SoftClassProperty->MetaClass;
		}
		// SoftObject
		else
		if (FSoftClassProperty* SoftObjectProperty = CastField<FSoftClassProperty>(Property))
		{
			Class = SoftObjectProperty->PropertyClass;
		}

		if (Class)
		{
			GetObjectPaths_Class_Internal(Class, OutPaths);
			continue;
		}

		// Struct
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			GetObjectPaths_Struct(StructProperty->Struct, OutPaths);
			continue;
		}
		// Array
		if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
		{
			Class = nullptr;
		
			// Class
			if (FClassProperty* InnerClassProperty = CastField<FClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerClassProperty->MetaClass;
			}
			// Object
			else
			if (FObjectProperty* InnerObjectProperty = CastField<FObjectProperty>(ArrayProperty->Inner))
			{
				 Class = InnerObjectProperty->PropertyClass;
			}
			// SoftClass
			else
			if (FSoftClassProperty* InnerSoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerSoftClassProperty->MetaClass;
			}
			// SoftObject
			else
			if (FSoftClassProperty* InnerSoftObjectProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerSoftObjectProperty->PropertyClass;
			}

			if (Class)
			{
				GetObjectPaths_Class_Internal(Class, OutPaths);
				continue;
			}

			// Struct
			if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
			{
				GetObjectPaths_Struct(InnerStructProperty->Struct, OutPaths);
				continue;
			}
			continue;
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_Internal(const void* StructValue, UStruct* const& Struct, NCsLoad::FGetObjectPaths& OutPaths)
{
	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		FProperty* Property = CastField<FProperty>(*It);

		const FString PropertyName = Property->GetName();
		
		// Class
		if (FClassProperty* ClassProperty = CastField<FClassProperty>(Property))
		{
			GetObjectPaths_ClassProperty(ClassProperty, StructValue, OutPaths);
			continue;
		}
		// Object
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			// Check for Material Expression that references Material.
			// This leads to infinite recursion. So, Skip.
			/*
			if (Struct->IsChildOf<UMaterialExpression>() &&
				ObjectProperty->PropertyClass->IsChildOf<UMaterialInterface>())
			{
				continue;
			}
			*/

			// DataTable
			if (ObjectProperty->PropertyClass == UDataTable::StaticClass())
			{
				UDataTable* const* DataTablePtr = ObjectProperty->ContainerPtrToValuePtr<UDataTable*>(StructValue);
				
				if (UDataTable* DataTable = *DataTablePtr)
				{
					if (!OutPaths.HasVisitedPointer(ObjectProperty->PropertyClass->GetFName(), DataTable))
					{
						OutPaths.VisitPointer(ObjectProperty->PropertyClass->GetFName(), DataTable);

						OutPaths.AddPath(FSoftObjectPath(DataTable));

						// Check each row for any Object Paths
						const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
						UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
						UStruct* const RowStruct		  = Temp;

						TArray<FName> RowNames = DataTable->GetRowNames();

						for (const FName& RowName : RowNames)
						{
							uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

							GetObjectPaths_Internal(RowPtr, RowStruct, OutPaths);
						}
					}
				}
			}
			else
			{
				GetObjectPaths_ObjectProperty(ObjectProperty, StructValue, OutPaths);
			}
			continue;
		}
		// SoftClass
		if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			GetObjectPaths_SoftClassProperty(SoftClassProperty, StructValue, OutPaths);
			continue;
		}
		// SoftObject
		if (FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
		{
			GetObjectPaths_SoftObjectProperty(SoftObjectProperty, StructValue, OutPaths);
			continue;
		}
		// Struct
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			//if (PropertyName.StartsWith(TEXT("UberGraphFrame")))
			//	continue;

			for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
			{
				if (const uint8* Ptr = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I))
				{
					if (!OutPaths.HasVisitedPointer(StructProperty->Struct->GetFName(), Ptr))
					{
						OutPaths.VisitPointer(StructProperty->Struct->GetFName(), Ptr);

						GetObjectPaths_Internal(Ptr, StructProperty->Struct, OutPaths);
					}
				}
			}
			continue;
		}
		
		// Array
		if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
		{
			FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

			const int32 Count = Helper.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				uint8* Ptr = Helper.GetRawPtr(I);

				// Class
				if (FClassProperty* InnerClassProperty = CastField<FClassProperty>(ArrayProperty->Inner))
				{
					UObject** ObjectPtr = reinterpret_cast<UObject**>(Ptr);

					if (UObject* Object = *ObjectPtr)
					{
						if (!OutPaths.HasVisitedPointer(InnerClassProperty->MetaClass->GetFName(), Ptr))
						{
							OutPaths.VisitPointer(InnerClassProperty->MetaClass->GetFName(), Ptr);

							GetObjectPaths_ClassProperty_Internal(InnerClassProperty->MetaClass, Object, OutPaths);
						}
					}
					continue;
				}
				// Object
				if (FObjectProperty* InnerObjectProperty = CastField<FObjectProperty>(ArrayProperty->Inner))
				{
					UObject** ObjectPtr = reinterpret_cast<UObject**>(Ptr);

					if (UObject* Object = *ObjectPtr)
					{
						if (!OutPaths.HasVisitedPointer(InnerObjectProperty->PropertyClass->GetFName(), Ptr))
						{
							OutPaths.VisitPointer(InnerObjectProperty->PropertyClass->GetFName(), Ptr);

							GetObjectPaths_ObjectProperty_Internal(InnerObjectProperty->PropertyClass, Object, OutPaths);
						}
					}
					continue;
				}
				// SoftClass
				if (FSoftClassProperty* InnerSoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
				{
					TSoftClassPtr<UObject>* ObjectPtr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));

					if (ObjectPtr->ToSoftObjectPath().IsValid())
					{
						UObject* Object = ObjectPtr->LoadSynchronous();

						if (UClass* Class = Cast<UClass>(Object))
						{
							if (!OutPaths.HasVisitedPointer(InnerSoftClassProperty->MetaClass->GetFName(), Ptr))
							{
								OutPaths.VisitPointer(InnerSoftClassProperty->MetaClass->GetFName(), Ptr);

								GetObjectPaths_ClassProperty_Internal(InnerSoftClassProperty->MetaClass, Object, OutPaths);
							}
						}
					}
					continue;
				}
				// SoftObject
				if (FSoftObjectProperty* InnerSoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner))
				{
					TSoftObjectPtr<UObject>* ObjectPtr = reinterpret_cast<TSoftObjectPtr<UObject>*>(Helper.GetRawPtr(I));

					if (ObjectPtr->ToSoftObjectPath().IsValid())
					{
						if (UObject* Object = ObjectPtr->LoadSynchronous())
						{
							if (!OutPaths.HasVisitedPointer(InnerSoftObjectProperty->PropertyClass->GetFName(), Ptr))
							{
								OutPaths.VisitPointer(InnerSoftObjectProperty->PropertyClass->GetFName(), Ptr);

								GetObjectPaths_ObjectProperty_Internal(InnerSoftObjectProperty->PropertyClass, Object, OutPaths);
							}
						}
					}
					continue;
				}
				// Struct
				if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
				{
					if (!OutPaths.HasVisitedPointer(InnerStructProperty->Struct->GetFName(), Ptr))
					{
						OutPaths.VisitPointer(InnerStructProperty->Struct->GetFName(), Ptr);

						GetObjectPaths_Internal(Ptr, InnerStructProperty->Struct, OutPaths);
					}
					continue;
				}
			}
			continue;
		}
	}
	
	// Iterate through Functions
	for (UFunction* Function : TFieldRange<UFunction>(Struct))
	{
		const FString FunctionName = Function->GetName();

		//if (FunctionName.StartsWith(TEXT("ExecuteUbergraph")))
		//	continue;

		const FString FunctionPath = FString::Printf(TEXT("%s.%s"), *(Struct->GetName()), *FunctionName);

		if (!OutPaths.HasVisitedFunction(FunctionPath))
		{
			OutPaths.VisitFunction(FunctionPath);

			GetObjectPaths_Function(Function, OutPaths);
		}
	}
}

void UCsLibrary_Load::GetObjectPaths(const void* StructValue, UStruct* const& Struct, NCsLoad::FGetObjectPaths& OutPaths)
{
	OutPaths.VisitPointer(Struct->GetFName(), StructValue);

	GetObjectPaths_Internal(StructValue, Struct, OutPaths);

	OutPaths.Resolve();
}

void UCsLibrary_Load::GetObjectPaths(UObject* StructValue, UStruct* const& Struct, NCsLoad::FGetObjectPaths& OutPaths)
{
	// Subobjects

		// Ignore UFunction and UMaterialFunctionInterface as getting subobjects have some thread / resource contention issues
	if (!Struct->IsChildOf<UFunction>() &&
		!Struct->IsChildOf<UMaterialFunctionInterface>())
	{
		TArray<UObject*> OutDefaultSubobjects;
		StructValue->GetDefaultSubobjects(OutDefaultSubobjects);

		for (UObject* O : OutDefaultSubobjects)
		{
			OutPaths.VisitPointer(O->GetClass()->GetFName(), O);

			GetObjectPaths_Internal(O, O->GetClass(), OutPaths);
		}
	}

	OutPaths.VisitPointer(Struct->GetFName(), StructValue);

	GetObjectPaths_Internal(StructValue, Struct, OutPaths);

	OutPaths.Resolve();
}

#pragma endregion ObjectPath

// Load
#pragma region

bool UCsLibrary_Load::CanLoad(void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
{
	return true;

	// DEPRECATED: LoadFlags currently not used.

	/*
								// MemberName + TEXT("_LoadFlags")
	const FString FlagMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

	if (FIntProperty* IntProperty = FindFProperty<FIntProperty>(Struct, *FlagMemberName))
	{
		if (int32* MemberLoadFlags = IntProperty->ContainerPtrToValuePtr<int32>(StructValue))
		{
			if (LoadFlags == NCsLoadFlags::All)
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::SuppressLoadFlagsAllWarning))
					return true;

				UE_LOG(LogCs, Warning, TEXT("URsLibrary_Load::CanLoad (%s @ %s): Using LoadFlags = 1 (All). This should be reserved for debugging. Be explicit with LoadFlags."), *(Struct->GetName()), *MemberName);
				return true;
			}
			if (*MemberLoadFlags == NCsLoadFlags::All)
			{
				if (CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::SuppressLoadFlagsAllWarning))
					return true;

				UE_LOG(LogCs, Warning, TEXT("URsLibrary_Load::CanLoad (%s @ %s): Using LoadFlags = 1 (All). This should be reserved for debugging. Be explicit with LoadFlags."), *(Struct->GetName()), *MemberName);
				return true;
			}
			if (CS_TEST_BLUEPRINT_BITFLAG(*MemberLoadFlags, LoadFlags))
				return true;
		}
	}
	return true;
	*/
}

void UCsLibrary_Load::LoadSoftClassProperty(FSoftClassProperty* SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
{
	if (FSoftObjectPtr* Member = SoftClassProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		if (!Member->ToSoftObjectPath().IsValid())
			return;

		if (!CanLoad(StructValue, Struct, MemberName, LoadFlags, LoadCodes))
			return;

		// Check if an "Internal" member exists (i.e. MemberName + _Internal)

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (FObjectProperty* InternalObjectProperty = FindFProperty<FObjectProperty>(Struct, *InternalMemberName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftClassProperty->MetaClass == InternalObjectProperty->PropertyClass)
			{
				if (UObject** Internal = InternalObjectProperty->ContainerPtrToValuePtr<UObject*>(StructValue))
				{
					UObject* O	  = Member->LoadSynchronous();
					UClass* Class = Cast<UClass>(O);
					*Internal	  = Class->GetDefaultObject();

					if (*Internal)
					{
						// ICsData
						if (ICsData* Data = Cast<ICsData>(*Internal))
						{
						#if WITH_EDITOR
							Data->Load(LoadFlags);
						#else
							if (!Data->IsLoaded())
								Data->Load(LoadFlags);
						#endif // #if WITH_EDITOR
						}
						// ICsScriptData
						else
						if ((*Internal)->GetClass()->ImplementsInterface(UCsData::StaticClass()))
						{
							bool OutSuccess = false;
						#if WITH_EDITOR
							ICsScriptData::Execute_Script_Load(*Internal, LoadFlags, OutSuccess);
						#else
							if (!ICsScriptData::Execute_Script_IsLoaded(*Internal, OutSuccess))
								ICsScriptData::Execute_Script_Load(*Internal, LoadFlags, OutSuccess);
						#endif // #if WITH_EDITOR
						}
						else
						{
							LoadStruct(*Internal, Class, LoadFlags, LoadCodes);
						}
					}
				}
			}
		}

		// Check if a "Class" member exists (i.e. MemberName + _Class)

										// MemberName + TEXT("_Class")
		const FString InternalClassName = MemberName + ECsLoadCached::Str::_Class;

		if (FClassProperty* InternalClassProperty = FindFProperty<FClassProperty>(Struct, *InternalClassName))
		{
			if (TObjectPtr<UObject>* Object = InternalClassProperty->GetPropertyValuePtr_InContainer(StructValue))
			{
				*Object = Member->LoadSynchronous();
			}
		}

		// Check if a "SubclassOf" member exists (i.e. MemberName + _SubclassOf)

		// MemberName + TEXT("_SubclassOf")
		const FString InternalSubclassOfName = MemberName + ECsLoadCached::Str::_SubclassOf;

		if (FClassProperty* InternalSubclassOfProperty = FindFProperty<FClassProperty>(Struct, *InternalSubclassOfName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftClassProperty->MetaClass == InternalSubclassOfProperty->MetaClass)
			{
				if (TObjectPtr<UObject>* Object = InternalSubclassOfProperty->GetPropertyValuePtr_InContainer(StructValue))
				{
					*Object = Member->LoadSynchronous();
				}
			}
		}
	}
}

void UCsLibrary_Load::LoadArraySoftClassProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
{
	if (!CanLoad(StructValue, Struct, MemberName, LoadFlags, LoadCodes))
		return;

	// Check if an "Internal" member exists (i.e. MemberName + _Internal)

									// MemberName + TEXT("_Internal")
	const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

	if (FArrayProperty* InternalArrayProperty = FindFProperty<FArrayProperty>(Struct, *InternalMemberName))
	{
		if (FObjectProperty* InternalSoftObjectProperty = CastField<FObjectProperty>(InternalArrayProperty->Inner))
		{
			FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner);

			// Check Member is the same type as the Member_Internal
			if (SoftClassProperty->MetaClass == InternalSoftObjectProperty->PropertyClass)
			{
				FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);
				FScriptArrayHelper_InContainer InternalHelper(InternalArrayProperty, StructValue);

				const int32 Count = Helper.Num();

				InternalHelper.EmptyAndAddUninitializedValues(Helper.Num());

				for (int32 I = 0; I < Count; ++I)
				{
					TSoftClassPtr<UObject>* Ptr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));
					UObject** InternalPtr		= reinterpret_cast<UObject**>(InternalHelper.GetRawPtr(I));

					*InternalPtr = nullptr;

					if (Ptr->IsValid())
					{
						UObject* O	  = Ptr->LoadSynchronous();
						UClass* Class = Cast<UClass>(O);
						*InternalPtr  = Class->GetDefaultObject();

						if (InternalPtr)
						{
							// ICsData
							if (ICsData* Data = Cast<ICsData>(*InternalPtr))
							{
							#if WITH_EDITOR
								Data->Load(LoadFlags);
							#else
								if (!Data->IsLoaded())
									Data->Load(LoadFlags);
							#endif // #if WITH_EDITOR
							}
							// ICsScriptData
							else
							if ((*InternalPtr)->GetClass()->ImplementsInterface(UCsData::StaticClass()))
							{
								bool OutSuccess = false;
							#if WITH_EDITOR
								ICsScriptData::Execute_Script_Load(*InternalPtr, LoadFlags, OutSuccess);
							#else
								if (!ICsScriptData::Execute_Script_IsLoaded(*InternalPtr, OutSuccess))
									ICsScriptData::Execute_Script_Load(*InternalPtr, LoadFlags, OutSuccess);
							#endif // #if WITH_EDITOR
							}
							else
							{
								LoadStruct(*InternalPtr, Class, LoadFlags, LoadCodes);
							}
						}
					}
				}
			}
		}
	}

	// Check if an "Class" member exists (i.e. MemberName + _Class)

									// MemberName + TEXT("_Class")
	const FString InternalClassName = MemberName + ECsLoadCached::Str::_Class;

	if (FArrayProperty* InternalArrayProperty = FindFProperty<FArrayProperty>(Struct, *InternalClassName))
	{
		if (FSoftClassProperty* InternalSoftClassProperty = CastField<FSoftClassProperty>(InternalArrayProperty->Inner))
		{
			FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner);

			FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);
			FScriptArrayHelper_InContainer InternalHelper(InternalArrayProperty, StructValue);

			const int32 Count = Helper.Num();

			InternalHelper.EmptyAndAddUninitializedValues(Helper.Num());

			for (int32 I = 0; I < Count; ++I)
			{
				TSoftClassPtr<UObject>* Ptr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));
				UClass** InternalPtr		= reinterpret_cast<UClass**>(InternalHelper.GetRawPtr(I));

				*InternalPtr = nullptr;

				if (Ptr->IsValid())
				{
					UObject* O    = Ptr->LoadSynchronous();
					*InternalPtr  = Cast<UClass>(O);
				}
			}
		}
	}

	// TODO: SubclassOf
}

void UCsLibrary_Load::LoadSoftObjectProperty(FSoftObjectProperty* SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
{
	if (FSoftObjectPtr* Member = SoftObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		if (!Member->ToSoftObjectPath().IsValid())
			return;

		if (!CanLoad(StructValue, Struct, MemberName, LoadFlags, LoadCodes))
			return;

		// Check if an "Internal" member exists (i.e. MemberName + _Internal)

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (FObjectProperty* InternalObjectProperty = FindFProperty<FObjectProperty>(Struct, *InternalMemberName))
		{
			// Blueprint
			if (SoftObjectProperty->PropertyClass->IsChildOf(UBlueprint::StaticClass()) &&
				InternalObjectProperty->PropertyClass->IsChildOf(UBlueprintGeneratedClass::StaticClass()))
			{
				if (TObjectPtr<UObject>* Internal = InternalObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
				{
					FString Path = Member->ToSoftObjectPath().ToString();

					if (!Path.EndsWith(ECsLoadCached::Str::_C, ESearchCase::CaseSensitive))
						Path.Append(ECsLoadCached::Str::_C);

					FSoftObjectPath SoftPath(Path);

					UObject* O = SoftPath.TryLoad();

					checkf(O, TEXT("UCsLibrary_Load::LoadSoftObjectProperty: Failed to load Object at Path: %s."), *Path);

					*Internal = O;

					// TODO: Eventually get LoadStruct to work for BlueprintGeneratedClass
					/*
					if (*Internal)
					{
						LoadStruct(*Internal, Cast<UClass>((*Internal)), LoadFlags, LoadCodes);
					}
					*/
				}
			}
			// Check Member is the same type as the Member_Internal
			else
			if (SoftObjectProperty->PropertyClass == InternalObjectProperty->PropertyClass)
			{
				if (TObjectPtr<UObject>* Internal = InternalObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
				{
					*Internal = Member->LoadSynchronous();

					if (*Internal)
					{
						// Recursive Load DataTable
						if (SoftObjectProperty->PropertyClass == UDataTable::StaticClass() &&
							CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::RecursiveLoadDataTable))
						{
							UDataTable* DataTable = Cast<UDataTable>(*Internal);

							LoadDataTable(DataTable, LoadFlags, LoadCodes);
						}
						else
						{
							LoadStruct(*Internal, (*Internal)->GetClass(), LoadFlags, LoadCodes);
						}
					}
				}
			}
		}
	}
}

void UCsLibrary_Load::LoadArraySoftObjectProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
{
	if (!CanLoad(StructValue, Struct, MemberName, LoadFlags, LoadCodes))
		return;

	// Check if an "Internal" member exists (i.e. MemberName + _Internal)

									// MemberName + TEXT("_Internal")
	const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

	if (FArrayProperty* InternalArrayProperty = FindFProperty<FArrayProperty>(Struct, *InternalMemberName))
	{
		if (FObjectProperty* InternalSoftObjectProperty = CastField<FObjectProperty>(InternalArrayProperty->Inner))
		{
			FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner);

			// Blueprint
			if (SoftObjectProperty->PropertyClass->IsChildOf(UBlueprint::StaticClass()) &&
				InternalSoftObjectProperty->PropertyClass->IsChildOf(UBlueprintGeneratedClass::StaticClass()))
			{
				FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);
				FScriptArrayHelper_InContainer InternalHelper(InternalArrayProperty, StructValue);

				const int32 Count = Helper.Num();

				InternalHelper.EmptyAndAddUninitializedValues(Helper.Num());

				for (int32 I = 0; I < Count; ++I)
				{
					TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<TSoftObjectPtr<UObject>*>(Helper.GetRawPtr(I));
					UObject** InternalPtr		 = reinterpret_cast<UObject**>(InternalHelper.GetRawPtr(I));

					*InternalPtr = nullptr;

					if (Ptr->ToSoftObjectPath().IsValid())
					{
						FString Path = Ptr->ToSoftObjectPath().ToString();

						if (!Path.EndsWith(ECsLoadCached::Str::_C, ESearchCase::CaseSensitive))
							Path.Append(ECsLoadCached::Str::_C);

						FSoftObjectPath SoftPath(Path);

						UObject* O = SoftPath.TryLoad();

						checkf(O, TEXT("UCsLibrary_Load::LoadArraySoftObjectProperty: Failed to load Object at Path: %s."), *Path);

						UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

						checkf(BpGC, TEXT("UCsLibrary_Load::LoadArraySoftObjectProperty: Failed to cast Object: %s to UBlueprintGeneratedClass."), *(O->GetName()));

						//checkf(BpGC->ClassGeneratedBy, TEXT("UCsLibrary_Load::LoadArraySoftObjectProperty: ClassGeneratedBy is NULL for Object: %s."), *(O->GetName()));

						UBlueprintCore* BpC = nullptr;//Cast<UBlueprintCore>(BpGC->ClassGeneratedBy);

						//checkf(BpC, TEXT("UCsLibrary_Load::LoadArraySoftObjectProperty: Failed to cast Class: %s to UBlueprintCore."), *(BpGC->ClassGeneratedBy->GetName()));

						checkf(BpC->GeneratedClass, TEXT("UCsLibrary_Load::LoadArraySoftObjectProperty: Failed to get GeneratedClass from Class: %s."), *(BpC->GetName()));

						*InternalPtr = BpC->GeneratedClass;
					}

					if (*InternalPtr)
					{
						LoadStruct(*InternalPtr, Cast<UClass>((*InternalPtr)), LoadFlags, LoadCodes);
					}
				}
			}
			// Check Member is the same type as the Member_Internal
			else
			if (SoftObjectProperty->PropertyClass == InternalSoftObjectProperty->PropertyClass)
			{
				FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);
				FScriptArrayHelper_InContainer InternalHelper(InternalArrayProperty, StructValue);

				const int32 Count = Helper.Num();

				InternalHelper.EmptyAndAddUninitializedValues(Helper.Num());

				for (int32 I = 0; I < Count; ++I)
				{
					TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<TSoftObjectPtr<UObject>*>(Helper.GetRawPtr(I));
					UObject** InternalPtr		 = reinterpret_cast<UObject**>(InternalHelper.GetRawPtr(I));

					*InternalPtr = nullptr;

					if (Ptr->ToSoftObjectPath().IsValid())
					{
						*InternalPtr = Ptr->LoadSynchronous();
					}

					if (*InternalPtr)
					{
						// Recursive Load DataTable
						if (SoftObjectProperty->PropertyClass == UDataTable::StaticClass() &&
							CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::RecursiveLoadDataTable))
						{
							UDataTable* DataTable = Cast<UDataTable>(*InternalPtr);

							LoadDataTable(DataTable, LoadFlags, LoadCodes);
						}
						else
						{
							LoadStruct(*InternalPtr, (*InternalPtr)->GetClass(), LoadFlags, LoadCodes);
						}
					}
				}
			}
		}
	}
}

void UCsLibrary_Load::LoadClassProperty(FClassProperty* ClassProperty, void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes)
{
	if (TObjectPtr<UObject>* ObjectPtr = ClassProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		if (UObject* Object = ObjectPtr->Get())
		{
			UClass* Class = Cast<UClass>(Object);
			UObject* DOb = Class->GetDefaultObject();

			// ICsData
			if (ICsData* Data = Cast<ICsData>(DOb))
			{
			#if WITH_EDITOR
				Data->Load(LoadFlags);
			#else
				if (!Data->IsLoaded())
					Data->Load(LoadFlags);
			#endif // #if WITH_EDITOR
			}
			// ICsScriptData
			else
			if (DOb->GetClass()->ImplementsInterface(UCsData::StaticClass()))
			{
				bool OutSuccess = false;
			#if WITH_EDITOR
				ICsScriptData::Execute_Script_Load(DOb, LoadFlags, OutSuccess);
			#else
				if (!ICsScriptData::Execute_Script_IsLoaded(DOb, OutSuccess))
					ICsScriptData::Execute_Script_Load(DOb, LoadFlags, OutSuccess);
			#endif // #if WITH_EDITOR
			}
		}
	}
}

void UCsLibrary_Load::LoadArrayClassProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		UObject** Object = reinterpret_cast<UObject**>(Helper.GetRawPtr(I));

		if (Object)
		{
			UClass* Class = Cast<UClass>(*Object);
			UObject* DOb  = Class->GetDefaultObject();

			// ICsData
			if (ICsData* Data = Cast<ICsData>(DOb))
			{
			#if WITH_EDITOR
				Data->Load(LoadFlags);
			#else
				if (!Data->IsLoaded())
					Data->Load(LoadFlags);
			#endif // #if WITH_EDITOR
			}
			// ICsScriptData
			else
			if (DOb->GetClass()->ImplementsInterface(UCsData::StaticClass()))
			{
				bool OutSuccess = false;
			#if WITH_EDITOR
				ICsScriptData::Execute_Script_Load(DOb, LoadFlags, OutSuccess);
			#else
				if (!ICsScriptData::Execute_Script_IsLoaded(DOb, OutSuccess))
					ICsScriptData::Execute_Script_Load(DOb, LoadFlags, OutSuccess);
			#endif // #if WITH_EDITOR
			}
		}
	}
}

void UCsLibrary_Load::LoadArrayObjectProperty(FArrayProperty* ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	FObjectProperty* ObjectProperty = CastField<FObjectProperty>(ArrayProperty->Inner);

	for (int32 I = 0; I < Count; ++I)
	{
		uint8* Ptr = Helper.GetRawPtr(I);

		LoadStruct(Ptr, ObjectProperty->PropertyClass, LoadFlags, LoadCodes);
	}
}

void UCsLibrary_Load::LoadArrayStructProperty(FArrayProperty* ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	FStructProperty* StructProperty = CastField<FStructProperty>(ArrayProperty->Inner);

	for (int32 I = 0; I < Count; ++I)
	{
		uint8* Ptr = Helper.GetRawPtr(I);

		LoadStruct(Ptr, StructProperty->Struct, LoadFlags, LoadCodes);
	}
}

void UCsLibrary_Load::LoadStruct(void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes)
{
	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		FProperty* Property = CastField<FProperty>(*It);

		const FString PropertyName = Property->GetName();

		// TSoftClassPtr
		if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			LoadSoftClassProperty(SoftClassProperty, StructValue, Struct, PropertyName, NCsLoadFlags::All, LoadCodes);
			continue;
		}
		// TSoftObjectPtr
		if (FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
		{
			LoadSoftObjectProperty(SoftObjectProperty, StructValue, Struct, PropertyName, NCsLoadFlags::All, LoadCodes);
			continue;
		}
		// Class
		if (FClassProperty* ClassProperty = CastField<FClassProperty>(Property))
		{
			LoadClassProperty(ClassProperty, StructValue, Struct, LoadFlags, LoadCodes);
			continue;
		}
		// Object
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			// Recursive Load DataTable
			if (ObjectProperty->PropertyClass == UDataTable::StaticClass() &&
				CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::RecursiveLoadDataTable))
			{
				UDataTable** DataTable = ObjectProperty->ContainerPtrToValuePtr<UDataTable*>(StructValue);

				if (*DataTable)
				{
					LoadDataTable(*DataTable, LoadFlags, LoadCodes);
				}
			}
			// Anim Notifies
			else
			if (ObjectProperty->PropertyClass == UAnimNotify::StaticClass())
			{
				UAnimNotify** Notify = ObjectProperty->ContainerPtrToValuePtr<UAnimNotify*>(StructValue);

				if (*Notify)
				{
					LoadStruct(*Notify, (*Notify)->GetClass(), LoadFlags, LoadCodes);
				}
			}
			continue;
		}
		// Struct
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
			{
				uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I);
				
				LoadStruct(Value, StructProperty->Struct, LoadFlags, LoadCodes);
			}
			continue;
		}
		// Array
		if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (FSoftClassProperty* InnerSoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
			{
				LoadArraySoftClassProperty(ArrayProperty, StructValue, Struct, PropertyName, NCsLoadFlags::All, LoadCodes);
				continue;
			}
			// TSoftObjectPtr
			if (FSoftObjectProperty* InnerSoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner))
			{
				LoadArraySoftObjectProperty(ArrayProperty, StructValue, Struct, PropertyName, NCsLoadFlags::All, LoadCodes);
				continue;
			}
			// Class
			if (FClassProperty* InnerClassProperty = CastField<FClassProperty>(ArrayProperty->Inner))
			{
				LoadArrayClassProperty(ArrayProperty, StructValue, Struct, NCsLoadFlags::All, LoadCodes);
				continue;
			}
			// Object
			if (FObjectProperty* InnerObjectProperty = CastField<FObjectProperty>(ArrayProperty->Inner))
			{
				// Recursive Load DataTable
				if (InnerObjectProperty->PropertyClass == UDataTable::StaticClass() &&
					CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::RecursiveLoadDataTable))
				{
					LoadArrayObjectProperty(ArrayProperty, StructValue, LoadFlags, LoadCodes);
				}
				continue;
			}
			// Struct
			if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
			{
				LoadArrayStructProperty(ArrayProperty, StructValue, LoadFlags, LoadCodes);
				continue;
			}
		}
		// Map
		if (FMapProperty* MapProperty = CastField<FMapProperty>(*It))
		{
			// Struct
			if (FStructProperty* StructValueProperty = CastField<FStructProperty>(MapProperty->ValueProp))
			{
				void* MapPtr = MapProperty->ContainerPtrToValuePtr<void>(StructValue, 0);

				FScriptMapHelper MapHelper(MapProperty, MapPtr);

				for (FScriptMapHelper::FIterator MapIt = MapHelper.CreateIterator(); MapIt; ++MapIt)
				{
					void* ValuePtr = MapHelper.GetValuePtr(*MapIt);

					LoadStruct(ValuePtr, StructValueProperty->Struct, LoadFlags, LoadCodes);
					continue;
				}
			}
		}
		// Set
		if (FSetProperty* SetProperty = CastField<FSetProperty>(*It))
		{
			// Struct
			if (FStructProperty* StructElementProperty = CastField<FStructProperty>(SetProperty->ElementProp))
			{
				void* SetPtr = SetProperty->ContainerPtrToValuePtr<void>(StructValue, 0);

				FScriptSetHelper SetHelper(SetProperty, SetPtr);

				for (FScriptSetHelper::FIterator SetIt = SetHelper.CreateIterator(); SetIt; ++SetIt)
				{
					void* ValuePtr = SetHelper.GetElementPtr(*SetIt);

					LoadStruct(ValuePtr, StructElementProperty->Struct, LoadFlags, LoadCodes);
					continue;
				}
			}
		}
	}
}

void UCsLibrary_Load::LoadDataTable(UDataTable* DataTable, const int32& LoadFlags, const int32& LoadCodes)
{
	const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
	UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct			  = Temp;

	TArray<FName> RowNames = DataTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

		LoadStruct(RowPtr, Struct, LoadFlags, LoadCodes);
	}
}

void UCsLibrary_Load::LoadDataTableRowChecked(const FString& Context, UDataTable* DataTable, const FName& RowName, const int32& LoadFlags, const int32& LoadCodes)
{
	CS_IS_PTR_NULL_CHECKED(DataTable)
	CS_IS_NAME_NONE_CHECKED(RowName)

	const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();

	checkf(ScriptStruct, TEXT("%s: No RowStruct for DataTable: %s."), *Context, *(DataTable->GetName()));

	UScriptStruct* Temp		= const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct	= Temp;

	uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

	checkf(RowPtr, TEXT("%s: Failed to find Row: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DataTable->GetName()));

	LoadStruct(RowPtr, Struct, LoadFlags, LoadCodes);
}

bool UCsLibrary_Load::SafeLoadDataTableRow(const FString& Context, UDataTable* DataTable, const FName& RowName, const int32& LoadFlags, const int32& LoadCodes, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	CS_IS_PTR_NULL(DataTable)
	CS_IS_NAME_NONE(RowName)

	const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();

	if (!ScriptStruct)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No RowStruct for DataTable: %s."), *Context, *(DataTable->GetName())));
		return false;
	}

	UScriptStruct* Temp		= const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct	= Temp;

	uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

	if (!RowPtr)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Row: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DataTable->GetName())));
		return false;
	}

	LoadStruct(RowPtr, Struct, LoadFlags, LoadCodes);
	return true;
}

UObject* UCsLibrary_Load::LoadSoftClassPtrChecked(const FString& Context, const TSoftClassPtr<UObject>& SoftClass, const int32& LoadFlags, const int32& LoadCodes)
{
	checkf(SoftClass.ToSoftObjectPath().IsValid(), TEXT("%: SoftClass is NOT Valid."), *Context);

	UObject* O	  = SoftClass.LoadSynchronous();
	UClass* Class = Cast<UClass>(O);
	UObject* DOb  = Class->GetDefaultObject();

	checkf(DOb, TEXT("%s: Failed to get Default Object from Class: %s"), *Context, *(Class->GetName()));

	// ICsData
	if (ICsData* Data = Cast<ICsData>(DOb))
	{
	#if WITH_EDITOR
		Data->Load(LoadFlags);
	#else
		if (!Data->IsLoaded())
			Data->Load(LoadFlags);
	#endif // #if WITH_EDITOR
	}
	// ICsScriptData
	else
	if (DOb->GetClass()->ImplementsInterface(UCsData::StaticClass()))
	{
		bool OutSuccess = false;
	#if WITH_EDITOR
		ICsScriptData::Execute_Script_Load(DOb, LoadFlags, OutSuccess);
	#else
		if (!ICsScriptData::Execute_Script_IsLoaded(DOb, OutSuccess))
			ICsScriptData::Execute_Script_Load(DOb, LoadFlags, OutSuccess);
	#endif // #if WITH_EDITOR
	}
	else
	{
		LoadStruct(DOb, Class, LoadFlags, LoadCodes);
	}
	return DOb;
}

#pragma endregion Load

// Unload
#pragma region

void UCsLibrary_Load::UnloadSoftClassProperty(FSoftClassProperty* SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes)
{
	if (FSoftObjectPtr* Member = SoftClassProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		if (!Member->ToSoftObjectPath().IsValid())
			return;

		Member->ResetWeakPtr();

		// Check if an "Internal" member exists (i.e. MemberName + _Internal)

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (FObjectProperty* InternalObjectProperty = FindFProperty<FObjectProperty>(Struct, *InternalMemberName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftClassProperty->MetaClass == InternalObjectProperty->PropertyClass)
			{
				if (UObject** Internal = InternalObjectProperty->ContainerPtrToValuePtr<UObject*>(StructValue))
				{
					*Internal = nullptr;
				}
			}
		}

		// Check if a "Class" member exists (i.e. MemberName + _Class)

										// MemberName + TEXT("_Class")
		const FString InternalClassName = MemberName + ECsLoadCached::Str::_Class;

		if (FClassProperty* InternalClassProperty = FindFProperty<FClassProperty>(Struct, *InternalClassName))
		{
			if (TObjectPtr<UObject>* Object = InternalClassProperty->GetPropertyValuePtr_InContainer(StructValue))
			{
				*Object = nullptr;
			}
		}

		// Check if a "SubclassOf" member exists (i.e. MemberName + _SubclassOf)

		// MemberName + TEXT("_SubclassOf")
		const FString InternalSubclassOfName = MemberName + ECsLoadCached::Str::_SubclassOf;

		if (FClassProperty* InternalSubclassOfProperty = FindFProperty<FClassProperty>(Struct, *InternalSubclassOfName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftClassProperty->MetaClass == InternalSubclassOfProperty->MetaClass)
			{
				if (TObjectPtr<UObject>* Object = InternalSubclassOfProperty->GetPropertyValuePtr_InContainer(StructValue))
				{
					*Object = nullptr;
				}
			}
		}
	}
}

void UCsLibrary_Load::UnloadArraySoftClassProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes)
{
	// Check if an "Internal" member exists (i.e. MemberName + _Internal)

									// MemberName + TEXT("_Internal")
	const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

	if (FArrayProperty* InternalArrayProperty = FindFProperty<FArrayProperty>(Struct, *InternalMemberName))
	{
		if (FSoftObjectProperty* InternalSoftObjectProperty = CastField<FSoftObjectProperty>(InternalArrayProperty->Inner))
		{
			FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner);

			// Check Member is the same type as the Member_Internal
			if (SoftClassProperty->MetaClass == InternalSoftObjectProperty->PropertyClass)
			{
				FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);
				FScriptArrayHelper_InContainer InternalHelper(InternalArrayProperty, StructValue);

				const int32 Count = Helper.Num();

				InternalHelper.EmptyAndAddUninitializedValues(Helper.Num());

				for (int32 I = 0; I < Count; ++I)
				{
					TSoftClassPtr<UObject>* Ptr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));
					UObject** InternalPtr		= reinterpret_cast<UObject**>(InternalHelper.GetRawPtr(I));

					Ptr->ResetWeakPtr();
					*InternalPtr = nullptr;
				}
			}
		}
	}

	// Check if an "Class" member exists (i.e. MemberName + _Class)

									// MemberName + TEXT("_Class")
	const FString InternalClassName = MemberName + ECsLoadCached::Str::_Class;

	if (FArrayProperty* InternalArrayProperty = FindFProperty<FArrayProperty>(Struct, *InternalClassName))
	{
		if (FSoftClassProperty* InternalSoftClassProperty = CastField<FSoftClassProperty>(InternalArrayProperty->Inner))
		{
			FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner);

			FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);
			FScriptArrayHelper_InContainer InternalHelper(InternalArrayProperty, StructValue);

			const int32 Count = Helper.Num();

			InternalHelper.EmptyAndAddUninitializedValues(Helper.Num());

			for (int32 I = 0; I < Count; ++I)
			{
				TSoftClassPtr<UObject>* Ptr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));
				UClass** InternalPtr		= reinterpret_cast<UClass**>(InternalHelper.GetRawPtr(I));

				Ptr->ResetWeakPtr();
				*InternalPtr = nullptr;
			}
		}
	}

	// TODO: SubclassOf
}

void UCsLibrary_Load::UnloadSoftObjectProperty(FSoftObjectProperty* SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes)
{
	if (FSoftObjectPtr* Member = SoftObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		if (!Member->ToSoftObjectPath().IsValid())
			return;

		Member->ResetWeakPtr();

		// Check if an "Internal" member exists (i.e. MemberName + _Internal)

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (FObjectProperty* InternalObjectProperty = FindFProperty<FObjectProperty>(Struct, *InternalMemberName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftObjectProperty->PropertyClass == InternalObjectProperty->PropertyClass)
			{
				if (TObjectPtr<UObject>* Internal = InternalObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
				{
					// Recursive Unload DataTable
					if (*Internal	 &&
						SoftObjectProperty->PropertyClass == UDataTable::StaticClass() &&
						CS_TEST_BLUEPRINT_BITFLAG(UnloadCodes, ECsUnloadCode::RecursiveUnloadDataTable))
					{
						UDataTable* DataTable = Cast<UDataTable>(*Internal);

						UnloadDataTable(DataTable, UnloadCodes);
					}
					*Internal = nullptr;
				}
			}
		}
	}
}

void UCsLibrary_Load::UnloadArraySoftObjectProperty(FArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes)
{
	// Check if an "Internal" member exists (i.e. MemberName + _Internal)

									// MemberName + TEXT("_Internal")
	const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

	if (FArrayProperty* InternalArrayProperty = FindFProperty<FArrayProperty>(Struct, *InternalMemberName))
	{
		if (FSoftObjectProperty* InternalSoftObjectProperty = CastField<FSoftObjectProperty>(InternalArrayProperty->Inner))
		{
			FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner);

			// Check Member is the same type as the Member_Internal
			if (SoftObjectProperty->PropertyClass == InternalSoftObjectProperty->PropertyClass)
			{
				FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);
				FScriptArrayHelper_InContainer InternalHelper(InternalArrayProperty, StructValue);

				const int32 Count = Helper.Num();

				InternalHelper.EmptyAndAddUninitializedValues(Helper.Num());

				for (int32 I = 0; I < Count; ++I)
				{
					TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<TSoftObjectPtr<UObject>*>(Helper.GetRawPtr(I));
					UObject** InternalPtr		 = reinterpret_cast<UObject**>(InternalHelper.GetRawPtr(I));

					// Recursive Unload DataTable
					if (*InternalPtr &&
						SoftObjectProperty->PropertyClass == UDataTable::StaticClass() &&
						CS_TEST_BLUEPRINT_BITFLAG(UnloadCodes, ECsUnloadCode::RecursiveUnloadDataTable))
					{
						UDataTable* DataTable = Cast<UDataTable>(*InternalPtr);

						UnloadDataTable(DataTable, UnloadCodes);
					}

					Ptr->ResetWeakPtr();
					*InternalPtr = nullptr;
				}
			}
		}
	}
}

void UCsLibrary_Load::UnloadArrayObjectProperty(FArrayProperty* ArrayProperty, void* StructValue, const int32& UnloadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	FObjectProperty* ObjectProperty = CastField<FObjectProperty>(ArrayProperty->Inner);

	for (int32 I = 0; I < Count; ++I)
	{
		uint8* Ptr = Helper.GetRawPtr(I);

		UnloadStruct(Ptr, ObjectProperty->PropertyClass, UnloadCodes);
	}
}

void UCsLibrary_Load::UnloadArrayStructProperty(FArrayProperty* ArrayProperty, void* StructValue, const int32& UnloadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	FStructProperty* StructProperty = CastField<FStructProperty>(ArrayProperty->Inner);

	for (int32 I = 0; I < Count; ++I)
	{
		uint8* Ptr = Helper.GetRawPtr(I);

		UnloadStruct(Ptr, StructProperty->Struct, UnloadCodes);
	}
}

void UCsLibrary_Load::UnloadStruct(void* StructValue, UStruct* const& Struct, const int32& UnloadCodes)
{
	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		FProperty* Property = CastField<FProperty>(*It);

		const FString PropertyName = Property->GetName();

		// TSoftClassPtr
		if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			UnloadSoftClassProperty(SoftClassProperty, StructValue, Struct, PropertyName, UnloadCodes);
			continue;
		}
		// TSoftObjectPtr
		if (FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
		{
			UnloadSoftObjectProperty(SoftObjectProperty, StructValue, Struct, PropertyName, UnloadCodes);
			continue;
		}
		// Object
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			// Recursive Load DataTable
			if (ObjectProperty->PropertyClass == UDataTable::StaticClass() &&
				CS_TEST_BLUEPRINT_BITFLAG(UnloadCodes, ECsUnloadCode::RecursiveUnloadDataTable))
			{
				UDataTable** DataTable = ObjectProperty->ContainerPtrToValuePtr<UDataTable*>(StructValue);

				UnloadDataTable(*DataTable, UnloadCodes);
			}
			continue;
		}
		// Struct
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
			{
				uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I);

				UnloadStruct(Value, StructProperty->Struct, UnloadCodes);
			}
			continue;
		}
		// Array
		if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (FSoftClassProperty* InnerSoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
			{
				UnloadArraySoftClassProperty(ArrayProperty, StructValue, Struct, PropertyName, UnloadCodes);
				continue;
			}
			// TSoftObjectPtr
			if (FSoftObjectProperty* InnerSoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner))
			{
				UnloadArraySoftObjectProperty(ArrayProperty, StructValue, Struct, PropertyName, UnloadCodes);
				continue;
			}
			// Object
			if (FObjectProperty* InnerObjectProperty = CastField<FObjectProperty>(ArrayProperty->Inner))
			{
				// Recursive Load DataTable
				if (InnerObjectProperty->PropertyClass == UDataTable::StaticClass() &&
					CS_TEST_BLUEPRINT_BITFLAG(UnloadCodes, ECsUnloadCode::RecursiveUnloadDataTable))
				{
					UnloadArrayObjectProperty(ArrayProperty, StructValue, UnloadCodes);
				}
				continue;
			}
			// Struct
			if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
			{
				UnloadArrayStructProperty(ArrayProperty, StructValue, UnloadCodes);
				continue;
			}
		}	
	}
}

void UCsLibrary_Load::UnloadDataTable(UDataTable* DataTable, const int32& UnloadCodes)
{
	const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
	UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
	UStruct* const Struct			  = Temp;

	TArray<FName> RowNames = DataTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

		UnloadStruct(RowPtr, Struct, UnloadCodes);
	}
}

#pragma endregion Unload

// References
#pragma region

void UCsLibrary_Load::GetReferencesReport_ClassProperty(FClassProperty* ClassProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
{
	if (UObject* const* Ptr = ClassProperty->ContainerPtrToValuePtr<UObject*>(StructValue))
	{
		FCsLibraryLoad_MemberInfo MemberInfo;

		const FString PropertyName = ClassProperty->GetName();
		const FString MemberPath   = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

		MemberInfo.SetName(PropertyName);
		MemberInfo.SetPath(MemberPath);
		MemberInfo.SetType(ClassProperty->MetaClass->GetName());
		
		if (const UObject* Object = *Ptr)
		{
			const bool ValidClass = ClassProperty->MetaClass->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint);

			const UClass* Class = Cast<UClass>(Object);

			if (ValidClass)
			{
				FSoftClassPath ClassPath(Class);

				const bool ValidPathRoot = !ClassPath.GetAssetPathString().StartsWith(TEXT("/Temp")) &&
										   !ClassPath.GetAssetPathString().StartsWith(TEXT("/Script"));

				if (ValidPathRoot)
				{
					OutReport.Hard.Add(MemberInfo, ClassPath);

					OutReport.AddToDepthList(ClassPath, Depth);
				}
			}

			if (!ClassProperty->MetaClass->HasAnyClassFlags(EClassFlags::CLASS_Abstract))
			{
				GetReferencesReport(Class, Object->GetClass(), MemberPath, OutReport, Depth + 1);
			}
		}
		/*
		else
		{
			OutReport.Hard.AddUnused(MemberInfo);
		}
		*/
	}
}

void UCsLibrary_Load::GetReferencesReport_ObjectProperty(FObjectProperty* ObjectProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
{
	if (UObject* const* Ptr = ObjectProperty->ContainerPtrToValuePtr<UObject*>(StructValue))
	{
		const FString PropertyName = ObjectProperty->GetName();
		const FString MemberPath   = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

		const bool ValidClass = ObjectProperty->PropertyClass->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint) ||
								ObjectProperty->PropertyClass == UDataTable::StaticClass() ||
								Cast<IInterface_AssetUserData>(ObjectProperty->PropertyClass) != nullptr;
		
		if (const UObject* Object = *Ptr)
		{
			if (ValidClass)
			{
				FSoftObjectPath ObjectPath(Object);

				const bool ValidName = ObjectPath.GetAssetName() != OutReport.Name &&
									   ObjectPath.GetAssetName() != OutReport.DefaultName;
				
				const bool ValidPathRoot = !ObjectPath.GetAssetPathString().StartsWith(TEXT("/Temp")) &&
										   !ObjectPath.GetAssetPathString().StartsWith(TEXT("/Script"));

				if (ValidName &&
					ValidPathRoot)
				{
					FCsLibraryLoad_MemberInfo MemberInfo;

					MemberInfo.SetName(PropertyName);
					MemberInfo.SetPath(MemberPath);
					MemberInfo.SetType(ObjectProperty->PropertyClass->GetName());

					OutReport.Hard.Add(MemberInfo, ObjectPath);

					OutReport.AddToDepthList(ObjectPath, Depth);
				}
			}
			
			// Subobjects
			TArray<UObject*> OutDefaultSubobjects;
			const_cast<UObject*>(Object)->GetDefaultSubobjects(OutDefaultSubobjects);

			for (UObject* O : OutDefaultSubobjects)
			{
				const FString SubobjectPath = FString::Printf(TEXT("%s.%s"), *MemberPath, *(O->GetName()));

				GetReferencesReport(O, O->GetClass(), SubobjectPath, OutReport, Depth + 1);
			}

			if (!ObjectProperty->PropertyClass->HasAnyClassFlags(EClassFlags::CLASS_Abstract))
			{
				if (ObjectProperty->PropertyClass == UDataTable::StaticClass())
				{
					UDataTable* const* DataTablePtr = ObjectProperty->ContainerPtrToValuePtr<UDataTable*>(StructValue);
					
					if (UDataTable* DataTable = *DataTablePtr)
					{
						const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
						UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
						UStruct* const Struct			  = Temp;

						TArray<FName> RowNames = DataTable->GetRowNames();

						for (const FName& RowName : RowNames)
						{
							uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

							const FString RowMemberPath = FString::Printf(TEXT("%s.%s[%s]"), *OuterName, *PropertyName, *(RowName.ToString()));

							GetReferencesReport(RowPtr, Struct, RowMemberPath, OutReport, Depth + 1);
						}
					}
				}
				else
				{
					GetReferencesReport(Object, Object->GetClass(), MemberPath, OutReport, Depth + 1);
				}
			}
		}
		/*
		else
		{
			if (ValidClass)
			{
				FRsLibraryLoad_MemberInfo MemberInfo;

				MemberInfo.SetName(PropertyName);
				MemberInfo.SetPath(MemberPath);
				MemberInfo.SetType(ObjectProperty->PropertyClass->GetName());

				OutReport.Hard.AddUnused(MemberInfo);
			}
		}
		*/
	}
}

void UCsLibrary_Load::GetReferencesReport_SoftClassProperty(FSoftClassProperty* SoftClassProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
{
	if (const FSoftObjectPtr* Ptr = SoftClassProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		FCsLibraryLoad_MemberInfo MemberInfo;

		const FString PropertyName = SoftClassProperty->GetName();
		const FString MemberPath   = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

		MemberInfo.SetName(PropertyName);
		MemberInfo.SetPath(MemberPath);
		MemberInfo.SetType(SoftClassProperty->MetaClass->GetName());

		const FSoftObjectPath ObjectPath = Ptr->ToSoftObjectPath();

		if (ObjectPath.IsValid())
		{
			UObject* O = Ptr->LoadSynchronous();

			if (UClass* Class = Cast<UClass>(O))
			{
				OutReport.Soft.Add(MemberInfo, ObjectPath);

				OutReport.AddToDepthList(ObjectPath, Depth);

				GetReferencesReport(Class->GetDefaultObject(), Class->StaticClass(), MemberPath, OutReport, Depth + 1);
			}
		}
		/*
		else
		{
			OutReport.Soft.AddUnused(MemberInfo);
		}
		*/
	}
}

void UCsLibrary_Load::GetReferencesReport_SoftObjectProperty(FSoftObjectProperty* SoftObjectProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
{
	if (const FSoftObjectPtr* Ptr = SoftObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		FCsLibraryLoad_MemberInfo MemberInfo;

		const FString PropertyName = SoftObjectProperty->GetName();
		const FString MemberPath   = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

		MemberInfo.SetName(PropertyName);
		MemberInfo.SetPath(MemberPath);
		MemberInfo.SetType(SoftObjectProperty->PropertyClass->GetName());

		const FSoftObjectPath ObjectPath = Ptr->ToSoftObjectPath();

		if (ObjectPath.IsValid())
		{
			if (UObject* O = Ptr->LoadSynchronous())
			{
				OutReport.Soft.Add(MemberInfo, ObjectPath);

				OutReport.AddToDepthList(ObjectPath, Depth);

				if (SoftObjectProperty->PropertyClass == UDataTable::StaticClass())
				{
					UDataTable* DataTable = Cast<UDataTable>(O);

					OutReport.AddToDepthList(FSoftObjectPath(DataTable), Depth + 1);

					const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
					UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
					UStruct* const Struct			  = Temp;

					TArray<FName> RowNames = DataTable->GetRowNames();

					for (const FName& RowName : RowNames)
					{
						uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

						const FString RowMemberPath = FString::Printf(TEXT("%s.%s[%s]"), *OuterName, *PropertyName, *(RowName.ToString()));

						GetReferencesReport(RowPtr, Struct, RowMemberPath, OutReport, Depth + 1);
					}
				}
				else
				{
					GetReferencesReport(O, O->GetClass(), MemberPath, OutReport, Depth + 1);
				}
			}
		}
		/*
		else
		{
			OutReport.Soft.AddUnused(MemberInfo);
		}
		*/
	}
}

void UCsLibrary_Load::GetReferencesReport_Function(UStruct* const& ParentStruct, UFunction* Function, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
{
	//Function->ScriptObjectReferences
	for (FProperty* Property = (FProperty*)Function->Children; Property; Property = (FProperty*)Property->Next)
	{
		const FString PropertyName = Property->GetName();

		UClass* Class = nullptr;
		
		// Class
		if (FClassProperty* ClassProperty = CastField<FClassProperty>(Property))
		{
			Class = ClassProperty->MetaClass;
		}
		// Object
		else
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			 Class = ObjectProperty->PropertyClass;
		}
		// SoftClass
		else
		if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			Class = SoftClassProperty->MetaClass;
		}
		// SoftObject
		else
		if (FSoftClassProperty* SoftObjectProperty = CastField<FSoftClassProperty>(Property))
		{
			Class = SoftObjectProperty->PropertyClass;
		}

		if (Class)
		{
			const bool ValidClass = Class != ParentStruct &&
									Class->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint);

			FSoftClassPath ClassPath(Class);

			const bool ValidName = ClassPath.GetAssetName() != OutReport.Name &&
								   ClassPath.GetAssetName() != OutReport.DefaultName;

			const bool ValidPathRoot = !ClassPath.GetAssetPathString().StartsWith(TEXT("/Temp")) &&
									   !ClassPath.GetAssetPathString().StartsWith(TEXT("/Script"));

			if (ValidClass &&
				ValidName &&
				ValidPathRoot)
			{
				FCsLibraryLoad_MemberInfo MemberInfo;

				const FString MemberPath  = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

				MemberInfo.SetName(PropertyName);
				MemberInfo.SetPath(MemberPath);
				MemberInfo.SetType(Class->GetName());

				OutReport.Hard.Add(MemberInfo, ClassPath);

				OutReport.AddToDepthList(ClassPath, Depth);
			}

			if (ValidClass)
			{
				const FString MemberPath = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

				GetReferencesReport(Class->GetDefaultObject(), Class, MemberPath, OutReport, Depth + 1);
			}
		}

		/*
		// TODO:
		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
		{
			for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
			{
				if (const uint8* Ptr = StructProperty->ContainerPtrToValuePtr<uint8>(Function, I))
				{
					const FString MemberPath = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

					GetReferencesReport(Ptr, StructProperty->Struct, MemberPath, OutReport);
				}
			}
			continue;
		}
		*/
	}
}

void UCsLibrary_Load::GetReferencesReport(const void* StructValue, UStruct* const& Struct, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
{
	for (TFieldIterator<FProperty> It(Struct); It; ++It)
	{
		FProperty* Property = CastField<FProperty>(*It);

		const FString PropertyName = Property->GetName();

		// Class
		if (FClassProperty* ClassProperty = CastField<FClassProperty>(Property))
		{
			GetReferencesReport_ClassProperty(ClassProperty, StructValue, OuterName, OutReport, Depth + 1);
			continue;
		}
		// Object
		if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
		{
			// Check for Material Expression that references Material.
			// This leads to infinite recursion. So, Skip.
			if (Struct->IsChildOf(UMaterialExpression::StaticClass()) &&
				ObjectProperty->PropertyClass == UMaterial::StaticClass())
			{
				continue;
			}

			if (ObjectProperty->PropertyClass == UDataTable::StaticClass())
			{
				UDataTable* const* DataTablePtr = ObjectProperty->ContainerPtrToValuePtr<UDataTable*>(StructValue);
				
				if (UDataTable* DataTable = *DataTablePtr)
				{
					OutReport.AddToDepthList(FSoftObjectPath(DataTable), Depth + 1);

					const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
					UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
					UStruct* const RowStruct		  = Temp;

					TArray<FName> RowNames = DataTable->GetRowNames();

					for (const FName& RowName : RowNames)
					{
						uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

						const FString MemberPath = FString::Printf(TEXT("%s.%s[%s]"), *OuterName, *PropertyName, *(RowName.ToString()));

						GetReferencesReport(RowPtr, RowStruct, MemberPath, OutReport, Depth + 1);
					}
				}
			}
			else
			{
				GetReferencesReport_ObjectProperty(ObjectProperty, StructValue, OuterName, OutReport, Depth + 1);
			}
			continue;
		}
		// SoftClass
		if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
		{
			GetReferencesReport_SoftClassProperty(SoftClassProperty, StructValue, OuterName, OutReport, Depth + 1);
			continue;
		}
		// SoftObject
		if (FSoftClassProperty* SoftObjectProperty = CastField<FSoftClassProperty>(Property))
		{
			GetReferencesReport_SoftObjectProperty(SoftObjectProperty, StructValue, OuterName, OutReport, Depth + 1);
			continue;
		}
		// Struct
		if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
		{
			if (PropertyName.StartsWith(TEXT("UberGraphFrame")))
				continue;

			for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
			{
				if (const uint8* Ptr = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I))
				{
					const FString MemberPath = FString::Printf(TEXT("%s.%s"), *OuterName, *PropertyName);

					GetReferencesReport(Ptr, StructProperty->Struct, MemberPath, OutReport, Depth + 1);
				}
			}
			continue;
		}
	}
	
	// Iterate through Functions
	for (UFunction* Function : TFieldRange<UFunction>(Struct))
	{
		const FString FunctionName = Function->GetName();

		if (FunctionName.StartsWith(TEXT("ExecuteUbergraph")))
			continue;

		const FString FunctionPath = FString::Printf(TEXT("%s.%s"), *(Struct->GetName()), *FunctionName);

		if (!OutReport.HasVisitedFunction(FunctionPath))
		{
			OutReport.VisitFunction(FunctionPath);

			const FString Name = FString::Printf(TEXT("%s.%s"), *OuterName, *FunctionName);

			GetReferencesReport_Function(Struct, Function, Name, OutReport, Depth + 1);
		}
	}
}

#pragma endregion References

// Default Object
#pragma region

UObject* UCsLibrary_Load::GetDefaultObjectChecked(const FString& Context, const TSubclassOf<UObject>& SubclassOf)
{
	UObject* O = SubclassOf.Get();

	checkf(O, TEXT("%s: SubclassOf is NULL."), *Context);

	// Blueprint
	if (UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O))
	{
		//if (UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy))
		UBlueprintCore* BpC = nullptr;
		if (BpC)
		{
			if (UClass* Class = BpC->GeneratedClass.Get())
			{
				UObject* DOb = Class->GetDefaultObject();

				checkf(DOb, TEXT("%s: Failed to get DefaultObject from Object: %s with Class: %s."), *Context, *(O->GetName()), *(Class->GetName()));

				return DOb;
			}
		}
		else
		//if (UClass* Class = Cast<UClass>(BpGC->ClassGeneratedBy))
		if (0)
		{
			UClass* Class = nullptr;

			UObject* DOb = Class->GetDefaultObject();

			checkf(DOb, TEXT("%s: Failed to get DefaultObject from Object: %s with Class: %s."), *Context, *(O->GetName()), *(Class->GetName()));

			return DOb;
		}
		else
		{
			UObject* DOb = BpGC->GetDefaultObject();

			checkf(DOb, TEXT("%s: Failed to get DefaultObject from Object: %s with Class: %s."), *Context, *(O->GetName()), *(BpGC->GetName()));

			return DOb;
		}
	}
	else
	{
		UClass* Class = O->GetClass();

		checkf(Class, TEXT("%s: Failed to Class from Object: %s."), *Context, *(O->GetName()));

		UObject* DOb = Class->GetDefaultObject();

		checkf(DOb, TEXT("%s: Failed to get DefaultObject from Object: %s with Class: %s."), *Context, *(O->GetName()), *(Class->GetName()));

		return DOb;
	}
	checkf(0, TEXT("%s: Failed to get DefaultObject from Object: %s."), *Context, *(O->GetName()))
	return nullptr;
}

#pragma endregion Default Object