// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Load/CsLibrary_Load.h"
#include "CsCore.h"

// Sound
#include "Sound/SoundCue.h"
// FX
#include "Particles/ParticleSystem.h"
// Data
#include "Data/CsData.h"
#include "Engine/DataTable.h"
// Material
#include "Classes/Materials/Material.h"
#include "Classes/Materials/MaterialExpression.h"
#include "Classes/Materials/MaterialFunction.h"
// Graph
#include "EdGraph/EdGraphNode.h"
// Blueprint
#include "Engine/BlueprintGeneratedClass.h"

UCsLibrary_Load::UCsLibrary_Load(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// DataTable
#pragma region

void UCsLibrary_Load::GetDataTables(const void* StructValue, UStruct* const& Struct, TMap<FName, UDataTable*>& OutDataTableMap)
{
	// Iterate through Properties
	for (TPropertyValueIterator<UProperty> It(Struct, StructValue); It; ++It)
	{
		UProperty* Property		  = It.Key();
		const void* PropertyValue = It.Value();

		// TSoftObjectPtr
		if (const USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(Property))
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
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
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
	for (TPropertyValueIterator<UProperty> It(Struct, StructValue); It; ++It)
	{
		UProperty* Property		  = It.Key();
		const void* PropertyValue = It.Value();

		// TSoftClassPtr
		if (const USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
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
		if (const USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(Property))
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
		if (const UStructProperty* StructProperty = Cast<UStructProperty>(Property))
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
		if (const UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
		{
			// TODO: Look at FScriptArray, FScriptArrayHelper
			continue;
		}
		// Map
		if (const UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
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
	for (TPropertyValueIterator<UProperty> It(Struct, StructValue); It; ++It)
	{
		UProperty* Property		  = It.Key();
		const void* PropertyValue = It.Value();

		// TSoftClassPtr
		if (const USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
		{
			if (const TSoftClassPtr<UObject>* Ptr = reinterpret_cast<const TSoftClassPtr<UObject>*>(PropertyValue))
			{
				const FSoftObjectPath& Path = Ptr->ToSoftObjectPath();

				if (Path.IsValid())
				{
					OutObjectPathMap.FindOrAdd(Path.GetAssetPathName()) = Path;
					// TODO: Load SoftClassPtr and GetObjectPaths from that. Have an optional enum for recursive look up with load
				}
			}
			continue;
		}
		// TSoftObjectPtr
		if (const USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(Property))
		{
			if (const TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<const TSoftObjectPtr<UObject>*>(PropertyValue))
			{
				const FSoftObjectPath& Path = Ptr->ToSoftObjectPath();

				if (Path.IsValid())
					OutObjectPathMap.FindOrAdd(Path.GetAssetPathName()) = Path;
			}
			continue;
		}
		// Struct
		if (const UStructProperty* StructProperty = Cast<UStructProperty>(Property))
		{
			// SoftClassPath
			if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
			{
				if (const FSoftClassPath* Ptr = reinterpret_cast<const FSoftClassPath*>(PropertyValue))
				{
					if (Ptr->IsValid())
						OutObjectPathMap.FindOrAdd(Ptr->GetAssetPathName()) = *Ptr;
				}
				continue;
			}
			// SoftObjectPath
			if (StructProperty->Struct == TBaseStructure<FSoftClassPath>::Get())
			{
				if (const FSoftObjectPath* Ptr = reinterpret_cast<const FSoftObjectPath*>(PropertyValue))
				{
					if (Ptr->IsValid())
						OutObjectPathMap.FindOrAdd(Ptr->GetAssetPathName()) = *Ptr;
				}
				continue;
			}
			continue;
		}
		// Array
		if (const UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
		{
			// TODO: Look at FScriptArray, FScriptArrayHelper
			continue;
		}
		// Map
		if (const UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
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

bool UCsLibrary_Load::GetSoftObjectPaths_SoftObjectPath(UProperty* Property, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetSoftObjectPaths& Result)
{
	FSoftObjectPath Path;
	FString StructName = TEXT("");
	bool DoRecursion = false;

	// TSoftClassPtr
	if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
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
	if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(Property))
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
	if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
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

bool UCsLibrary_Load::GetSoftObjectPaths_Array_SoftObjectPath(UArrayProperty* ArrayProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetSoftObjectPaths& Result)
{
	FString StructName = TEXT("");
	bool DoRecursion = false;

	// TSoftClassPtr
	if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
	{
		StructName  = SoftClassProperty->MetaClass->GetName();
		DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetClass);
	}
	// TSoftObjectPtr
	else
	if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
	{
		StructName  = SoftObjectProperty->PropertyClass->GetName();
		DoRecursion = CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetObject);
	}
	// Struct
	else
	if (UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
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
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
		{
			TSoftClassPtr<UObject>* Ptr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));
			Path						= Ptr->ToSoftObjectPath();
		}
		// TSoftObjectPtr
		else
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
		{
			TSoftObjectPtr<UObject>* Ptr = reinterpret_cast<TSoftObjectPtr<UObject>*>(Helper.GetRawPtr(I));
			Path						 = Ptr->ToSoftObjectPath();
		}
		// Struct
		else
		if (UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
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
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		// TSoftClassPtr | TSoftObjectPtr | FSoftClassPath | FSoftObjectPath
		if (GetSoftObjectPaths_SoftObjectPath(Property, StructValue, OuterName, Result))
			continue;

		// Class
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(Property))
		{
			if (CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetClass))
			{
				UObject* const* Object = ClassProperty->ContainerPtrToValuePtr<UObject*>(StructValue);

				GetSoftObjectPaths(*Object, (*Object)->GetClass(), PropertyName, Result);
			}
			continue;
		}
		// Object
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
		{
			if (CS_TEST_BITFLAG(Result.Code, ECsLibraryLoad_GetSoftObjectPaths_Code::RecursiveGetObject))
			{
				UObject* const* Object = ObjectProperty->ContainerPtrToValuePtr<UObject*>(StructValue);

				GetSoftObjectPaths(*Object, (*Object)->GetClass(), PropertyName, Result);
			}
			continue;
		}
		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
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
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr | TSoftObjectPtr | FSoftClassPath | FSoftObjectPath
			if (GetSoftObjectPaths_Array_SoftObjectPath(ArrayProperty, StructValue, OuterName, Result))
				continue;

			// Struct
			if (UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
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

void UCsLibrary_Load::GetObjectPaths_Class_Internal(UClass* Class, FCsLibraryLoad_GetObjectPaths& OutPaths)
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

void UCsLibrary_Load::GetObjectPaths_ClassProperty(UClassProperty* ClassProperty, const void* StructValue, FCsLibraryLoad_GetObjectPaths& OutPaths)
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

void UCsLibrary_Load::GetObjectPaths_ClassProperty_Internal(UClass* MetaClass, const UObject* Object, FCsLibraryLoad_GetObjectPaths& OutPaths)
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

void UCsLibrary_Load::GetObjectPaths_ObjectProperty(UObjectProperty* ObjectProperty, const void* StructValue, FCsLibraryLoad_GetObjectPaths& OutPaths)
{
	if (UObject* const* Ptr = ObjectProperty->ContainerPtrToValuePtr<UObject*>(StructValue))
	{
		if (const UObject* Object = *Ptr)
		{
			GetObjectPaths_ObjectProperty_Internal(ObjectProperty->PropertyClass, Object, OutPaths);
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_ObjectProperty_Internal(UClass* PropertyClass, const UObject* Object, FCsLibraryLoad_GetObjectPaths& OutPaths)
{
	const bool ValidClass = PropertyClass->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint) ||
							PropertyClass == UDataTable::StaticClass() ||
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

void UCsLibrary_Load::GetObjectPaths_SoftClassProperty(USoftClassProperty* SoftClassProperty, const void* StructValue, FCsLibraryLoad_GetObjectPaths& OutPaths)
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

void UCsLibrary_Load::GetObjectPaths_SoftObjectProperty(USoftObjectProperty* SoftObjectProperty, const void* StructValue, FCsLibraryLoad_GetObjectPaths& OutPaths)
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

void UCsLibrary_Load::GetObjectPaths_Struct(UStruct* Struct, FCsLibraryLoad_GetObjectPaths& OutPaths)
{
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		UClass* Class = nullptr;
		
		// Class
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(Property))
		{
			Class = ClassProperty->MetaClass;
		}
		// Object
		else
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
		{
			 Class = ObjectProperty->PropertyClass;
		}
		// SoftClass
		else
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
		{
			Class = SoftClassProperty->MetaClass;
		}
		// SoftObject
		else
		if (USoftClassProperty* SoftObjectProperty = Cast<USoftClassProperty>(Property))
		{
			Class = SoftObjectProperty->PropertyClass;
		}

		if (Class)
		{
			GetObjectPaths_Class_Internal(Class, OutPaths);
			continue;
		}

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
		{
			GetObjectPaths_Struct(StructProperty->Struct, OutPaths);
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
		{
			Class = nullptr;
		
			// Class
			if (UClassProperty* InnerClassProperty = Cast<UClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerClassProperty->MetaClass;
			}
			// Object
			else
			if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
			{
				 Class = InnerObjectProperty->PropertyClass;
			}
			// SoftClass
			else
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerSoftClassProperty->MetaClass;
			}
			// SoftObject
			else
			if (USoftClassProperty* InnerSoftObjectProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerSoftObjectProperty->PropertyClass;
			}

			if (Class)
			{
				GetObjectPaths_Class_Internal(Class, OutPaths);
				continue;
			}

			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				GetObjectPaths_Struct(InnerStructProperty->Struct, OutPaths);
				continue;
			}
			continue;
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_Function(UFunction* Function, FCsLibraryLoad_GetObjectPaths& OutPaths)
{
	for (UObject* Object : Function->ScriptObjectReferences)
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

	for (UProperty* Property = (UProperty*)Function->Children; Property; Property = (UProperty*)Property->Next)
	{
		const FString PropertyName = Property->GetName();

		UClass* Class = nullptr;
		
		// Class
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(Property))
		{
			Class = ClassProperty->MetaClass;
		}
		// Object
		else
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
		{
			 Class = ObjectProperty->PropertyClass;
		}
		// SoftClass
		else
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
		{
			Class = SoftClassProperty->MetaClass;
		}
		// SoftObject
		else
		if (USoftClassProperty* SoftObjectProperty = Cast<USoftClassProperty>(Property))
		{
			Class = SoftObjectProperty->PropertyClass;
		}

		if (Class)
		{
			GetObjectPaths_Class_Internal(Class, OutPaths);
			continue;
		}

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
		{
			GetObjectPaths_Struct(StructProperty->Struct, OutPaths);
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
		{
			Class = nullptr;
		
			// Class
			if (UClassProperty* InnerClassProperty = Cast<UClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerClassProperty->MetaClass;
			}
			// Object
			else
			if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
			{
				 Class = InnerObjectProperty->PropertyClass;
			}
			// SoftClass
			else
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerSoftClassProperty->MetaClass;
			}
			// SoftObject
			else
			if (USoftClassProperty* InnerSoftObjectProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				Class = InnerSoftObjectProperty->PropertyClass;
			}

			if (Class)
			{
				GetObjectPaths_Class_Internal(Class, OutPaths);
				continue;
			}

			// Struct
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				GetObjectPaths_Struct(InnerStructProperty->Struct, OutPaths);
				continue;
			}
			continue;
		}
	}
}

void UCsLibrary_Load::GetObjectPaths_Internal(const void* StructValue, UStruct* const& Struct, FCsLibraryLoad_GetObjectPaths& OutPaths)
{
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();
		
		// Class
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(Property))
		{
			GetObjectPaths_ClassProperty(ClassProperty, StructValue, OutPaths);
			continue;
		}
		// Object
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
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
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
		{
			GetObjectPaths_SoftClassProperty(SoftClassProperty, StructValue, OutPaths);
			continue;
		}
		// SoftObject
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(Property))
		{
			GetObjectPaths_SoftObjectProperty(SoftObjectProperty, StructValue, OutPaths);
			continue;
		}
		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
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
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Property))
		{
			FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

			const int32 Count = Helper.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				uint8* Ptr = Helper.GetRawPtr(I);

				// Class
				if (UClassProperty* InnerClassProperty = Cast<UClassProperty>(ArrayProperty->Inner))
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
				if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
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
				if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
				{
					TSoftClassPtr<UObject>* ObjectPtr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));

					if (ObjectPtr->IsValid())
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
				if (USoftClassProperty* InnerSoftObjectProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
				{
					TSoftObjectPtr<UObject>* ObjectPtr = reinterpret_cast<TSoftObjectPtr<UObject>*>(Helper.GetRawPtr(I));

					if (ObjectPtr->IsValid())
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
				if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
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

void UCsLibrary_Load::GetObjectPaths(const void* StructValue, UStruct* const& Struct, FCsLibraryLoad_GetObjectPaths& OutPaths)
{
	OutPaths.VisitPointer(Struct->GetFName(), StructValue);

	GetObjectPaths_Internal(StructValue, Struct, OutPaths);

	OutPaths.Resolve();
}

void UCsLibrary_Load::GetObjectPaths(UObject* StructValue, UStruct* const& Struct, FCsLibraryLoad_GetObjectPaths& OutPaths)
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
								// MemberName + TEXT("_LoadFlags")
	const FString FlagMemberName = MemberName + ECsLoadCached::Str::_LoadFlags;

	if (UIntProperty* IntProperty = FindField<UIntProperty>(Struct, *FlagMemberName))
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
}

void UCsLibrary_Load::LoadSoftClassProperty(USoftClassProperty* SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
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

		if (UObjectProperty* InternalObjectProperty = FindField<UObjectProperty>(Struct, *InternalMemberName))
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
							if (!Data->IsLoaded())
								Data->Load(LoadFlags);
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

		if (UClassProperty* InternalClassProperty = FindField<UClassProperty>(Struct, *InternalClassName))
		{
			if (UObject** Object = InternalClassProperty->GetPropertyValuePtr_InContainer(StructValue))
			{
				*Object = Member->LoadSynchronous();
			}
		}

		// Check if a "SubclassOf" member exists (i.e. MemberName + _SubclassOf)

		// MemberName + TEXT("_SubclassOf")
		const FString InternalSubclassOfName = MemberName + ECsLoadCached::Str::_SubclassOf;

		if (UClassProperty* InternalSubclassOfProperty = FindField<UClassProperty>(Struct, *InternalSubclassOfName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftClassProperty->MetaClass == InternalSubclassOfProperty->MetaClass)
			{
				if (UObject** Object = InternalSubclassOfProperty->GetPropertyValuePtr_InContainer(StructValue))
				{
					*Object = Member->LoadSynchronous();
				}
			}
		}
	}
}

void UCsLibrary_Load::LoadArraySoftClassProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
{
	if (!CanLoad(StructValue, Struct, MemberName, LoadFlags, LoadCodes))
		return;

	// Check if an "Internal" member exists (i.e. MemberName + _Internal)

									// MemberName + TEXT("_Internal")
	const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

	if (UArrayProperty* InternalArrayProperty = FindField<UArrayProperty>(Struct, *InternalMemberName))
	{
		if (USoftObjectProperty* InternalSoftObjectProperty = Cast<USoftObjectProperty>(InternalArrayProperty->Inner))
		{
			USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner);

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
								if (!Data->IsLoaded())
									Data->Load(LoadFlags);
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

	if (UArrayProperty* InternalArrayProperty = FindField<UArrayProperty>(Struct, *InternalClassName))
	{
		if (USoftClassProperty* InternalSoftClassProperty = Cast<USoftClassProperty>(InternalArrayProperty->Inner))
		{
			USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner);

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

void UCsLibrary_Load::LoadSoftObjectProperty(USoftObjectProperty* SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
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

		if (UObjectProperty* InternalObjectProperty = FindField<UObjectProperty>(Struct, *InternalMemberName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftObjectProperty->PropertyClass == InternalObjectProperty->PropertyClass)
			{
				if (UObject** Internal = InternalObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
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

void UCsLibrary_Load::LoadArraySoftObjectProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& LoadFlags, const int32& LoadCodes)
{
	if (!CanLoad(StructValue, Struct, MemberName, LoadFlags, LoadCodes))
		return;

	// Check if an "Internal" member exists (i.e. MemberName + _Internal)

									// MemberName + TEXT("_Internal")
	const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

	if (UArrayProperty* InternalArrayProperty = FindField<UArrayProperty>(Struct, *InternalMemberName))
	{
		if (USoftObjectProperty* InternalSoftObjectProperty = Cast<USoftObjectProperty>(InternalArrayProperty->Inner))
		{
			USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner);

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

					*InternalPtr = nullptr;

					if (Ptr->IsValid())
						*InternalPtr = Ptr->LoadSynchronous();

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

void UCsLibrary_Load::LoadClassProperty(UClassProperty* ClassProperty, void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes)
{
	if (UObject** Object = ClassProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		if (*Object)
		{
			UClass* Class = Cast<UClass>(*Object);
			UObject* DOb = Class->GetDefaultObject();

			// ICsData
			if (ICsData* Data = Cast<ICsData>(DOb))
			{
				if (!Data->IsLoaded())
					Data->Load(LoadFlags);
			}
		}
	}
}

void UCsLibrary_Load::LoadArrayClassProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes)
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
				if (!Data->IsLoaded())
					Data->Load(LoadFlags);
			}
		}
	}
}

void UCsLibrary_Load::LoadArrayObjectProperty(UArrayProperty* ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	UObjectProperty* ObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner);

	for (int32 I = 0; I < Count; ++I)
	{
		uint8* Ptr = Helper.GetRawPtr(I);

		LoadStruct(Ptr, ObjectProperty->PropertyClass, LoadFlags, LoadCodes);
	}
}

void UCsLibrary_Load::LoadArrayStructProperty(UArrayProperty* ArrayProperty, void* StructValue, const int32& LoadFlags, const int32& LoadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

	for (int32 I = 0; I < Count; ++I)
	{
		uint8* Ptr = Helper.GetRawPtr(I);

		LoadStruct(Ptr, StructProperty->Struct, LoadFlags, LoadCodes);
	}
}

void UCsLibrary_Load::LoadStruct(void* StructValue, UStruct* const& Struct, const int32& LoadFlags, const int32& LoadCodes)
{
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
		{
			LoadSoftClassProperty(SoftClassProperty, StructValue, Struct, PropertyName, NCsLoadFlags::All, LoadCodes);
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(Property))
		{
			LoadSoftObjectProperty(SoftObjectProperty, StructValue, Struct, PropertyName, NCsLoadFlags::All, LoadCodes);
			continue;
		}
		// Class
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(Property))
		{
			LoadClassProperty(ClassProperty, StructValue, Struct, LoadFlags, LoadCodes);
			continue;
		}
		// Object
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
		{
			// Recursive Load DataTable
			if (ObjectProperty->PropertyClass == UDataTable::StaticClass() &&
				CS_TEST_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::RecursiveLoadDataTable))
			{
				UDataTable** DataTable = ObjectProperty->ContainerPtrToValuePtr<UDataTable*>(StructValue);

				LoadDataTable(*DataTable, LoadFlags, LoadCodes);
			}
			continue;
		}
		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
		{
			for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
			{
				uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I);

				LoadStruct(Value, StructProperty->Struct, LoadFlags, LoadCodes);
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				LoadArraySoftClassProperty(ArrayProperty, StructValue, Struct, PropertyName, NCsLoadFlags::All, LoadCodes);
				continue;
			}
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				LoadArraySoftObjectProperty(ArrayProperty, StructValue, Struct, PropertyName, NCsLoadFlags::All, LoadCodes);
				continue;
			}
			// Class
			if (UClassProperty* InnerClassProperty = Cast<UClassProperty>(ArrayProperty->Inner))
			{
				LoadArrayClassProperty(ArrayProperty, StructValue, Struct, NCsLoadFlags::All, LoadCodes);
				continue;
			}
			// Object
			if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
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
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
			{
				LoadArrayStructProperty(ArrayProperty, StructValue, LoadFlags, LoadCodes);
				continue;
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

#pragma endregion Load

// Unload
#pragma region

void UCsLibrary_Load::UnloadSoftClassProperty(USoftClassProperty* SoftClassProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes)
{
	if (FSoftObjectPtr* Member = SoftClassProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		if (!Member->ToSoftObjectPath().IsValid())
			return;

		Member->ResetWeakPtr();

		// Check if an "Internal" member exists (i.e. MemberName + _Internal)

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UObjectProperty* InternalObjectProperty = FindField<UObjectProperty>(Struct, *InternalMemberName))
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

		if (UClassProperty* InternalClassProperty = FindField<UClassProperty>(Struct, *InternalClassName))
		{
			if (UObject** Object = InternalClassProperty->GetPropertyValuePtr_InContainer(StructValue))
			{
				*Object = nullptr;
			}
		}

		// Check if a "SubclassOf" member exists (i.e. MemberName + _SubclassOf)

		// MemberName + TEXT("_SubclassOf")
		const FString InternalSubclassOfName = MemberName + ECsLoadCached::Str::_SubclassOf;

		if (UClassProperty* InternalSubclassOfProperty = FindField<UClassProperty>(Struct, *InternalSubclassOfName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftClassProperty->MetaClass == InternalSubclassOfProperty->MetaClass)
			{
				if (UObject** Object = InternalSubclassOfProperty->GetPropertyValuePtr_InContainer(StructValue))
				{
					*Object = nullptr;
				}
			}
		}
	}
}

void UCsLibrary_Load::UnloadArraySoftClassProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes)
{
	// Check if an "Internal" member exists (i.e. MemberName + _Internal)

									// MemberName + TEXT("_Internal")
	const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

	if (UArrayProperty* InternalArrayProperty = FindField<UArrayProperty>(Struct, *InternalMemberName))
	{
		if (USoftObjectProperty* InternalSoftObjectProperty = Cast<USoftObjectProperty>(InternalArrayProperty->Inner))
		{
			USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner);

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

	if (UArrayProperty* InternalArrayProperty = FindField<UArrayProperty>(Struct, *InternalClassName))
	{
		if (USoftClassProperty* InternalSoftClassProperty = Cast<USoftClassProperty>(InternalArrayProperty->Inner))
		{
			USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner);

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

void UCsLibrary_Load::UnloadSoftObjectProperty(USoftObjectProperty* SoftObjectProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes)
{
	if (FSoftObjectPtr* Member = SoftObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
	{
		if (!Member->ToSoftObjectPath().IsValid())
			return;

		Member->ResetWeakPtr();

		// Check if an "Internal" member exists (i.e. MemberName + _Internal)

										// MemberName + TEXT("_Internal")
		const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

		if (UObjectProperty* InternalObjectProperty = FindField<UObjectProperty>(Struct, *InternalMemberName))
		{
			// Check Member is the same type as the Member_Internal
			if (SoftObjectProperty->PropertyClass == InternalObjectProperty->PropertyClass)
			{
				if (UObject** Internal = InternalObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
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

void UCsLibrary_Load::UnloadArraySoftObjectProperty(UArrayProperty* ArrayProperty, void* StructValue, UStruct* const& Struct, const FString& MemberName, const int32& UnloadCodes)
{
	// Check if an "Internal" member exists (i.e. MemberName + _Internal)

									// MemberName + TEXT("_Internal")
	const FString InternalMemberName = MemberName + ECsLoadCached::Str::_Internal;

	if (UArrayProperty* InternalArrayProperty = FindField<UArrayProperty>(Struct, *InternalMemberName))
	{
		if (USoftObjectProperty* InternalSoftObjectProperty = Cast<USoftObjectProperty>(InternalArrayProperty->Inner))
		{
			USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner);

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

void UCsLibrary_Load::UnloadArrayObjectProperty(UArrayProperty* ArrayProperty, void* StructValue, const int32& UnloadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	UObjectProperty* ObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner);

	for (int32 I = 0; I < Count; ++I)
	{
		uint8* Ptr = Helper.GetRawPtr(I);

		UnloadStruct(Ptr, ObjectProperty->PropertyClass, UnloadCodes);
	}
}

void UCsLibrary_Load::UnloadArrayStructProperty(UArrayProperty* ArrayProperty, void* StructValue, const int32& UnloadCodes)
{
	FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

	const int32 Count = Helper.Num();

	UStructProperty* StructProperty = Cast<UStructProperty>(ArrayProperty->Inner);

	for (int32 I = 0; I < Count; ++I)
	{
		uint8* Ptr = Helper.GetRawPtr(I);

		UnloadStruct(Ptr, StructProperty->Struct, UnloadCodes);
	}
}

void UCsLibrary_Load::UnloadStruct(void* StructValue, UStruct* const& Struct, const int32& UnloadCodes)
{
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		// TSoftClassPtr
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
		{
			UnloadSoftClassProperty(SoftClassProperty, StructValue, Struct, PropertyName, UnloadCodes);
			continue;
		}
		// TSoftObjectPtr
		if (USoftObjectProperty* SoftObjectProperty = Cast<USoftObjectProperty>(Property))
		{
			UnloadSoftObjectProperty(SoftObjectProperty, StructValue, Struct, PropertyName, UnloadCodes);
			continue;
		}
		// Object
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
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
		if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
		{
			for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
			{
				uint8* Value = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I);

				UnloadStruct(Value, StructProperty->Struct, UnloadCodes);
			}
			continue;
		}
		// Array
		if (UArrayProperty* ArrayProperty = Cast<UArrayProperty>(*It))
		{
			// TSoftClassPtr
			if (USoftClassProperty* InnerSoftClassProperty = Cast<USoftClassProperty>(ArrayProperty->Inner))
			{
				UnloadArraySoftClassProperty(ArrayProperty, StructValue, Struct, PropertyName, UnloadCodes);
				continue;
			}
			// TSoftObjectPtr
			if (USoftObjectProperty* InnerSoftObjectProperty = Cast<USoftObjectProperty>(ArrayProperty->Inner))
			{
				UnloadArraySoftObjectProperty(ArrayProperty, StructValue, Struct, PropertyName, UnloadCodes);
				continue;
			}
			// Object
			if (UObjectProperty* InnerObjectProperty = Cast<UObjectProperty>(ArrayProperty->Inner))
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
			if (UStructProperty* InnerStructProperty = Cast<UStructProperty>(ArrayProperty->Inner))
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

void UCsLibrary_Load::GetReferencesReport_ClassProperty(UClassProperty* ClassProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
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

void UCsLibrary_Load::GetReferencesReport_ObjectProperty(UObjectProperty* ObjectProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
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

void UCsLibrary_Load::GetReferencesReport_SoftClassProperty(USoftClassProperty* SoftClassProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
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

void UCsLibrary_Load::GetReferencesReport_SoftObjectProperty(USoftObjectProperty* SoftObjectProperty, const void* StructValue, const FString& OuterName, FCsLibraryLoad_GetReferencesReport& OutReport, int32 Depth)
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
	for (UProperty* Property = (UProperty*)Function->Children; Property; Property = (UProperty*)Property->Next)
	{
		const FString PropertyName = Property->GetName();

		UClass* Class = nullptr;
		
		// Class
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(Property))
		{
			Class = ClassProperty->MetaClass;
		}
		// Object
		else
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
		{
			 Class = ObjectProperty->PropertyClass;
		}
		// SoftClass
		else
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
		{
			Class = SoftClassProperty->MetaClass;
		}
		// SoftObject
		else
		if (USoftClassProperty* SoftObjectProperty = Cast<USoftClassProperty>(Property))
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
	for (TFieldIterator<UProperty> It(Struct); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString PropertyName = Property->GetName();

		// Class
		if (UClassProperty* ClassProperty = Cast<UClassProperty>(Property))
		{
			GetReferencesReport_ClassProperty(ClassProperty, StructValue, OuterName, OutReport, Depth + 1);
			continue;
		}
		// Object
		if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
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
		if (USoftClassProperty* SoftClassProperty = Cast<USoftClassProperty>(Property))
		{
			GetReferencesReport_SoftClassProperty(SoftClassProperty, StructValue, OuterName, OutReport, Depth + 1);
			continue;
		}
		// SoftObject
		if (USoftClassProperty* SoftObjectProperty = Cast<USoftClassProperty>(Property))
		{
			GetReferencesReport_SoftObjectProperty(SoftObjectProperty, StructValue, OuterName, OutReport, Depth + 1);
			continue;
		}
		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
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