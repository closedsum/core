// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

class CSCORE_API FCsLibrary_Property
{
public:

	/**
	*
	*
	* @param Struct
	* @param PropertyName
	* return
	*/
	template<typename T>
	static T* FindPropertyByName(const UStruct* Struct, const FName& PropertyName)
	{
		T* Property = CastField<T>(Struct->FindPropertyByName(PropertyName));
		Property	= Property ? Property : Cast<T>(Struct->CustomFindProperty(PropertyName));

		return Property;
	}

	/**
	*
	*
	* @param Struct
	* @param PropertyName
	* return
	*/
	template<typename StructType>
	static FStructProperty* FindStructPropertyByName(const UStruct* Struct, const FName& PropertyName)
	{
		FStructProperty* Property = CastField<FStructProperty>(Struct->FindPropertyByName(PropertyName));
		Property				  = Property ? Property : CastField<FStructProperty>(Struct->CustomFindProperty(PropertyName));

		if (Property &&
			Property->Struct == StructType::StaticStruct())
			return Property;
		return nullptr;
	}

	/**
	*
	*
	* @param Context
	* @param Struct
	* @param PropertyName
	* @param InterfaceName
	* return
	*/
	template<typename T>
	static T* FindPropertyByNameForInterfaceChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& InterfaceName)
	{
		T* Property = CastField<T>(Struct->FindPropertyByName(PropertyName));
		Property	= Property ? Property : CastField<T>(Struct->CustomFindProperty(PropertyName));

		checkf(Property, TEXT("%s: Failed to find Propery: %s when emulating interface: %s."), *Context, *(PropertyName.ToString()), *InterfaceName);

		return Property;
	}

	/**
	*
	*
	* @param Context
	* @param Struct
	* @param PropertyName
	* @param InterfaceName
	* return
	*/
	template<typename StructType>
	static FStructProperty* FindStructPropertyByNameForInterfaceChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& InterfaceName)
	{
		FStructProperty* Property = CastField<FStructProperty>(Struct->FindPropertyByName(PropertyName));
		Property				  = Property ? Property : CastField<FStructProperty>(Struct->CustomFindProperty(PropertyName));

		checkf(Property, TEXT("%s: Failed to find StructPropery: %s when emulating interface: %s."), *Context, *(PropertyName.ToString()), *InterfaceName);

		checkf(Property->Struct == StructType::StaticStruct(), TEXT("%s: StructProperty: %s's Struct type is NOT %s when emulating interface: %s."), *Context, (*PropertyName.ToString()), *(StructType::StaticStruct()->GetName()), *InterfaceName);

		return Property;
	}

	/**
	*
	*
	* @param Context
	* @param Property
	* @param Ptr
	* return
	*/
	template<typename ValueType>
	static ValueType* ContainerPtrToValuePtrChecked(const FString& Context, FProperty* Property, void* Ptr)
	{
		ValueType* ValuePtr = Property->ContainerPtrToValuePtr<ValueType>(Ptr);

		checkf(ValuePtr, TEXT("%s: Failed get Value Ptr from %s: %s."), *Context, *(Property->GetClass()->GetName()), *(Property->GetName()));

		return ValuePtr;
	}
};