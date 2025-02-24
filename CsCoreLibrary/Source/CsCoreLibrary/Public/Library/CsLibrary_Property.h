// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "UObject/SoftObjectPtr.h"
#include "UObject/UnrealType.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UStruct;
class FProperty;
class FByteProperty;
class FBoolProperty;
class FStructProperty;
class FNameProperty;
class FStrProperty;
class FSoftObjectProperty;
class FSoftClassProperty;
class FClassProperty;
class FObjectProperty;
class FArrayProperty;
class FSetProperty;

class UAnimSequence;

namespace NCsProperty
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORELIBRARY_API const FString FindPropertyByName;
				extern CSCORELIBRARY_API const FString FindStructPropertyByName;
				extern CSCORELIBRARY_API const FString FindClassPropertyByName;
				extern CSCORELIBRARY_API const FString FindObjectPropertyByName;
				extern CSCORELIBRARY_API const FString GetObjectPropertyValue;
			}
		}
	}

	struct CSCORELIBRARY_API FLibrary
	{
	#define USING_NS_CACHED using namespace NCsProperty::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsProperty::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	public:

		static FString PrintStructName(const UStruct* Struct);

		static FString PrintPropertyClassName(const FProperty* Property);

		static FString PrintPropertyStructName(const FStructProperty* Property);

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
		* Find the Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property of type: T.
		*/
		template<typename T>
		static T* FindPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName)
		{
			FProperty* Property = FindPropertyByNameChecked(Context, Struct, PropertyName);
			T* Prop				= CastField<T>(Property);

			checkf(Prop, TEXT("%s: %s.%s is NOT of type: T."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()));
			return Prop;
		}

		/**
		* Find the Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FProperty* FindPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

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
		static T* FindPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
		{
			FProperty* Property = FindPropertyByName(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			T* Prop = CastField<T>(Property);

			if (!Prop)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NOT of type: T."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
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

		// Bool
	#pragma region
	public:

		static FBoolProperty* FindBoolPropertyByPath(const FString& Context, const UStruct* Struct, const FString& Path, LogLevel);

	#pragma endregion Bool

		// Enum
	#pragma region
	public:

		/**
		* Find the Struct Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FByteProperty* FindEnumPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType);

		/**
		* Find the Struct Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FByteProperty* FindEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel);

	#pragma endregion Enum

		// Struct
	#pragma region
	public:

		/**
		* Find the Struct Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FStructProperty* FindStructPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the Struct Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FStructProperty* FindStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

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

			checkf(Property->Struct == StructType::StaticStruct(), TEXT("%s: %s.%s of type: T is NOT of type: T."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *PrintPropertyStructName(Property), *(StructType::StaticStruct()->GetName()));
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
		static FStructProperty* FindStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
		{
			FStructProperty* Property = FindStructPropertyByName(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			if (Property->Struct != StructType::StaticStruct())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s of type: T is NOT of type: T."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *PrintPropertyStructName(Property), *(StructType::StaticStruct()->GetName())));
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

		static bool HasStructProperty(const FString& Context, const UStruct* Struct, const UStruct* SearchStruct, LogLevel);

		template<typename StructType>
		FORCEINLINE static bool HasStructProperty(const FString& Context, const UStruct* Struct, LogLevel)
		{
			return HasStructProperty(Context, Struct, StructType::StaticStruct(), Log);
		}

	#pragma endregion Struct

		// Vector
	#pragma region
	public:

		/**
		* Find the Struct Property of type FVector from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FStructProperty* FindVectorPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the Struct Property of type: FVector from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FStructProperty* FindVectorPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);
		FORCEINLINE static FStructProperty* FindVectorPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FStructProperty* Prop = FindVectorPropertyByName(Context, Struct, PropertyName, Log);
			OutSuccess			  = Prop != nullptr;
			return Prop;
		}

	#pragma endregion Vector

		// Rotator
	#pragma region
	public:

		/**
		* Find the Struct Property of type FRotator from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FStructProperty* FindRotatorPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the Struct Property of type: FVector from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FStructProperty* FindRotatorPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);
		FORCEINLINE static FStructProperty* FindRotatorPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FStructProperty* Prop = FindRotatorPropertyByName(Context, Struct, PropertyName, Log);
			OutSuccess			  = Prop != nullptr;
			return Prop;
		}

	#pragma endregion Rotator

		// Name
	#pragma region
	public:

		/**
		* Find the Name Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FNameProperty* FindNamePropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the Name Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FNameProperty* FindNamePropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

	#pragma endregion Name

		// String
	#pragma region
	public:

		/**
		* Find the String Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FStrProperty* FindStringPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the String Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FStrProperty* FindStringPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

	#pragma endregion String

		// SoftObjectPtr
	#pragma region
	public:

		/**
		* Find the SoftObjectPtr Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FSoftObjectProperty* FindSoftObjectPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the SoftObjectPtr Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FSoftObjectProperty* FindSoftObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

	#pragma endregion SoftObjectPtr

		// SoftClassPtr
	#pragma region
	public:

		/**
		* Find the SoftClassPtr Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FSoftClassProperty* FindSoftClassPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the SoftClassPtr Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FSoftClassProperty* FindSoftClassPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

	#pragma endregion SoftClassPtr

		// Class
	#pragma region
	public:

		/**
		* Find the Class Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		static FClassProperty* FindClassPropertyByNameChecked(const FString& Context, const UStruct* Struct, const FName& PropertyName);

		/**
		* Find the Class Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FClassProperty* FindClassPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Find the Class Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				Property.
		*/
		FORCEINLINE static FClassProperty* FindClassPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FClassProperty* Prop = FindClassPropertyByName(Context, Struct, PropertyName, Log);
			OutSuccess			 = Prop != nullptr;
			return Prop;
		}

		/**
		* Find the Class Property of type: T from Struct with name: PropertyName.
		*
		* @param Struct
		* @param PropertyName
		* return				Property.
		*/
		FORCEINLINE static FClassProperty* FindClassPropertyByName(const UStruct* Struct, const FName& PropertyName)
		{
			using namespace NCsProperty::NLibrary::NCached;

			const FString& Context = Str::FindClassPropertyByName;

			return FindClassPropertyByName(Context, Struct, PropertyName, nullptr);
		}

	#pragma endregion Class

		// Object
	#pragma region
	public:

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
		* @param Log			(optional)
		* return				Property.
		*/
		static FObjectProperty* FindObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Find the Object Property of type: T from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				Property.
		*/
		FORCEINLINE static FObjectProperty* FindObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FObjectProperty* Prop = FindObjectPropertyByName(Context, Struct, PropertyName, Log);
			OutSuccess			  = Prop != nullptr;
			return Prop;
		}

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

	#pragma endregion Object

		// Array
	#pragma region
	public:

		/**
		* Find the Array Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FArrayProperty* FindArrayPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);
		FORCEINLINE static FArrayProperty* FindArrayPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FArrayProperty* Prop = FindArrayPropertyByName(Context, Struct, PropertyName, Log);
			OutSuccess			 = Prop != nullptr;
			return Prop;
		}

		/**
		* Find the Array Property (TArray of enums) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FArrayProperty* FindArrayEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel);

		/**
		* Find the Array Property (TArray of FName) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FArrayProperty* FindArrayNamePropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Find the Array Property (TArray of UStructs) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FArrayProperty* FindArrayStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Find the Array Property (TArray of StructType) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		template<typename StructType>
		static FArrayProperty* FindArrayStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
		{
			FArrayProperty* Property = FindArrayStructPropertyByName(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			FStructProperty* InnerProperty = CastField<FStructProperty>(Property->Inner);

			if (InnerProperty->Struct == StructType::StaticStruct())
				return Property;

			if (Log)
				Log(FString::Printf(TEXT("%s: %s.%s is NOT a TArray of %s but a TArray of %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(StructType::StaticStruct()->GetName()), *(Property->Inner->GetName())));
			return nullptr;
		}

		/**
		* Find the Array Property (TArray of UObjects) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FArrayProperty* FindArrayObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Find the Array Property (TArray of ObjectType) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		template<typename ObjectType>
		static FArrayProperty* FindArrayObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
		{
			FArrayProperty* Property = FindArrayObjectPropertyByName(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			FObjectProperty* InnerProperty = CastField<FObjectProperty>(Property->Inner);

			if (InnerProperty->PropertyClass == ObjectType::StaticClass())
				return Property;

			if (Log)
				Log(FString::Printf(TEXT("%s: %s.%s is NOT a TArray of %s but a TArray of %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(ObjectType::StaticClass()->GetName()), *(Property->Inner->GetName())));
			return nullptr;
		}
		template<typename ObjectType>
		FORCEINLINE static FArrayProperty* FindArrayObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FArrayProperty* Prop = FindArrayObjectPropertyByName<ObjectType>(Context, Struct, PropertyName, Log);
			OutSuccess			 = Prop != nullptr;
			return Prop;
		}

		/**
		* Find the Array Property (TArray of SoftObjectPtr<ObjectType>) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				Property.
		*/
		template<typename ObjectType>
		static FArrayProperty* FindArraySoftObjectPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FArrayProperty* Property = FindArrayPropertyByName(Context, Struct, PropertyName, OutSuccess, Log);

			if (!Property)
				return nullptr;

			FSoftObjectProperty* InnerProperty = CastField<FSoftObjectProperty>(Property->Inner);

			if (InnerProperty->PropertyClass == ObjectType::StaticClass())
				return Property;

			if (Log)
				Log(FString::Printf(TEXT("%s: %s.%s is NOT a TArray of %s but a TArray of %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(ObjectType::StaticClass()->GetName()), *(Property->Inner->GetName())));
			return nullptr;
		}

	#pragma endregion Array

		// Set
	#pragma region
	public:

		/**
		* Find the Set Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FSetProperty* FindSetPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Find the Set Property (TSet of enums) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				Property.
		*/
		static FSetProperty* FindSetEnumPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel);

		/**
		* Find the Set Property (Value of type: UStruct) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FSetProperty* FindSetStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Find the Set Property (Value of type: UStruct) from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		template<typename StructType>
		static FSetProperty* FindSetStructPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel)
		{
			FSetProperty* Property = FindSetStructPropertyByName(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			FStructProperty* ElementProperty = CastField<FStructProperty>(Property->ElementProp);

			if (ElementProperty->Struct == StructType::StaticStruct())
				return Property;

			if (Log)
				Log(FString::Printf(TEXT("%s: %s.%s is NOT a TSet of %s but a TSet of %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(StructType::StaticStruct()->GetName()), *(Property->ElementProp->GetName())));
			return nullptr;
		}

	#pragma endregion Set

		// Map
	#pragma region
	public:
	
		/**
		* Find the Map Property from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FMapProperty* FindMapPropertyByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Find the Map Property with Value of type: UStruct from Struct with name: PropertyName.
		*
		* @param Context		The calling context.
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				Property.
		*/
		static FMapProperty* FindMapPropertyWithStructValueByName(const FString& Context, const UStruct* Struct, const FName& PropertyName, LogLevel);

	#pragma endregion Map

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

			checkf(ValuePtr, TEXT("%s: Failed get Value Ptr from %s: %s."), *Context, *PrintPropertyClassName(Property), *(Property->GetName()));
			return ValuePtr;
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
		static ValueType* ContainerPtrToValuePtr(const FString& Context, FProperty* Property, void* Ptr, LogLevel)
		{
			ValueType* ValuePtr = Property->ContainerPtrToValuePtr<ValueType>(Ptr);

			if (!ValuePtr)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed get Value Ptr from %s: %s."), *Context, *PrintPropertyClassName(Property), *(Property->GetName())));
				return nullptr;
			}
			return ValuePtr;
		}

		struct FGetEndPropertyInfoByPath
		{
		public:

			struct FParser
			{
			public:

				struct FPropertyInfo
				{
					bool bMapOrArray;

					FString KeyOrIndex;

					FName Name;

					FPropertyInfo() :
						bMapOrArray(false),
						KeyOrIndex(),
						Name(NAME_None)
					{
					}
				};

				TArray<FPropertyInfo> Infos;

				FParser() :
					Infos()
				{
				}

				bool Process(const FString& Context, const FString& Path, LogLevel);
			};

			struct FResult
			{
			public:

				void* StructValue;
				UStruct* Struct;
				FProperty* Property;
				FName PropertyName;

				FResult() :
					StructValue(nullptr),
					Struct(nullptr),
					Property(nullptr),
					PropertyName(NAME_None)
				{
				}
			};
		};

	#define ResultType NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult
		static bool GetEndPropertyInfoByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, ResultType& OutResult, LogLevel);
	#undef ResultType

		// Bool
	#pragma region
	public:

		static bool* GetBoolPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static bool* GetBoolPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		FORCEINLINE static bool GetBoolPropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (bool* Value = GetBoolPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return false;
		}

		static bool GetBoolPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Bool

		// Int
	#pragma region
	public:

		static int32* GetIntPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static int32* GetIntPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		FORCEINLINE static int32 GetIntPropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (int32* Value = GetIntPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return 0;
		}

		static int32 GetIntPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Int

		// Float
	#pragma region
	public:

		static float* GetFloatPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static float* GetFloatPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		FORCEINLINE static float GetFloatPropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (float* Value = GetFloatPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return 0.0f;
		}

		static float GetFloatPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

			// Float or Double
	#pragma region
	public:

		FORCEINLINE static float GetFloatOrDoublePropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			// Float
			if (float* FloatValue = GetFloatPropertyValuePtr(Context, StructValue, Struct, PropertyName, nullptr))
			{
				OutSuccess = true;
				return *FloatValue;
			}
			// Double
			if (double* DoubleValue = GetDoublePropertyValuePtr(Context, StructValue, Struct, PropertyName, nullptr))
			{
				OutSuccess = true;
				return *DoubleValue;
			}

			if (Log)
				Log(FString::Printf(TEXT("%s: Property with name: %s from Struct: %s is NOT of type: float or double."), *Context, *(PropertyName.ToString()), *PrintStructName(Struct)));
			return 0.0f;
		}

		static float GetFloatOrDoublePropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Float or Double

	#pragma endregion Float

		// Double
	#pragma region
	public:

		static double* GetDoublePropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static double* GetDoublePropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		FORCEINLINE static double GetDoublePropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (double* Value = GetDoublePropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return 0.0;
		}

		static double GetDoublePropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Double

		// Enum
	#pragma region
	public:

		template<typename EnumType>
		static EnumType* GetEnumPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType)
		{
			FByteProperty* ByteProperty = FindEnumPropertyByNameChecked(Context, Struct, PropertyName, EnumCppType);
			EnumType* Value				= ByteProperty->ContainerPtrToValuePtr<EnumType>(StructValue);

			checkf(Value, TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()));
			return Value;
		}

		template<typename EnumType>
		static EnumType* GetEnumPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel)
		{
			FByteProperty* ByteProperty = FindEnumPropertyByName(Context, Struct, PropertyName, EnumCppType, Log);

			if (!ByteProperty)
				return nullptr;

			EnumType* Value = ByteProperty->ContainerPtrToValuePtr<EnumType>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
			}
			return Value;
		}

	#pragma endregion Enuym

		// Struct
	#pragma region
	public:

		template<typename StructType>
		static StructType* GetStructPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
		{
			FStructProperty* StructProperty = FindStructPropertyByNameChecked<StructType>(Context, Struct, PropertyName);
			StructType* Value				= StructProperty->ContainerPtrToValuePtr<StructType>(StructValue);

			checkf(Value, TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()));
			return Value;
		}

		template<typename StructType>
		static StructType* GetStructPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
		{
			FStructProperty* StructProperty = FindStructPropertyByName<StructType>(Context, Struct, PropertyName, Log);

			if (!StructProperty)
				return nullptr;

			StructType* Value = StructProperty->ContainerPtrToValuePtr<StructType>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

		static uint8* GetStructPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		static bool GetStructPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, UStruct*& OutStruct, uint8*& OutStructValue, LogLevel);

	#pragma endregion Struct

		// Vector
	#pragma region
	public:

		static FVector* GetVectorPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static FVector* GetVectorPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		FORCEINLINE static FVector GetVectorPropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (FVector* Value = GetVectorPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return FVector::ZeroVector;
		}

		static FVector GetVectorPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Vector

		// Rotator
	#pragma region
	public:

		static FRotator* GetRotatorPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static FRotator* GetRotatorPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		FORCEINLINE static FRotator GetRotatorPropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (FRotator* Value = GetRotatorPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return FRotator::ZeroRotator;
		}

		static FRotator GetRotatorPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Rotator

		// Name
	#pragma region
	public:

		static FName* GetNamePropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static FName* GetNamePropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		FORCEINLINE static FName GetNamePropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (FName* Value = GetNamePropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return NAME_None;
		}

		static FName GetNamePropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Name

		// String
	#pragma region
	public:

		static FString* GetStringPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static FString* GetStringPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		FORCEINLINE static FString GetStringPropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (FString* Value = GetStringPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return FString();
		}

		static FString GetStringPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion String

		// SoftObjectPtr
	#pragma region
	public:

		static FSoftObjectPtr* GetSoftObjectPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static FSoftObjectPtr* GetSoftObjectPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Get the pointer to the TSoftObjectPtr<T> (as FSoftObjectPtr) for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				pointer to TSoftObjectPtr<T> (as FSoftObjectPtr).
		*/
		template<typename T>
		static FSoftObjectPtr* GetSoftObjectPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
		{
			FSoftObjectProperty* SoftObjectProperty = FindSoftObjectPropertyByName(Context, Struct, PropertyName, Log);

			if (!SoftObjectProperty)
				return nullptr;

			if (!SoftObjectProperty->PropertyClass->IsChildOf(T::StaticClass()))
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NOT of type: %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(T::StaticClass()->GetName())));
				return nullptr;
			}

			if (!StructValue)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: StructValue is NULL."), *Context));
				return nullptr;
			}

			FSoftObjectPtr* ValuePtr = SoftObjectProperty->GetPropertyValuePtr_InContainer(StructValue);

			if (!ValuePtr)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to get Value Ptr from %s.%s."), *Context, *(T::StaticClass()->GetName()), *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return ValuePtr;
		}
		template<typename T>
		FORCEINLINE static FSoftObjectPtr* GetSoftObjectPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FSoftObjectPtr* Ptr = GetSoftObjectPropertyValuePtr<T>(Context, StructValue, Struct, PropertyName, Log);
			OutSuccess			= Ptr != nullptr;
			return Ptr;
		}

		/**
		* Get the pointer to the TSoftObjectPtr<T> (as FSoftObjectPtr) for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				pointer to TSoftObjectPtr<T> (as FSoftObjectPtr).
		*/
		template<typename T>
		FORCEINLINE static FSoftObjectPtr* GetSoftObjectPropertyValuePtrByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool& OutSuccess, LogLevel)
		{
			typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
			ResultType Result;
			OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

			if (!OutSuccess)
				return nullptr;
			return GetSoftObjectPropertyValuePtr<T>(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
		}

		FORCEINLINE static FSoftObjectPtr GetSoftObjectPropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (FSoftObjectPtr* Value = GetSoftObjectPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return FSoftObjectPtr();
		}

		static FSoftObjectPtr GetSoftObjectPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

		/**
		* Get the value of TSoftObjectPtr<T> (as FSoftObjectPtr) for the Path from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param OutSuccess		(Out)
		* @param Log			(optional)
		* return				TSoftObjectPtr<T> (as FSoftObjectPtr).
		*/
		template<typename T>
		FORCEINLINE static FSoftObjectPtr GetSoftObjectPropertyValueByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool& OutSuccess, LogLevel)
		{
			FSoftObjectPtr* Ptr = GetSoftObjectPropertyValuePtrByPath<T>(Context, StructValue, Struct, Path, OutSuccess, Log);

			if (!Ptr)
				return FSoftObjectPtr();
			return *Ptr;
		}

	#pragma endregion SoftObjectPtr

		// SoftClassPtr
	#pragma region
	public:

		static FSoftObjectPtr* GetSoftClassPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName);

		static FSoftObjectPtr* GetSoftClassPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel);

		/**
		* Get the pointer to the TSoftClassPtr<T> (as FSoftObjectPtr) for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				pointer to TSoftClassPtr<T> (as FSoftObjectPtr).
		*/
		template<typename T>
		static FSoftObjectPtr* GetSoftClassPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, LogLevel)
		{
			FSoftClassProperty* SoftClassProperty = FindSoftClassPropertyByName(Context, Struct, PropertyName, Log);

			if (!SoftClassProperty)
				return nullptr;

			if (!SoftClassProperty->MetaClass->IsChildOf(T::StaticClass()))
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NOT of type: %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(T::StaticClass()->GetName())));
				return nullptr;
			}

			if (!StructValue)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: StructValue is NULL."), *Context));
				return nullptr;
			}

			FSoftObjectPtr* ValuePtr = SoftClassProperty->GetPropertyValuePtr_InContainer(StructValue);

			if (!ValuePtr)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to get Value Ptr from %s.%s."), *Context, *(T::StaticClass()->GetName()), *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return ValuePtr;
		}
		template<typename T>
		FORCEINLINE static FSoftObjectPtr* GetSoftClassPropertyValuePtr(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FSoftObjectPtr* Ptr = GetSoftClassPropertyValuePtr<T>(Context, StructValue, Struct, PropertyName, Log);
			OutSuccess			= Ptr != nullptr;
			return Ptr;
		}

		/**
		* Get the pointer to the TSoftClassPtr<T> (as FSoftObjectPtr) for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				pointer to TSoftClassPtr<T> (as FSoftObjectPtr).
		*/
		template<typename T>
		FORCEINLINE static FSoftObjectPtr* GetSoftClassPropertyValuePtrByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool& OutSuccess, LogLevel)
		{
			typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
			ResultType Result;
			OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

			if (!OutSuccess)
				return nullptr;
			return GetSoftClassPropertyValuePtr<T>(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
		}

		FORCEINLINE static FSoftObjectPtr GetSoftClassPropertyValue(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (FSoftObjectPtr* Value = GetSoftClassPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
			{
				OutSuccess = true;
				return *Value;
			}
			return FSoftObjectPtr();
		}

		static FSoftObjectPtr GetSoftClassPropertyValueByPath(const FString& Context, void* StructValue, const UStruct* Struct, const FString& Path, bool& OutSuccess, LogLevel);

		/**
		* Get the value of TSoftClassPtr<T> (as FSoftObjectPtr) for the Path from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param OutSuccess		(Out)
		* @param Log			(optional)
		* return				TSoftClassPtr<T> (as FSoftObjectPtr).
		*/
		template<typename T>
		FORCEINLINE static FSoftObjectPtr GetSoftClassPropertyValueByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool& OutSuccess, LogLevel)
		{
			FSoftObjectPtr* Ptr = GetSoftClassPropertyValuePtrByPath<T>(Context, StructValue, Struct, Path, OutSuccess, Log);

			if (!Ptr)
				return FSoftObjectPtr();
			return *Ptr;
		}

	#pragma endregion SoftClassPtr

		// Class
	#pragma region
	public:

		/**
		* Get the pointer to the UClass for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				pointer to UClass (TObjectPtr<UObject>).
		*/
		static TObjectPtr<UObject>* GetClassPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel);

		/**
		* Get the pointer to the UClass for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				pointer to UClass (TObjectPtr<UObject>).
		*/
		FORCEINLINE static TObjectPtr<UObject>* GetClassPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			TObjectPtr<UObject>* ValuePtr = GetClassPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log);
			OutSuccess					  = ValuePtr != nullptr;
			return ValuePtr;
		}

		/**
		* Get the UClass for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Log
		* return				UClass.
		*/
		FORCEINLINE static UClass* GetClassPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
		{
			if (TObjectPtr<UObject>* ValuePtr = GetClassPropertyValuePtr(Context, StructValue, Struct, PropertyName, Log))
				return Cast<UClass>(ValuePtr->Get());
			return nullptr;
		}
		FORCEINLINE static UClass* GetClassPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			UClass* Value = GetClassPropertyValue(Context, StructValue, Struct, PropertyName, Log);
			OutSuccess    = Value != nullptr;
			return Value;
		}

		/**
		* Get the UClass value for the Path from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param OutSuccess		(Out)
		* @param Log			(optional)
		* return				UClass.
		*/
		static UClass* GetClassPropertyValueByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool& OutSuccess, LogLevel);

	#pragma endregion Class

		// Object
	#pragma region
	public:

		template<typename T>
		static T** GetObjectPropertyValuePtrChecked(const FString& Context, void* StructValue, const UStruct* Struct, const FName& PropertyName)
		{
			FObjectProperty* ObjectProperty = FindObjectPropertyByNameChecked(Context, Struct, PropertyName);

			checkf(ObjectProperty->PropertyClass->IsChildOf(T::StaticClass()), TEXT("%s: %s.%s is NOT of type: %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(T::StaticClass()->GetName()));

			T** Value = ObjectProperty->ContainerPtrToValuePtr<T*>(StructValue);

			checkf(Value, TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()));
			return Value;
		}

		/**
		* Get the pointer to the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				pointer to UObject of type: T.
		*/
		template<typename T>
		static T** GetObjectPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
		{
			FObjectProperty* ObjectProperty = FindObjectPropertyByName(Context, Struct, PropertyName, Log);

			if (!ObjectProperty)
				return nullptr;

			if (!ObjectProperty->PropertyClass->IsChildOf(T::StaticClass()))
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NOT of type: %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(T::StaticClass()->GetName())));
				return nullptr;
			}

			if (!StructValue)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: StructValue is NULL."), *Context));
				return nullptr;
			}

			T** Value = ObjectProperty->ContainerPtrToValuePtr<T*>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to get pointer to member of type: from %s.%s."), *Context, *(T::StaticClass()->GetName()), *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

		/**
		* Get the pointer to the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				pointer to UObject of type: T.
		*/
		template<typename T>
		static T** GetObjectPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			FObjectProperty* ObjectProperty = FindObjectPropertyByName(Context, Struct, PropertyName, OutSuccess, Log);

			if (!ObjectProperty)
				return nullptr;

			if (!ObjectProperty->PropertyClass->IsChildOf(T::StaticClass()))
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NOT of type: %s."), *Context, *PrintStructName(Struct), *(PropertyName.ToString()), *(T::StaticClass()->GetName())));
				OutSuccess = false;
				return nullptr;
			}

			if (!StructValue)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: StructValue is NULL."), *Context));
				OutSuccess = false;
				return nullptr;
			}

			T** Value = ObjectProperty->ContainerPtrToValuePtr<T*>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to get pointer to member of type: from %s.%s."), *Context, *(T::StaticClass()->GetName()), *PrintStructName(Struct), *(PropertyName.ToString())));
				OutSuccess = false;
				return nullptr;
			}
			return Value;
		}

		/**
		* Get the pointer to the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				pointer to UObject of type: T.
		*/
		template<typename T>
		FORCEINLINE static T** GetObjectPropertyValuePtrByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool& OutSuccess, LogLevel)
		{
			typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
			ResultType Result;
			OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

			if (!OutSuccess)
				return nullptr;
			return GetObjectPropertyValuePtr<T>(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutSuccess, Log);
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
		* return				UObject of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* GetObjectPropertyValueChecked(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName)
		{
			T** Ptr = GetObjectPropertyValuePtrChecked<T>(Context, StructValue, Struct, PropertyName);
			return *Ptr;
		}

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue	Pointer an object that is recognized by Unreal's reflection.
		* @param Struct			The Unreal Class or Struct associated with StructValue.
		* @param PropertyName	The Member Name of the Property.
		* @param Log			(optional)
		* @param OutSuccess		(out) Whether this process executed successfully or not.
		* return				UObject.
		*/
		static UObject* GetObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, bool& OutSuccess, LogLevel);
		FORCEINLINE static UObject* GetObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
		{
			bool OutSuccess = false;
			return GetObjectPropertyValue(Context, StructValue, Struct, PropertyName, OutSuccess, Log);
		}

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param StructValue	Pointer an object that is recognized by Unreal's reflection.
		* @param Struct			The Unreal Class or Struct associated with StructValue.
		* @param PropertyName	The Member Name of the Property.
		* @param OutSuccess		(out) Whether this process executed successfully or not.
		* return				UObject.
		*/
		FORCEINLINE static UObject* GetObjectPropertyValue(void* StructValue, UStruct* const& Struct, const FName& PropertyName, bool& OutSuccess)
		{
			SET_CONTEXT(GetObjectPropertyValue);

			return GetObjectPropertyValue(Context, StructValue, Struct, PropertyName, OutSuccess, nullptr);
		}
		FORCEINLINE static UObject* GetObjectPropertyValue(void* StructValue, UStruct* const& Struct, const FName& PropertyName)
		{
			SET_CONTEXT(GetObjectPropertyValue);

			bool OutSuccess = false;
			return GetObjectPropertyValue(Context, StructValue, Struct, PropertyName, OutSuccess, nullptr);
		}

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Log			(optional)
		* return				UObject of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* GetObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
		{
			T** Ptr = GetObjectPropertyValuePtr<T>(Context, StructValue, Struct, PropertyName, Log);

			if (!Ptr)
				return nullptr;
			return *Ptr;
		}

		/**
		* Get the UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				UObject of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* GetObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, bool& OutSuccess, LogLevel)
		{
			T* O	   = GetObjectPropertyValue<T>(Context, StructValue, Struct, PropertyName, Log);
			OutSuccess = O != nullptr;
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
		* Get the UObject value of type: T for the Path from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param OutSuccess		(Out)
		* @param Log			(optional)
		* return				UObject of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* GetObjectPropertyValueByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, bool& OutSuccess, LogLevel)
		{
			T** Ptr = GetObjectPropertyValuePtrByPath<T>(Context, StructValue, Struct, Path, OutSuccess, Log);

			if (!Ptr)
				return nullptr;
			return *Ptr;
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

	#pragma endregion Object

		// Array
	#pragma region
	public:

		/**
		* Get the Array of enums value of type: EnumType for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				TArray<EnumType>*.
		*/
		template<typename EnumType>
		static TArray<EnumType>* GetArrayEnumPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel)
		{
			FArrayProperty* Property = FindArrayEnumPropertyByName(Context, Struct, PropertyName, EnumCppType, Log);

			if (!Property)
				return nullptr;

			TArray<EnumType>* Value = Property->ContainerPtrToValuePtr<TArray<EnumType>>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

		/**
		* Get the Array of FName with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				TArray<FName>*.
		*/
		static TArray<FName>* GetArrayNamePropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
		{
			FArrayProperty* Property = FindArrayNamePropertyByName(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			TArray<FName>* Value = Property->ContainerPtrToValuePtr<TArray<FName>>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

		/**
		* Get the Array of UStruct value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				TArray<T>* (UObject of type: T).
		*/
		template<typename T>
		static TArray<T>* GetArrayStructPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
		{
			FArrayProperty* Property = FindArrayStructPropertyByName<T>(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			TArray<T>* Value = Property->ContainerPtrToValuePtr<TArray<T>>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

		/**
		* Get the Array of UObject value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				TArray<T>* (UObject of type: T).
		*/
		template<typename T>
		static TArray<T*>* GetArrayObjectPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
		{
			FArrayProperty* Property = FindArrayObjectPropertyByName<T>(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			TArray<T*>* Value = Property->ContainerPtrToValuePtr<TArray<T*>>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

		/**
		* Get the Array of UObject values of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName		
		* @param OutArray		(out)
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				bool
		*/
		template<typename T>
		static bool GetArrayObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, TArray<T*>& OutArray, bool& OutSuccess, LogLevel)
		{
			FArrayProperty* Property = FindArrayObjectPropertyByName<T>(Context, Struct, PropertyName, OutSuccess, Log);

			if (!Property)
				return false;

			FScriptArrayHelper_InContainer Helper(Property, StructValue);

			const int32 Count = Helper.Num();

			OutArray.Reset(Count);

			for (int32 I = 0; I < Count; ++I)
			{
				T** Ptr						   = reinterpret_cast<T**>(Helper.GetRawPtr(I));
				OutArray.AddDefaulted_GetRef() = *Ptr;
			}
			return true;
		}

		/**
		* Get the Array of UObject values of type: T for the Path from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param OutArray		(out)
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				bool
		*/
		template<typename T>
		static bool GetArrayObjectPropertyValueByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, TArray<T*>& OutArray, bool& OutSuccess, LogLevel)
		{
			typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
			ResultType Result;
			OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

			if (!OutSuccess)
				return false;
			return GetArrayObjectPropertyValue<T>(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutArray, OutSuccess, Log);
		}

		/**
		* Get the Array of SoftObjectPtr values of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName		
		* @param OutArray		(out)
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				bool
		*/
		template<typename T>
		static bool GetArraySoftObjectPropertyValue(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, TArray<TSoftObjectPtr<T>>& OutArray, bool& OutSuccess, LogLevel)
		{
			FArrayProperty* Property = FindArraySoftObjectPropertyByName<T>(Context, Struct, PropertyName, OutSuccess, Log);

			if (!Property)
				return false;

			FScriptArrayHelper_InContainer Helper(Property, StructValue);

			const int32 Count = Helper.Num();

			OutArray.Reset(Count);

			for (int32 I = 0; I < Count; ++I)
			{
				TSoftObjectPtr<T>* Ptr		   = reinterpret_cast<TSoftObjectPtr<T>*>(Helper.GetRawPtr(I));
				OutArray.AddDefaulted_GetRef() = *Ptr;
			}
			return true;
		}

		/**
		* Get the Array of SoftObjectPtr values of type: T for the Path from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param OutArray		(out)
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				bool
		*/
		template<typename T>
		static bool GetArraySoftObjectPropertyValueByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, TArray<TSoftObjectPtr<T>>& OutArray, bool& OutSuccess, LogLevel)
		{
			typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
			ResultType Result;
			OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

			if (!OutSuccess)
				return false;
			return GetArraySoftObjectPropertyValue<T>(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutArray, OutSuccess, Log);
		}

		/**
		* Get the Array of SoftObjectPtr values of type: T for the Property with name: PropertyName from StructValue as an Array of Strings.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName		
		* @param OutArray		(out)
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				bool
		*/
		template<typename T>
		static bool GetArraySoftObjectPropertyValueAsString(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, TArray<FString>& OutArray, bool& OutSuccess, LogLevel)
		{
			FArrayProperty* Property = FindArraySoftObjectPropertyByName<T>(Context, Struct, PropertyName, OutSuccess, Log);

			if (!Property)
				return false;

			FScriptArrayHelper_InContainer Helper(Property, StructValue);

			const int32 Count = Helper.Num();

			OutArray.Reset(Count);

			for (int32 I = 0; I < Count; ++I)
			{
				TSoftObjectPtr<T>* Ptr		   = reinterpret_cast<TSoftObjectPtr<T>*>(Helper.GetRawPtr(I));
				OutArray.AddDefaulted_GetRef() = Ptr->ToSoftObjectPath().ToString();
			}
			return true;
		}

		/**
		* Get the Array of SoftObjectPtr values of type: T for the Path from StructValue as an Array of Strings.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param OutArray		(out)
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				bool
		*/
		template<typename T>
		static bool GetArraySoftObjectPropertyValueAsStringByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, TArray<FString>& OutArray, bool& OutSuccess, LogLevel)
		{
			typedef NCsProperty::FLibrary::FGetEndPropertyInfoByPath::FResult ResultType;
		
			ResultType Result;
			OutSuccess = GetEndPropertyInfoByPath(Context, StructValue, Struct, Path, Result, Log);

			if (!OutSuccess)
				return false;
			return GetArraySoftObjectPropertyValueAsString<T>(Context, Result.StructValue, Result.Struct, Result.PropertyName, OutArray, OutSuccess, Log);
		}

	#pragma endregion Array

		// Set
	#pragma region
	public:

		/**
		* Get the Set of enums value of type: EnumType for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				TSet<EnumType>*.
		*/
		template<typename EnumType>
		static TSet<EnumType>* GetSetEnumPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const FString& EnumCppType, LogLevel)
		{
			FSetProperty* Property = FindSetEnumPropertyByName(Context, Struct, PropertyName, EnumCppType, Log);

			if (!Property)
				return nullptr;

			TSet<EnumType>* Value = Property->ContainerPtrToValuePtr<TSet<EnumType>>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

		/**
		* Get the Set of UStruct value of type: T for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* return				TSet<T>* (struct of type: T).
		*/
		template<typename T>
		static TSet<T>* GetSetStructPropertyValuePtr(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, LogLevel)
		{
			FSetProperty* Property = FindSetStructPropertyByName<T>(Context, Struct, PropertyName, Log);

			if (!Property)
				return nullptr;

			TSet<T>* Value = Property->ContainerPtrToValuePtr<TSet<T>>(StructValue);

			if (!Value)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s.%s is NULL."), *Context, *PrintStructName(Struct), *(PropertyName.ToString())));
				return nullptr;
			}
			return Value;
		}

#pragma endregion Set

	#pragma endregion Get

	// Set
	#pragma region
	public:

		// Bool
	#pragma region
	public:

		/**
		* Set the bool value for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Value
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		static bool SetBoolPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const bool& Value, LogLevel);

		/**
		* Set the bool value by Path for StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param Value
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		static bool SetBoolPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const bool& Value, LogLevel);
		FORCEINLINE static bool SetBoolPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const bool& Value, bool& OutSuccess, LogLevel)
		{
			OutSuccess = SetBoolPropertyByPath(Context, StructValue, Struct, Path, Value, Log);
			return OutSuccess;
		}

	#pragma endregion Bool

		// Int
	#pragma region
	public:

		/**
		* Set the int32 value for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Value
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		static bool SetIntPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const int32& Value, LogLevel);

		/**
		* Set the int32 value by Path for StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param Value
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		static bool SetIntPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const int32& Value, LogLevel);
		FORCEINLINE static bool SetIntPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const int32& Value, bool& OutSuccess, LogLevel)
		{
			OutSuccess = SetIntPropertyByPath(Context, StructValue, Struct, Path, Value, Log);
			return OutSuccess;
		}

	#pragma endregion Int

		// Float
	#pragma region
	public:

		/**
		* Set the float value for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Value
		* return				Whether Value was successfully set or not.
		*/
		static bool SetFloatPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const float& Value, LogLevel);

		/**
		* Set the float value by Path for StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param Value
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		static bool SetFloatPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const float& Value, LogLevel);
		FORCEINLINE static bool SetFloatPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const float& Value, bool& OutSuccess, LogLevel)
		{
			OutSuccess = SetFloatPropertyByPath(Context, StructValue, Struct, Path, Value, Log);
			return OutSuccess;
		}

	#pragma endregion Float

		// Vector
	#pragma region
	public:

		/**
		* Set the FVector value for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Value
		* return				Whether Value was successfully set or not.
		*/
		static bool SetVectorPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const FVector& Value, LogLevel);

		/**
		* Set the FVector value by Path for StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param Value
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		static bool SetVectorPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const FVector& Value, LogLevel);
		FORCEINLINE static bool SetVectorPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const FVector& Value, bool& OutSuccess, LogLevel)
		{
			OutSuccess = SetVectorPropertyByPath(Context, StructValue, Struct, Path, Value, Log);
			return OutSuccess;
		}

	#pragma endregion Vector

		// Rotator
	#pragma region
	public:

		/**
		* Set the FRotator value for the Property with name: PropertyName from StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Value
		* return				Whether Value was successfully set or not.
		*/
		static bool SetRotatorPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, const FRotator& Value, LogLevel);

		/**
		* Set the FRotator value by Path for StructValue.
		*
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param Path
		* @param Value
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		static bool SetRotatorPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const FRotator& Value, LogLevel);
		FORCEINLINE static bool SetRotatorPropertyByPath(const FString& Context, void* StructValue, UStruct* const& Struct, const FString& Path, const FRotator& Value, bool& OutSuccess, LogLevel)
		{
			OutSuccess = SetRotatorPropertyByPath(Context, StructValue, Struct, Path, Value, Log);
			return OutSuccess;
		}

	#pragma endregion Rotator

		// Object
	#pragma region
	public:

		/**
		* Set the UObject value of type: T for the Property with name: PropertyName from StructValue.
		* 
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Value
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		template<typename T>
		static bool SetObjectPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, T* Value, LogLevel)
		{
			T** Ptr = GetObjectPropertyValuePtr<T>(Context, StructValue, Struct, PropertyName, Log);

			if (!Ptr)
				return false;

			*Ptr = Value;
			return true;
		}

		/**
		* Set the UObject value of type: T for the Property with name: PropertyName from StructValue.
		* 
		* @param Context		The calling context.
		* @param StructValue
		* @param Struct
		* @param PropertyName
		* @param Value
		* @param OutSuccess		(out)
		* @param Log			(optional)
		* return				Whether Value was successfully set or not.
		*/
		template<typename T>
		static bool SetObjectPropertyByName(const FString& Context, void* StructValue, UStruct* const& Struct, const FName& PropertyName, T* Value, bool& OutSuccess, LogLevel)
		{
			T** Ptr = GetObjectPropertyValuePtr<T>(Context, StructValue, Struct, PropertyName, OutSuccess, Log);

			if (!Ptr)
				return false;

			*Ptr = Value;
			return true;
		}

	#pragma endregion Object

	#pragma endregion Set

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

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef LogLevel
	};
}

using CsPropertyLibrary = NCsProperty::FLibrary;