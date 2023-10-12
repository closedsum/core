// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Property.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsProperty
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, FindPropertyByName);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, FindStructPropertyByName);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, FindObjectPropertyByName);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProperty::FLibrary, GetObjectPropertyValue);
			}
		}
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

	FProperty* FLibrary::FindPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	FBoolProperty* FLibrary::FindBoolPropertyByPath(const FString& Context, const UStruct* Struct, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	FByteProperty* FLibrary::FindEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	FStructProperty* FLibrary::FindStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	#pragma endregion Struct

		// Vector
	#pragma region

	FStructProperty* FLibrary::FindVectorPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FStructProperty* Prop = FindStructPropertyByNameChecked(Context, Struct, PropertyName);

		checkf(Prop->Struct == TBaseStructure<FVector>::Get(), TEXT("%s: %s.%s of type: %s is NOT FVector."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Prop->Struct->GetName()));
		return Prop;
	}

	FStructProperty* FLibrary::FindVectorPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

		// Object
	#pragma region

	FObjectProperty* FLibrary::FindObjectPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
	{
		FProperty* Property   = FindPropertyByNameChecked(Context, Struct, PropertyName);
		FObjectProperty* Prop = CastField<FObjectProperty>(Property);

		checkf(Prop, TEXT("%s: %s.%s is NOT a UObject."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Prop;
	}

	FObjectProperty* FLibrary::FindObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		FObjectProperty* Prop = CastField<FObjectProperty>(Property);

		if (!Prop)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a UObject."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
		}
		return Prop;
	}

	#pragma endregion Object

		// Array
	#pragma region
	
	FArrayProperty* FLibrary::FindArrayPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	FArrayProperty* FLibrary::FindArrayEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	FArrayProperty* FLibrary::FindArrayNamePropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		FArrayProperty* Property = FindArrayPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		if (FNameProperty* NameProperty = CastField<FNameProperty>(Property->Inner))
			return Property;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TArray of FName but a TArray of %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->Inner->GetName())));
		return nullptr;
	}

	FArrayProperty* FLibrary::FindArrayStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		FArrayProperty* Property = FindArrayPropertyByName(Context, Struct, PropertyName, Log);

		if (!Property)
			return nullptr;

		if (FStructProperty* InnerProperty = CastField<FStructProperty>(Property->Inner))
			return Property;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NOT a TArray of UStructs but a TArray of %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->Inner->GetName())));
		return nullptr;
	}

	FArrayProperty* FLibrary::FindArrayObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	FSetProperty* FLibrary::FindSetPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	FSetProperty* FLibrary::FindSetEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	FSetProperty* FLibrary::FindSetStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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

	#pragma endregion Find

	// Get
	#pragma region

		// Bool
	#pragma region

	bool* FLibrary::GetBoolPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FBoolProperty* BoolProperty = FindPropertyByNameChecked<FBoolProperty>(Context, Struct, PropertyName);
		bool* Value					= BoolProperty->ContainerPtrToValuePtr<bool>(StructValue);

		checkf(Value, TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Value;
	}

	bool* FLibrary::GetBoolPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FBoolProperty* BoolProperty = FindPropertyByName<FBoolProperty>(Context, Struct, PropertyName, Log);
	
		if (!BoolProperty)
			return nullptr;

		bool* Value = BoolProperty->ContainerPtrToValuePtr<bool>(StructValue);

		if (!Value)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}
		return Value;
	}

	bool FLibrary::GetBoolPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		OutSuccess = false;

		CS_IS_PTR_NULL(Struct)
		CS_IS_STRING_EMPTY(Path)

		TArray<FString> PropertyNames;
		Path.ParseIntoArray(PropertyNames, TEXT("."), 1);

		if (PropertyNames.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
			return false;
		}

		const int32 Count = PropertyNames.Num();
		int32 I = 0;

		void* CurrentStructValue   = StructValue;
		UStruct* CurrentStruct	   = const_cast<UStruct*>(Struct);
		FProperty* CurrentProperty = nullptr;

		while (I < Count)
		{
			// TODO: Check PropertyName for [] and ""
			const FString& PropertyName = PropertyNames[I];

			if (I < (Count - 1))
			{
				// Struct
				if (FStructProperty* StructProperty = FindStructPropertyByName(Context, CurrentStruct, FName(*PropertyName), Log))
				{
					CurrentProperty = StructProperty;

					if (StructProperty->ArrayDim == 1)
					{
						CurrentStructValue = StructProperty->ContainerPtrToValuePtr<uint8>(CurrentStructValue, 0);
						CurrentStruct	   = StructProperty->Struct;
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
				return GetBoolPropertyValue(Context, CurrentStructValue, CurrentStruct, FName(*PropertyName), OutSuccess, Log);
			}
			++I;
		}
		return false;
	}

	#pragma endregion Bool

		// Int
	#pragma region

	int32* FLibrary::GetIntPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FIntProperty* IntProperty = FindPropertyByNameChecked<FIntProperty>(Context, Struct, PropertyName);
		int32* Value			  = IntProperty->ContainerPtrToValuePtr<int32>(StructValue);

		checkf(Value, TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Value;
	}

	int32* FLibrary::GetIntPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FIntProperty* IntProperty = FindPropertyByName<FIntProperty>(Context, Struct, PropertyName, Log);

		if (!IntProperty)
			return nullptr;

		int32* Value = IntProperty->ContainerPtrToValuePtr<int32>(StructValue);

		if (!Value)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}
		return Value;
	}

	int32 FLibrary::GetIntPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		OutSuccess = false;

		CS_IS_PTR_NULL_RET_VALUE(Struct, 0)
		//CS_IS_STRING_EMPTY_RET_VALUE(Path, 0)

		TArray<FString> PropertyNames;
		Path.ParseIntoArray(PropertyNames, TEXT("."), 1);

		if (PropertyNames.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
			return 0;
		}

		const int32 Count = PropertyNames.Num();
		int32 I = 0;

		void* CurrentStructValue   = StructValue;
		UStruct* CurrentStruct	   = const_cast<UStruct*>(Struct);
		FProperty* CurrentProperty = nullptr;

		while (I < Count)
		{
			// TODO: Check PropertyName for [] and ""
			const FString& PropertyName = PropertyNames[I];

			if (I < (Count - 1))
			{
				// Struct
				if (FStructProperty* StructProperty = FindStructPropertyByName(Context, CurrentStruct, FName(*PropertyName), Log))
				{
					CurrentProperty = StructProperty;

					if (StructProperty->ArrayDim == 1)
					{
						CurrentStructValue = StructProperty->ContainerPtrToValuePtr<uint8>(CurrentStructValue, 0);
						CurrentStruct	   = StructProperty->Struct;
					}
					else
					{
					}
				}
				else
				{
					// TODO: Need to "build" path for better error output.
					return 0;
				}
			}
			else
			{
				return GetIntPropertyValue(Context, CurrentStructValue, CurrentStruct, FName(*PropertyName), OutSuccess, Log);
			}
			++I;
		}
		return 0;
	}

	#pragma endregion Int

		// Float
	#pragma region

	float* FLibrary::GetFloatPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
	{
		CS_IS_PTR_NULL_CHECKED(StructValue)

		FFloatProperty* FloatProperty = FindPropertyByNameChecked<FFloatProperty>(Context, Struct, PropertyName);
		float* Value				  = FloatProperty->ContainerPtrToValuePtr<float>(StructValue);

		checkf(Value, TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
		return Value;
	}

	float* FLibrary::GetFloatPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(StructValue)

		FFloatProperty* FloatProperty = FindPropertyByName<FFloatProperty>(Context, Struct, PropertyName, Log);

		if (!FloatProperty)
			return nullptr;

		float* Value = FloatProperty->ContainerPtrToValuePtr<float>(StructValue);

		if (!Value)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			return nullptr;
		}
		return Value;
	}

	float FLibrary::GetFloatPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		OutSuccess = false;

		CS_IS_PTR_NULL_RET_VALUE(Struct, 0.0f)
		//CS_IS_STRING_EMPTY_RET_VALUE(Path, 0)

		TArray<FString> PropertyNames;
		Path.ParseIntoArray(PropertyNames, TEXT("."), 1);

		if (PropertyNames.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
			return 0.0f;
		}

		const int32 Count = PropertyNames.Num();
		int32 I = 0;

		void* CurrentStructValue   = StructValue;
		UStruct* CurrentStruct	   = const_cast<UStruct*>(Struct);
		FProperty* CurrentProperty = nullptr;

		while (I < Count)
		{
			// TODO: Check PropertyName for [] and ""
			const FString& PropertyName = PropertyNames[I];

			if (I < (Count - 1))
			{
				// Struct
				if (FStructProperty* StructProperty = FindStructPropertyByName(Context, CurrentStruct, FName(*PropertyName), Log))
				{
					CurrentProperty = StructProperty;

					if (StructProperty->ArrayDim == 1)
					{
						CurrentStructValue = StructProperty->ContainerPtrToValuePtr<uint8>(CurrentStructValue, 0);
						CurrentStruct	   = StructProperty->Struct;
					}
					else
					{
					}
				}
				else
				{
					// TODO: Need to "build" path for better error output.
					return 0.0f;
				}
			}
			else
			{
				return GetFloatPropertyValue(Context, CurrentStructValue, CurrentStruct, FName(*PropertyName), OutSuccess, Log);
			}
			++I;
		}
		return 0.0f;
	}

	#pragma endregion Float

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

	UObject* FLibrary::GetObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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
	
	bool FLibrary::SetBoolPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, bool Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		FBoolProperty* BoolProperty = FindPropertyByName<FBoolProperty>(Context, Struct, PropertyName, Log);

		if (!BoolProperty)
			return false;

		BoolProperty->SetPropertyValue_InContainer(StructValue, Value);
		return true;
	}

	bool FLibrary::SetBoolPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Struct)
		CS_IS_STRING_EMPTY(Path)

		TArray<FString> PropertyNames;
		Path.ParseIntoArray(PropertyNames, TEXT("."), 1);

		if (PropertyNames.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
			return false;
		}

		const int32 Count = PropertyNames.Num();
		int32 I = 0;

		void* CurrentStructValue   = StructValue;
		UStruct* CurrentStruct	   = const_cast<UStruct*>(Struct);
		FProperty* CurrentProperty = nullptr;

		while (I < Count)
		{
			// TODO: Check PropertyName for [] and ""
			const FString& PropertyName = PropertyNames[I];

			if (I < (Count - 1))
			{
				// Struct
				if (FStructProperty* StructProperty = FindStructPropertyByName(Context, CurrentStruct, FName(*PropertyName), Log))
				{
					CurrentProperty = StructProperty;

					if (StructProperty->ArrayDim == 1)
					{
						CurrentStructValue = StructProperty->ContainerPtrToValuePtr<uint8>(CurrentStructValue, 0);
						CurrentStruct	   = StructProperty->Struct;
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
				return SetBoolPropertyByName(Context, CurrentStructValue, CurrentStruct, FName(*PropertyName), Value, Log);
			}
			++I;
		}
		return false;
	}

	#pragma endregion Bool

		// Int
	#pragma region

	bool FLibrary::SetIntPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const int32& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		FIntProperty* IntProperty = FindPropertyByName<FIntProperty>(Context, Struct, PropertyName, Log);

		if (!IntProperty)
			return false;

		IntProperty->SetPropertyValue_InContainer(StructValue, Value);
		return true;
	}

	bool FLibrary::SetIntPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const int32& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL(Struct)
		CS_IS_STRING_EMPTY(Path)

		TArray<FString> PropertyNames;
		Path.ParseIntoArray(PropertyNames, TEXT("."), 1);

		if (PropertyNames.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s format is incorrect."), *Context, *Path));
			return false;
		}

		const int32 Count = PropertyNames.Num();
		int32 I = 0;

		void* CurrentStructValue   = StructValue;
		UStruct* CurrentStruct	   = const_cast<UStruct*>(Struct);
		FProperty* CurrentProperty = nullptr;

		while (I < Count)
		{
			// TODO: Check PropertyName for [] and ""
			const FString& PropertyName = PropertyNames[I];

			if (I < (Count - 1))
			{
				// Struct
				if (FStructProperty* StructProperty = FindStructPropertyByName(Context, CurrentStruct, FName(*PropertyName), Log))
				{
					CurrentProperty = StructProperty;

					if (StructProperty->ArrayDim == 1)
					{
						CurrentStructValue = StructProperty->ContainerPtrToValuePtr<uint8>(CurrentStructValue, 0);
						CurrentStruct	   = StructProperty->Struct;
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
				return SetIntPropertyByName(Context, CurrentStructValue, CurrentStruct, FName(*PropertyName), Value, Log);
			}
			++I;
		}
		return false;
	}

	#pragma endregion Int

		// Float
	#pragma region

	bool FLibrary::SetFloatPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, float Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		FFloatProperty* FloatProperty = FindPropertyByName<FFloatProperty>(Context, Struct, PropertyName, Log);

		if (!FloatProperty)
			return false;

		FloatProperty->SetPropertyValue_InContainer(StructValue, Value);
		return true;
	}

	#pragma endregion Float

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
}