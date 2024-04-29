// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Property.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Struct
#include "UObject/Class.h"

namespace NCsProperty
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, FindPropertyByName);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, FindStructPropertyByName);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, FindClassPropertyByName);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, FindObjectPropertyByName);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, GetObjectPropertyValue);
			}
		}
	}

	#define LogLevel void(*Log)(const FString&) /*=&FCsLog::Warning*/

	FString FLibrary::PrintStructName(const UStruct* Struct)
	{
		return Struct->GetName();
	}

	FString FLibrary::PrintPropertyClassName(const FProperty* Property)
	{
		return Property->GetClass()->GetName();
	}

	FString FLibrary::PrintPropertyStructName(const FStructProperty* Property)
	{
		return Property->Struct->GetName();
	}

	// Find
	#pragma region

	FProperty* FLibrary::FindPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(Struct)

		CS_IS_NAME_NONE_CHECKED(PropertyName)

		FProperty* Property = Struct->FindPropertyByName(PropertyName);
		Property			= Property ? Property : Struct->CustomFindProperty(PropertyName);

		checkf(Property, TEXT("%s: Failed to find Property with name: %s from Struct: %s."), *Context, *(PropertyName.ToString()), *(Struct->GetName()));
		return Property;
	}

	FProperty* FLibrary::FindPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(Struct)
		CS_IS_NAME_NONE_RET_NULL(PropertyName)

		FProperty* Property = Struct->FindPropertyByName(PropertyName);
		Property			= Property ? Property : Struct->CustomFindProperty(PropertyName);

		if (!Property)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Property with name: %s from Struct: %s."), *Context, *(PropertyName.ToString()), *(Struct->GetName())));
		}
		return  Property;
	}

		// Bool
	#pragma region

	FBoolProperty* FLibrary::FindBoolPropertyByPath(const FString& Context, const UStruct* Struct, const FString& Path, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(Struct)
		CS_IS_STRING_EMPTY_RET_NULL(Path)

		TArray<FString> PropertyNames;
		Path.ParseIntoArray(PropertyNames, TEXT("."), 1);

		if (PropertyNames.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
			return nullptr;
		}

		const int32 Count = PropertyNames.Num();
		int32 I = 0;

		UStruct* CurrentStruct	   = const_cast<UStruct*>(Struct);
		FProperty* CurrentProperty = nullptr;

		while (I < Count)
		{
			const FString& PropertyName = PropertyNames[I];

			if (I < (Count - 2))
			{
				// Struct
				FStructProperty* StructProperty = FindStructPropertyByName(Context, CurrentStruct, FName(*PropertyName), Log);
				CurrentProperty					= StructProperty;

				if (StructProperty->ArrayDim == 1)
				{
					CurrentStruct = StructProperty->Struct;
				}
				else
				{
				}
			}
			else
			if (I < (Count - 1))
			{
				return FindPropertyByName<FBoolProperty>(Context, CurrentStruct, FName(*PropertyName), Log);
			}
			++I;
		}
		return nullptr;
	}

	#pragma endregion Bool

		// Enum
	#pragma region

	FByteProperty* FLibrary::FindEnumPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType)
	{
		FByteProperty* ByteProperty = FindPropertyByNameChecked<FByteProperty>(Context, Struct, PropertyName);

		checkf(!EnumCppType.IsEmpty(), TEXT("%s: EnumCppyType is EMPTY."), *Context);

		checkf(ByteProperty->IsEnum(), TEXT("%s: %s.%s is NOT an Enum."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));

		checkf(ByteProperty->Enum->CppType.Contains(EnumCppType), TEXT("%s: %s.%s is NOT of type: EnumType."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));

		return ByteProperty;
	}

	FByteProperty* FLibrary::FindEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel)
	{
		FByteProperty* ByteProperty = FindPropertyByName<FByteProperty>(Context, Struct, PropertyName);

		if (!ByteProperty)
			return nullptr;

		if (EnumCppType.IsEmpty())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: EnumCppyType is EMPTY."), *Context));
			return nullptr;
		}

		if (!ByteProperty->IsEnum())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT an Enum."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}

		if (!ByteProperty->Enum->CppType.Contains(EnumCppType))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT of type: EnumType."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}
		return ByteProperty;
	}

	#pragma endregion Enum

		// Struct
	#pragma region

	FStructProperty* FLibrary::FindStructPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FProperty* Property   = FindPropertyByNameChecked(Context, Struct, PropertyName);
		FStructProperty* Prop = CastField<FStructProperty>(Property);

		checkf(Prop, TEXT("%s: %s.%s is NOT a struct."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Prop;
	}

	FStructProperty* FLibrary::FindStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FStructProperty* Prop = CastField<FStructProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a struct."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	bool FLibrary::HasStructProperty(const FString& Context, const UStruct* Struct, const UStruct* SearchStruct, LogLevel)
	{
		CS_IS_PTR_NULL(Struct)
		CS_IS_PTR_NULL(SearchStruct)

		for (TFieldIterator<FStructProperty> It(Struct); It; ++It)
		{
			FStructProperty* StructProperty = *It;

			if (StructProperty->Struct == SearchStruct)
				return true;
			if (HasStructProperty(Context, StructProperty->Struct, SearchStruct, nullptr))
				return true;
		}

			// Iterate through Functions
		for (UFunction* Function : TFieldRange<UFunction>(Struct))
		{
			if (Function->GetName().StartsWith(TEXT("ExecuteUbergraph")))
				continue;

			if (HasStructProperty(Context, Function, SearchStruct, nullptr))
				return true;
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Struct: %s does not contain struct of type: %s."), *(Struct->GetName()), *(SearchStruct->GetName())));
		return false;
	}

	#pragma endregion Struct

		// Vector
	#pragma region

	FStructProperty* FLibrary::FindVectorPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FStructProperty* Prop = FindStructPropertyByNameChecked(Context, Struct, PropertyName);

		checkf(Prop->Struct == TBaseStructure<FVector>::Get(), TEXT("%s: %s.%s of type: %s is NOT FVector."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Prop->Struct->GetName()));
		return Prop;
	}

	FStructProperty* FLibrary::FindVectorPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FStructProperty* Prop = FindStructPropertyByName(Context, Struct, PropertyName, Log);

		if (!Prop)
			return nullptr;

		if (Prop->Struct != TBaseStructure<FVector>::Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s of type: %s is NOT FVector."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Prop->Struct->GetName())));
			return nullptr;
		}
		return Prop;
	}

	#pragma endregion Vector

		// Rotator
	#pragma region

	FStructProperty* FLibrary::FindRotatorPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FStructProperty* Prop = FindStructPropertyByNameChecked(Context, Struct, PropertyName);

		checkf(Prop->Struct == TBaseStructure<FRotator>::Get(), TEXT("%s: %s.%s of type: %s is NOT FRotator."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Prop->Struct->GetName()));
		return Prop;
	}

	FStructProperty* FLibrary::FindRotatorPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FStructProperty* Prop = FindStructPropertyByName(Context, Struct, PropertyName, Log);

		if (!Prop)
			return nullptr;

		if (Prop->Struct != TBaseStructure<FRotator>::Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s of type: %s is NOT FRotator."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Prop->Struct->GetName())));
			return nullptr;
		}
		return Prop;
	}

	#pragma endregion Rotator

		// Name
	#pragma region

	FNameProperty* FLibrary::FindNamePropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FProperty* Property   = FindPropertyByNameChecked(Context, Struct, PropertyName);
		FNameProperty* Prop   = CastField<FNameProperty>(Property);

		checkf(Prop, TEXT("%s: %s.%s is NOT a FName."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Prop;
	}

	FNameProperty* FLibrary::FindNamePropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FNameProperty* Prop = CastField<FNameProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a FName."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	#pragma endregion Name

		// String
	#pragma region

	FStrProperty* FLibrary::FindStringPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FProperty* Property  = FindPropertyByNameChecked(Context, Struct, PropertyName);
		FStrProperty* Prop   = CastField<FStrProperty>(Property);

		checkf(Prop, TEXT("%s: %s.%s is NOT a FName."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Prop;
	}

	FStrProperty* FLibrary::FindStringPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FStrProperty* Prop = CastField<FStrProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a FName."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	#pragma endregion String

		// SoftObjectPtr
	#pragma region

	FSoftObjectProperty* FLibrary::FindSoftObjectPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FProperty* Property		  = FindPropertyByNameChecked(Context, Struct, PropertyName);
		FSoftObjectProperty* Prop = CastField<FSoftObjectProperty>(Property);

		checkf(Prop, TEXT("%s: %s.%s is NOT a TSoftObjectPtr."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Prop;
	}

	FSoftObjectProperty* FLibrary::FindSoftObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FSoftObjectProperty* Prop = CastField<FSoftObjectProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TSoftObjectPtr."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	#pragma endregion SoftObjectPtr

		// SoftClassPtr
	#pragma region

	FSoftClassProperty* FLibrary::FindSoftClassPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FProperty* Property		 = FindPropertyByNameChecked(Context, Struct, PropertyName);
		FSoftClassProperty* Prop = CastField<FSoftClassProperty>(Property);

		checkf(Prop, TEXT("%s: %s.%s is NOT a TSoftClassPtr."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Prop;
	}

	FSoftClassProperty* FLibrary::FindSoftClassPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FSoftClassProperty* Prop = CastField<FSoftClassProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TSoftClassPtr."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	#pragma endregion SoftClassPtr

		// Class
	#pragma region

	FClassProperty* FLibrary::FindClassPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FProperty* Property  = FindPropertyByNameChecked(Context, Struct, PropertyName);
		FClassProperty* Prop = CastField<FClassProperty>(Property);

		checkf(Prop, TEXT("%s: %s.%s is NOT a UClass."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Prop;
	}

	FClassProperty* FLibrary::FindClassPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FClassProperty* Prop = CastField<FClassProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a UClass."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}
		return Prop;
	}

	#pragma endregion Class

		// Object
	#pragma region

	FObjectProperty* FLibrary::FindObjectPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FProperty* Property   = FindPropertyByNameChecked(Context, Struct, PropertyName);
		FObjectProperty* Prop = CastField<FObjectProperty>(Property);

		checkf(Prop, TEXT("%s: %s.%s is NOT a UObject."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Prop;
	}

	FObjectProperty* FLibrary::FindObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FObjectProperty* Prop = CastField<FObjectProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a UObject."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}
		return Prop;
	}

	#pragma endregion Object

		// Array
	#pragma region
	
	FArrayProperty* FLibrary::FindArrayPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FArrayProperty* Prop = CastField<FArrayProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TArray."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	FArrayProperty* FLibrary::FindArrayEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel)
	{
		FArrayProperty* Property = FindArrayPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FByteProperty* ByteProperty = CastField<FByteProperty>(Property->Inner);

		if (!ByteProperty)
			return nullptr;

		if (EnumCppType.IsEmpty())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: EnumCppyType is EMPTY."), *Context));
			return nullptr;
		}

		if (!ByteProperty->IsEnum())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT TArray<enum>."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}

		if (!ByteProperty->Enum->CppType.Contains(EnumCppType))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is enum in TArray<enum> NOT of type: %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *EnumCppType));
			return nullptr;
		}
		return Property;
	}

	FArrayProperty* FLibrary::FindArrayNamePropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FArrayProperty* Property = FindArrayPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		if (FNameProperty* NameProperty = CastField<FNameProperty>(Property->Inner))
			return Property;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TArray of FName but a TArray of %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->Inner->GetName())));
		return nullptr;
	}

	FArrayProperty* FLibrary::FindArrayStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FArrayProperty* Property = FindArrayPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		if (FStructProperty* InnerProperty = CastField<FStructProperty>(Property->Inner))
			return Property;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TArray of UStructs but a TArray of %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->Inner->GetName())));
		return nullptr;
	}

	FArrayProperty* FLibrary::FindArrayObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FArrayProperty* Property = FindArrayPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		if (FObjectProperty* InnerProperty = CastField<FObjectProperty>(Property->Inner))
			return Property;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TArray of UObjects but a TArray of %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->Inner->GetName())));
		return nullptr;
	}

	#pragma endregion Array

		// Set
	#pragma region

	FSetProperty* FLibrary::FindSetPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FSetProperty* Prop = CastField<FSetProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TSet."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	FSetProperty* FLibrary::FindSetEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel)
	{
		FSetProperty* Property = FindSetPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FByteProperty* ByteProperty = CastField<FByteProperty>(Property->ElementProp);

		if (!ByteProperty)
			return nullptr;

		if (EnumCppType.IsEmpty())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: EnumCppyType is EMPTY."), *Context));
			return nullptr;
		}

		if (!ByteProperty->IsEnum())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT TSet<enum>."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}

		if (!ByteProperty->Enum->CppType.Contains(EnumCppType))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is enum in TSet<enum> NOT of type: %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *EnumCppType));
			return nullptr;
		}
		return Property;
	}

	FSetProperty* FLibrary::FindSetStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FSetProperty* Property = FindSetPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		if (FStructProperty* ElementProperty = CastField<FStructProperty>(Property->ElementProp))
			return Property;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TSet of UStructs but a TSet of %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->ElementProp->GetName())));
		return nullptr;
	}

	#pragma endregion Set

		// Map
	#pragma region

	
	FMapProperty* FLibrary::FindMapPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FMapProperty* Prop = CastField<FMapProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TMap."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	FMapProperty* FLibrary::FindMapPropertyWithStructValueByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FMapProperty* Property = FindMapPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		if (FStructProperty* ValueProperty = CastField<FStructProperty>(Property->ValueProp))
			return Property;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TMap with Value of type: UStruct but of type: %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->ValueProp->GetName())));
		return nullptr;
	}

	#pragma endregion Map

	#pragma endregion Find

	// Get
	#pragma region

	bool FLibrary::FGetEndPropertyInfoByPath::FParser::Process(const FString& Context, const FString& Path, LogLevel)
	{
		TArray<FString> PropertyNames;
		Path.ParseIntoArray(PropertyNames, TEXT("."), 1);

		if (PropertyNames.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
			return false;
		}

		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FParser::FPropertyInfo InfoType;

		Infos.Reset(2 * PropertyNames.Num());

		for (const FString& PropertyName : PropertyNames)
		{
			// TODO: Set
			
			// Map or Array
			//  Value[Key] or Array[Index]
			if (PropertyName.Contains(TEXT("[")) ||
				PropertyName.Contains(TEXT("]")))
			{
				if (PropertyName.Contains(TEXT("[")) &&
					PropertyName.EndsWith(TEXT("]")))
				{
					// Parse into: {Value, Key]} or {Array, Index]}
					TArray<FString> Parts;
					PropertyName.ParseIntoArray(Parts, TEXT("["));

					if (Parts.Num() != 2)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
						return false;
					}

					// Remove ']' for Key or Index
					const bool Success = Parts[1].RemoveFromEnd(TEXT("]"));

					if (!Success)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
						return false;
					}

					// TODO: Might need to check if Key is a string

					InfoType& Info   = Infos.AddDefaulted_GetRef();
					Info.bMapOrArray = true;
					Info.KeyOrIndex  = Parts[1];
					Info.Name	     = FName(*(Parts[0]));
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
					return false;
				}
			}
			else
			{
				InfoType& Info = Infos.AddDefaulted_GetRef();
				Info.Name	   = FName(*(PropertyName));
			}
		}
		return true;
	}

	#define ResultType NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult
	bool FLibrary::GetEndPropertyInfoByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, ResultType& OutResult, LogLevel)
	{
	#undef ResultType
		CS_IS_PTR_NULL(Struct)
		CS_IS_STRING_EMPTY(Path)

		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FParser ParserType;

		ParserType Parser;

		if (!Parser.Process(Context, Path, Log))
			return false;

		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FParser::FPropertyInfo InfoType;

		const TArray<InfoType>& Infos = Parser.Infos;

		const int32 Count = Infos.Num();
		int32 I = 0;

		OutResult.StructValue  = StructValue;
		OutResult.Struct	   = const_cast<UStruct*>(Struct);
		OutResult.Property	   = nullptr;
		
		while (I < Count)
		{
			const InfoType& Info = Infos[I];

			OutResult.PropertyName = Info.Name;

			if (I < (Count - 1))
			{
				// Map or Array
				if (Info.bMapOrArray)
				{
					bool Found = false;

					// Map
					if (FMapProperty* MapProperty = FindMapPropertyWithStructValueByName(Context, OutResult.Struct, OutResult.PropertyName, nullptr))
					{
						void* ValuePtr = MapProperty->ContainerPtrToValuePtr<void>(OutResult.StructValue, 0);

						FScriptMapHelper MapHelper(MapProperty, ValuePtr);

						for (FScriptMapHelper::FIterator MapIt = MapHelper.CreateIterator(); MapIt; ++MapIt)
						{
							const uint8* KeyPtr    = MapHelper.GetKeyPtr(*MapIt);
							FProperty* KeyProperty = MapHelper.KeyProp;

							FString OutValue;
							KeyProperty->ExportTextItem_Direct(OutValue, KeyPtr, nullptr, nullptr, PPF_None);

							if (Info.KeyOrIndex == OutValue)
							{
								// Only support Value of type: UStruct
								if (FStructProperty* StructProperty = CastField<FStructProperty>(MapHelper.ValueProp))
								{
									OutResult.Property	  = StructProperty;
									OutResult.StructValue = MapHelper.GetValuePtr(*MapIt);
									OutResult.Struct	  = StructProperty->Struct;

									Found = true;
									break;
								}

								CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
								return false;
							}
						}

						if (!Found)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
							return false;
						}
					}
				}
				// Struct
				else
				if (FStructProperty* StructProperty = FindStructPropertyByName(Context, OutResult.Struct, OutResult.PropertyName, Log))
				{
					OutResult.Property = StructProperty;

					if (StructProperty->ArrayDim == 1)
					{
						OutResult.StructValue = StructProperty->ContainerPtrToValuePtr<uint8>(OutResult.StructValue, 0);
						OutResult.Struct	  = StructProperty->Struct;
					}
					else
					{
					}
				}
				else
				{
					// TODO: Need to "build" path for better error output.
					return false;
				}
			}
			else
			{
				return true;
			}
			++I;
		}
		return false;
	}
	
		// Bool
	#pragma region

	bool* FLibrary::GetBoolPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FBoolProperty* BoolProperty = FindPropertyByNameChecked<FBoolProperty>(Context, Struct, PropertyName);

		return ContainerPtrToValuePtrChecked<bool>(Context, BoolProperty, StructValue);
	}

	bool* FLibrary::GetBoolPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FBoolProperty* BoolProperty = FindPropertyByName<FBoolProperty>(Context, Struct, PropertyName, Log);
	
		if (!BoolProperty)
			return nullptr;
		return ContainerPtrToValuePtr<bool>(Context, BoolProperty, StructValue, Log);
	}

	bool FLibrary::GetBoolPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return false;
		return GetBoolPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion Bool

		// Int
	#pragma region

	int32* FLibrary::GetIntPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FIntProperty* IntProperty = FindPropertyByNameChecked<FIntProperty>(Context, Struct, PropertyName);

		return ContainerPtrToValuePtrChecked<int32>(Context, IntProperty, StructValue);
	}

	int32* FLibrary::GetIntPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FIntProperty* IntProperty = FindPropertyByName<FIntProperty>(Context, Struct, PropertyName, Log);

		if (!IntProperty)
			return nullptr;
		return ContainerPtrToValuePtr<int32>(Context, IntProperty, StructValue, Log);
	}

	int32 FLibrary::GetIntPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return 0;
		return GetIntPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion Int

		// Float
	#pragma region

	float* FLibrary::GetFloatPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FFloatProperty* FloatProperty = FindPropertyByNameChecked<FFloatProperty>(Context, Struct, PropertyName);

		return ContainerPtrToValuePtrChecked<float>(Context, FloatProperty, StructValue);
	}

	float* FLibrary::GetFloatPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FFloatProperty* FloatProperty = FindPropertyByName<FFloatProperty>(Context, Struct, PropertyName, Log);

		if (!FloatProperty)
			return nullptr;
		return ContainerPtrToValuePtr<float>(Context, FloatProperty, StructValue, Log);
	}

	float FLibrary::GetFloatPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return 0.0f;
		return GetFloatPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

			// Float or Double
	#pragma region

	float FLibrary::GetFloatOrDoublePropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return 0.0f;

		const float FloatValue = GetFloatPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, nullptr);

		if (OutSuccess)
			return FloatValue;

		const double DoubleValue = GetDoublePropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, nullptr);

		if (OutSuccess)
			return (float)DoubleValue;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Property with name: %s from Struct: %s is NOT of type: float or double."), *Context, *(Result.PropertyName.ToString()), *(Result.Struct->GetName())));
		return 0.0f;
	}

	#pragma endregion Float or Double

	#pragma endregion Float

		// Double
	#pragma region

	double* FLibrary::GetDoublePropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FDoubleProperty* DoubleProperty = FindPropertyByNameChecked<FDoubleProperty>(Context, Struct, PropertyName);

		return ContainerPtrToValuePtrChecked<double>(Context, DoubleProperty, StructValue);
	}

	double* FLibrary::GetDoublePropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FDoubleProperty* DoubleProperty = FindPropertyByName<FDoubleProperty>(Context, Struct, PropertyName, Log);

		if (!DoubleProperty)
			return nullptr;
		return ContainerPtrToValuePtr<double>(Context, DoubleProperty, StructValue, Log);
	}

	double FLibrary::GetDoublePropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return 0.0;
		return GetDoublePropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion Double

		// Struct
	#pragma region

	uint8* FLibrary::GetStructPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		FStructProperty* StructProperty = FindStructPropertyByName(Context, Struct, PropertyName, Log);

		if (!StructProperty)
			return nullptr;

		return StructProperty->ContainerPtrToValuePtr<uint8>(StructValue);
	}
	
	bool FLibrary::GetStructPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, UStruct*& OutStruct, uint8*& OutStructValue, LogLevel)
	{
		OutStruct = nullptr;
		OutStructValue = nullptr;

		FStructProperty* StructProperty = FindStructPropertyByName(Context, Struct, PropertyName, Log);

		if (!StructProperty)
			return false;

		OutStruct	   = StructProperty->Struct;
		OutStructValue = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue);
		return true;
	}

	#pragma endregion Struct

		// Vector
	#pragma region

	FVector* FLibrary::GetVectorPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FStructProperty* VectorProperty = FindVectorPropertyByNameChecked(Context, Struct, PropertyName);

		return ContainerPtrToValuePtrChecked<FVector>(Context, VectorProperty, StructValue);
	}

	FVector* FLibrary::GetVectorPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FStructProperty* VectorProperty = FindVectorPropertyByName(Context, Struct, PropertyName, Log);

		if (!VectorProperty)
			return nullptr;
		return ContainerPtrToValuePtr<FVector>(Context, VectorProperty, StructValue, Log);
	}

	FVector FLibrary::GetVectorPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return FVector::ZeroVector;
		return GetVectorPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion Vector

		// Rotator
	#pragma region

	FRotator* FLibrary::GetRotatorPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FStructProperty* RotatorProperty = FindRotatorPropertyByNameChecked(Context, Struct, PropertyName);

		return ContainerPtrToValuePtrChecked<FRotator>(Context, RotatorProperty, StructValue);
	}

	FRotator* FLibrary::GetRotatorPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FStructProperty* RotatorProperty = FindRotatorPropertyByName(Context, Struct, PropertyName, Log);

		if (!RotatorProperty)
			return nullptr;
		return ContainerPtrToValuePtr<FRotator>(Context, RotatorProperty, StructValue, Log);
	}

	FRotator FLibrary::GetRotatorPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return FRotator::ZeroRotator;
		return GetRotatorPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion Rotator

		// Name
	#pragma region

	FName* FLibrary::GetNamePropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FNameProperty* NameProperty = FindPropertyByNameChecked<FNameProperty>(Context, Struct, PropertyName);

		return ContainerPtrToValuePtrChecked<FName>(Context, NameProperty, StructValue);
	}

	FName* FLibrary::GetNamePropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FNameProperty* NameProperty = FindPropertyByName<FNameProperty>(Context, Struct, PropertyName, Log);

		if (!NameProperty)
			return nullptr;
		return ContainerPtrToValuePtr<FName>(Context, NameProperty, StructValue, Log);
	}

	FName FLibrary::GetNamePropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return NAME_None;
		return GetNamePropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion Name

		// String
	#pragma region

	FString* FLibrary::GetStringPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FStrProperty* StringProperty = FindPropertyByNameChecked<FStrProperty>(Context, Struct, PropertyName);

		return ContainerPtrToValuePtrChecked<FString>(Context, StringProperty, StructValue);
	}

	FString* FLibrary::GetStringPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FStrProperty* StringProperty = FindPropertyByName<FStrProperty>(Context, Struct, PropertyName, Log);

		if (!StringProperty)
			return nullptr;
		return ContainerPtrToValuePtr<FString>(Context, StringProperty, StructValue, Log);
	}

	FString FLibrary::GetStringPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return FString();
		return GetStringPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion String

		// SoftObjectPtr
	#pragma region

	FSoftObjectPtr* FLibrary::GetSoftObjectPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FSoftObjectProperty* Property = FindSoftObjectPropertyByNameChecked(Context, Struct, PropertyName);
		FSoftObjectPtr* ValuePtr	  = Property->GetPropertyValuePtr_InContainer(StructValue);

		checkf(ValuePtr, TEXT("%s: Failed get Value Ptr from %s: %s."), *Context, *(Property->GetClass()->GetName()), *(Property->GetName()))
		return ValuePtr;
	}

	FSoftObjectPtr* FLibrary::GetSoftObjectPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FSoftObjectProperty* Property  = FindSoftObjectPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FSoftObjectPtr* ValuePtr = Property->GetPropertyValuePtr_InContainer(StructValue);

		if (!ValuePtr)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed get Value Ptr from %s: %s."), *Context, *(Property->GetClass()->GetName()), *(Property->GetName())));
			return nullptr;
		}
		return ValuePtr;
	}

	FSoftObjectPtr FLibrary::GetSoftObjectPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return FSoftObjectPtr();
		return GetSoftObjectPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion SoftObjectPtr

		// SoftClassPtr
	#pragma region

	FSoftObjectPtr* FLibrary::GetSoftClassPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FSoftClassProperty* Property = FindSoftClassPropertyByNameChecked(Context, Struct, PropertyName);
		FSoftObjectPtr* ValuePtr	  = Property->GetPropertyValuePtr_InContainer(StructValue);

		checkf(ValuePtr, TEXT("%s: Failed get Value Ptr from %s: %s."), *Context, *(Property->GetClass()->GetName()), *(Property->GetName()))
		return ValuePtr;
	}

	FSoftObjectPtr* FLibrary::GetSoftClassPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FSoftClassProperty* Property  = FindSoftClassPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FSoftObjectPtr* ValuePtr = Property->GetPropertyValuePtr_InContainer(StructValue);

		if (!ValuePtr)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed get Value Ptr from %s: %s."), *Context, *(Property->GetClass()->GetName()), *(Property->GetName())));
			return nullptr;
		}
		return ValuePtr;
	}

	FSoftObjectPtr FLibrary::GetSoftClassPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return FSoftObjectPtr();
		return GetSoftClassPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion SoftClassPtr

		// Class
	#pragma region
	
	TObjectPtr<UObject>* FLibrary::GetClassPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
	{
		FClassProperty* ClassProperty = FindClassPropertyByName(Context, Struct, PropertyName, Log);

		if (!ClassProperty)
			return nullptr;

		if (!StructValue)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: StructValue is NULL."), *Context));
			return nullptr;
		}

		TObjectPtr<UObject>* ValuePtr = ClassProperty->GetPropertyValuePtr_InContainer(StructValue);

		if (!ValuePtr)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Failed to get Value Ptr to member from %s.%s."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}
		return ValuePtr;
	}

	UClass* FLibrary::GetClassPropertyValueByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool& OutSuccess, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

		if (!OutSuccess)
			return nullptr;
		return GetClassPropertyValue(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
	}

	#pragma endregion Class

		// Object
	#pragma region

	UObject* FLibrary::GetObjectPropertyValueChecked(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FObjectProperty* ObjectProperty = FindObjectPropertyByNameChecked(Context, Struct, PropertyName);
		UObject* Value					= ObjectProperty->GetObjectPropertyValue_InContainer(StructValue);

		checkf(Value, TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Value;
	}

	UObject* FLibrary::GetObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FObjectProperty* ObjectProperty = FindPropertyByName<FObjectProperty>(Context, Struct, PropertyName, Log);

		if (!ObjectProperty)
			return nullptr;
		
		UObject* Value = ObjectProperty->GetObjectPropertyValue_InContainer(StructValue);

		if (!Value)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Value;
	}

	#pragma endregion Object

	#pragma endregion Get

	// Set
	#pragma region

		// Bool
	#pragma region
	
	bool FLibrary::SetBoolPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const bool& Value, LogLevel)
	{
		if (FBoolProperty* BoolProperty = FindPropertyByName<FBoolProperty>(Context, Struct, PropertyName, Log))
		{
			BoolProperty->SetPropertyValue_InContainer(StructValue, Value);
			return true;
		}
		return false;
	}

	bool FLibrary::SetBoolPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const bool& Value, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		if (!GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log))
			return false;
		return SetBoolPropertyByName(Context, Result.StructValue, Result.Struct, Result.PropertyName, Value, Log);
	}

	#pragma endregion Bool

		// Int
	#pragma region

	bool FLibrary::SetIntPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const int32& Value, LogLevel)
	{
		if (FIntProperty* IntProperty = FindPropertyByName<FIntProperty>(Context, Struct, PropertyName, Log))
		{
			IntProperty->SetPropertyValue_InContainer(StructValue, Value);
			return true;
		}
		return false;
	}

	bool FLibrary::SetIntPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const int32& Value, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		if (!GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log))
			return false;
		return SetIntPropertyByName(Context, Result.StructValue, Result.Struct, Result.PropertyName, Value, Log);
	}

	#pragma endregion Int

		// Float
	#pragma region

	bool FLibrary::SetFloatPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const float& Value, LogLevel)
	{
		if (FFloatProperty* FloatProperty = FindPropertyByName<FFloatProperty>(Context, Struct, PropertyName, Log))
		{
			FloatProperty->SetPropertyValue_InContainer(StructValue, Value);
			return true;
		}
		return false;
	}

	bool FLibrary::SetFloatPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const float& Value, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		if (!GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log))
			return false;
		return SetFloatPropertyByName(Context, Result.StructValue, Result.Struct, Result.PropertyName, Value, Log);
	}

	#pragma endregion Float

		// Vector
	#pragma region

	bool FLibrary::SetVectorPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const FVector& Value, LogLevel)
	{
		if (FStructProperty* VectorProperty = FindVectorPropertyByName(Context, Struct, PropertyName, Log))
		{
			VectorProperty->SetValue_InContainer(StructValue, &Value);
			return true;
		}
		return false;
	}

	bool FLibrary::SetVectorPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const FVector& Value, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		if (!GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log))
			return false;
		return SetVectorPropertyByName(Context, Result.StructValue, Result.Struct, Result.PropertyName, Value, Log);
	}

	#pragma endregion Vector

		// Rotator
	#pragma region

	bool FLibrary::SetRotatorPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const FRotator& Value, LogLevel)
	{
		if (FStructProperty* RotatorProperty = FindRotatorPropertyByName(Context, Struct, PropertyName, Log))
		{
			RotatorProperty->SetValue_InContainer(StructValue, &Value);
			return true;
		}
		return false;
	}

	bool FLibrary::SetRotatorPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const FRotator& Value, LogLevel)
	{
		typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
		ResultType Result;
		if (!GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log))
			return false;
		return SetRotatorPropertyByName(Context, Result.StructValue, Result.Struct, Result.PropertyName, Value, Log);
	}

	#pragma endregion Rotator

	#pragma endregion Set

	#if WITH_EDITOR

	TArrayView<const TMap<FString, int32>>& FLibrary::GetArrayIndicesPerObject(FPropertyChangedChainEvent& e)
	{
		// A bit of a hack to get access to e.ArrayIndicesPerObject, which is private.
		// Access is needed to determine if a property is part of the chain of events.

		// Get pointer to start of struct
		FProperty** Property = ((FProperty**)(&e));
		char* Base = (char*)Property;

		// Offset by Property
		size_t Offset = sizeof(FProperty*);
		// Offset by MemberProperty
		Offset += sizeof(FProperty*);
		// Offset by ChangeType
		Offset += sizeof(EPropertyChangeType::Type);
		// Offset by ObjectIteratorIndex
		Offset += sizeof(int32);

		return *((TArrayView<const TMap<FString, int32>>*)(Base + Offset));
	}

	bool FLibrary::GetArrayIndex(FPropertyChangedChainEvent& e, const FString& Name, int32& OutIndex)
	{
		TArrayView<const TMap<FString, int32>>& ArrayIndicesPerObject = GetArrayIndicesPerObject(e);

		//default to unknown index
		OutIndex = INDEX_NONE;
		if (ArrayIndicesPerObject.IsValidIndex(e.ObjectIteratorIndex))
		{
			if (const int32* ValuePtr = ArrayIndicesPerObject[e.ObjectIteratorIndex].Find(Name))
			{
				OutIndex = *ValuePtr;

				return true;
			}
		}
		return false;
	}

	void FLibrary::GetPropertyNamesInChain(FPropertyChangedChainEvent& e, TSet<FString>& OutNames)
	{
		TArrayView<const TMap<FString, int32>>& ArrayIndicesPerObject = GetArrayIndicesPerObject(e);

		if (ArrayIndicesPerObject.IsValidIndex(e.ObjectIteratorIndex))
		{
			const TMap<FString, int32>& Map = ArrayIndicesPerObject[e.ObjectIteratorIndex];

			for (const TPair<FString, int32>& Pair : Map)
			{
				OutNames.Add(Pair.Key);
			}
		}
	}

	void FLibrary::GetPropertyNamesWithIndexInChain(FPropertyChangedChainEvent& e, TMap<FString, int32>& OutIndexByNameMap)
	{
		TArrayView<const TMap<FString, int32>>& ArrayIndicesPerObject = GetArrayIndicesPerObject(e);

		if (ArrayIndicesPerObject.IsValidIndex(e.ObjectIteratorIndex))
		{
			const TMap<FString, int32>& Map = ArrayIndicesPerObject[e.ObjectIteratorIndex];

			for (const TPair<FString, int32>& Pair : Map)
			{
				OutIndexByNameMap.Add(Pair.Key, Pair.Value);
			}
		}
	}

	#endif // #if WITH_EDITOR

	#undef LogLevel
}