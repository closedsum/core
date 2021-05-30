// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UStruct;
class FProperty;
class FStructProperty;
class FObjectProperty;

namespace NCsProperty
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString FindPropertyByName;
				extern CSCORE_API const FString FindStructPropertyByName;
				extern CSCORE_API const FString FindObjectPropertyByName;
				extern CSCORE_API const FString GetObjectPropertyValue;
			}
		}
	}

	struct CSCORE_API FLibrary
	{
	// Find
	#pragma region
	public:

		/**
		* Find the Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FProperty* FindPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FProperty* FindPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Find the Property from Struct with name: PropertyName.
		*
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		FORCEINLINE static FProperty* FindPropertyByName(const UStruct* Struct, const FName& PropertyName)
		{
			using namespace NCsProperty::NLibrary::NCached;

			const FString& Context = Str::FindPropertyByName;

			return FindPropertyByName(Context, Struct, PropertyName, nullptr);
		}

		/**
		* Find the Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property of type: T.
		*/
		template<typename T>
		static T* FindPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
		{
			FProperty* Property = FindPropertyByNameChecked(Context, Struct, PropertyName);
			T* Prop				= CastField<T>(Property);

			checkf(Prop, TEXT("%s: %s.%s is NOT of type: T."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
			return Prop;
		}

		/**
		* Find the Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property of type: T.
		*/
		template<typename T>
		static T* FindPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			T* Prop = CastField<T>(Property);

			if (!Prop)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NOT of type: T."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
			}
			return Prop;
		}

		/**
		* Find the Property of type: T from Struct with name: PropertyName.
		*
		* @param Struct
		* @param PropertyName
		* return				Property of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* FindPropertyByName(const UStruct* Struct, const FName& PropertyName)
		{
			using namespace NCsProperty::NLibrary::NCached;

			const FString& Context = Str::FindPropertyByName;

			return FindPropertyByName<T>(Context, Struct, PropertyName, nullptr);
		}

		/**
		* Find the Struct Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FStructProperty* FindStructPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the Struct Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FStructProperty* FindStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Find the Struct Property of type: T from Struct with name: PropertyName.
		*
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		FORCEINLINE static FStructProperty* FindStructPropertyByName(const UStruct* Struct, const FName& PropertyName)
		{
			using namespace NCsProperty::NLibrary::NCached;

			const FString& Context = Str::FindStructPropertyByName;

			return FindStructPropertyByName(Context, Struct, PropertyName, nullptr);
		}

		/**
		* Find the Struct Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		template<typename StructType>
		static FStructProperty* FindStructPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
		{
			FStructProperty* Property = FindStructPropertyByNameChecked(Context, Struct, PropertyName);

			checkf(Property->Struct == StructType::StaticStruct(), TEXT("%s: %s.%s of type: T is NOT of type: T."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->Struct->GetName()), *(StructType::StaticStruct()->GetName()));
			return Property;
		}

		/**
		* Find the Struct Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		template<typename StructType>
		static FStructProperty* FindStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			FStructProperty* Property = FindStructPropertyByName(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			if (Property->Struct != StructType::StaticStruct())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s of type: T is NOT of type: T."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Property->Struct->GetName()), *(StructType::StaticStruct()->GetName())));
			}
			return Property;
		}

		/**
		* Find the Struct Property of type: T from Struct with name: PropertyName.
		*
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		template<typename StructType>
		FORCEINLINE static FStructProperty* FindStructPropertyByName(const UStruct* Struct, const FName& PropertyName)
		{
			using namespace NCsProperty::NLibrary::NCached;

			const FString& Context = Str::FindStructPropertyByName;

			return FindStructPropertyByName<StructType>(Context, Struct, PropertyName, nullptr);
		}

		/**
		* Find the Object Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FObjectProperty* FindObjectPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the Object Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FObjectProperty* FindObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Find the Object Property of type: T from Struct with name: PropertyName.
		*
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		FORCEINLINE static FObjectProperty* FindObjectPropertyByName(const UStruct* Struct, const FName& PropertyName)
		{
			using namespace NCsProperty::NLibrary::NCached;

			const FString& Context = Str::FindObjectPropertyByName;

			return FindObjectPropertyByName(Context, Struct, PropertyName, nullptr);
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

		#pragma endregion Find

	// Get
	#pragma region
	public:

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

		static float* GetFloatPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static float* GetFloatPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning);

		template<typename StructType>
		static StructType* GetStructPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
		{
			FStructProperty* StructProperty = FindStructPropertyByNameChecked<StructType>(Context, Struct, PropertyName);
			StructType* Value				= StructProperty->ContainerPtrToValuePtr<StructType>(StructValue);

			checkf(Value, TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString()));
			return Value;
		}

		template<typename StructType>
		static StructType* GetStructPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			FStructProperty* StructProperty = FindStructPropertyByName<StructType>(Context, Struct, PropertyName, Log);

			if (!StructProperty)
				return nullptr;

			StructType* Value = StructProperty->ContainerPtrToValuePtr<StructType>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *(Struct->GetName()), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				UObject.
		*/
		static UObject* GetObjectPropertyValueChecked(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName);

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				UObject.
		*/
		static UObject* GetObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				UObject.
		*/
		FORCEINLINE static UObject* GetObjectPropertyValue(void* StructValue, UStruct* const& Struct, const FName& PropertyName)
		{
			using namespace NCsProperty::NLibrary::NCached;

			const FString& Context = Str::GetObjectPropertyValue;

			return GetObjectPropertyValue(Context, StructValue, Struct, PropertyName, nullptr);
		}

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				UObject of type: T.
		*/
		template<typename T>
		static T* GetObjectPropertyValueChecked(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName)
		{
			UObject* Object = GetObjectPropertyValueChecked(Context, StructValue, Struct, PropertyName);
			T* O			= Cast<T>(Object);
			
			checkf(O, TEXT("%s: %s.%s = %s with Class: %s is NOT of type: %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Object->GetName()), *(Object->GetClass()->GetName()), *(T::StaticClass()->GetName()));
			return O;
		}

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				UObject of type: T.
		*/
		template<typename T>
		static T* GetObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			UObject* Object = GetObjectPropertyValue(Context, StructValue, Struct, PropertyName, Log);

			if (!Object)
				return nullptr;

			T* O = Cast<T>(Object);

			if (!O)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s = %s with Class: %s is NOT of type: %s."), *Context, *(Struct->GetName()), *(PropertyName.ToString()), *(Object->GetName()), *(Object->GetClass()->GetName()), *(T::StaticClass()->GetName())));
			}
			return O;
		}

		/**
		* Get the UObject value for the Property with name: PropertyName from StructValue.
		* 
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				UObject of type: T
		*/
		template<typename T>
		FORCEINLINE static T* GetObjectPropertyValue(void* StructValue, UStruct* const& Struct, const FName& PropertyName)
		{
			using namespace NCsProperty::NLibrary::NCached;

			const FString& Context = Str::GetObjectPropertyValue;

			return GetObjectPropertyValue<T>(Context, StructValue, Struct, PropertyName, nullptr);
		}

		/**
		* 
		* 
		* @param StructValue
		* @param Struct
		* @out OutValueMap
		*/
		template<typename T>
		static void GetObjectPropertyValues(void* StructValue, UStruct* const& Struct, TMap<FName, T*>& OutValueMap)
		{
			for (TFieldIterator<FProperty> It(Struct); It; ++It)
			{
				FProperty* Property = CastField<FProperty>(*It);

				const FName PropertyName = Property->GetFName();

				if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
				{
					if (ObjectProperty->PropertyClass == T::StaticClass())
					{
						if (T* Value = Cast<T>(ObjectProperty->GetObjectPropertyValue_InContainer(StructValue)))
						{
							OutValueMap.Add(PropertyName, Value);
						}
					}
				}
			}
		}

	#pragma endregion Get

	#if WITH_EDITOR

		/**
		*/
		static TArrayView<const TMap<FString, int32>>& GetArrayIndicesPerObject(FPropertyChangedChainEvent& e);

		/**
		 * Gets the Array Index of the "current object" based on a particular name.
		 * This can be used to check if a property is part of the given "chain" of events.
		 *
		 * @param e			A FPropertyChangedChainEvent.
		 * @param Name		Name of the property to find the array index for
		 * @param OutIndex	The array index of the property name found. 
							Set to INDEX_NONE if property name is NOT found or the property is 
							NOT an array.
		 * return			Whether the property with Name was found.
		 */
		static bool GetArrayIndex(FPropertyChangedChainEvent& e, const FString& Name, int32& OutIndex);

		/**
		*
		*
		* @param e
		* @param OutNames
		*/
		static void GetPropertyNamesInChain(FPropertyChangedChainEvent& e, TSet<FString>& OutNames);

		/**
		*
		*
		* @param e
		* @param OutIndexByNameMap
		*/
		static void GetPropertyNamesWithIndexInChain(FPropertyChangedChainEvent& e, TMap<FString, int32>& OutIndexByNameMap);

	#endif // #if WITH_EDITOR
	};
}