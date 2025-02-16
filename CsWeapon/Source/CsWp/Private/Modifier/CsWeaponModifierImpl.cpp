// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsWeaponModifierImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Modifier/CsLibrary_WeaponModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsWeaponModifierImpl)

// FCsWeaponModifier_Int
#pragma region

namespace NCsWeaponModifier_Int
{
	using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

	void FImpl::CopyToModifier(ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY(Modifier, Type);
		CS_THIS_COPY_TO_PROXY(Modifier, Value);
		CS_THIS_COPY_TYPE_TO_PROXY(Modifier, Application, ApplicationType);
	}

	void FImpl::CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Type);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Value);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Modifier, Application, ApplicationType);
	}
}

bool FCsWeaponModifier_Int::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, Application)
	return true;
}

bool FCsWeaponModifier_Int::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsWeaponModifier, FECsWeaponModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, Application)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsWeapon::NModifier::NInt::FInt);

	// NCsWeapon::NModifier::NInt::NInt
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NInt, Int)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsWeapon::NModifier::NInt::FInt, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NInt
		{
			FInt::FInt() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NNumeric::EApplication::Multiply)
			{
				InterfaceMap = new FCsInterfaceMap();
			
				CS_INTERFACE_MAP_SET_ROOT(FInt);

				CS_INTERFACE_MAP_ADD(CsModifierType);
				CS_INTERFACE_MAP_ADD(CsIntModifierType);
				CS_INTERFACE_MAP_ADD(CsWeaponModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetWeaponModifierType);
				CS_INTERFACE_MAP_ADD(ICsIsValid);
				CS_INTERFACE_MAP_ADD(CopyType);
				CS_INTERFACE_MAP_ADD(ICsReset);

				CS_CTOR_SET_MEMBER_PROXY(Type);
				CS_CTOR_SET_MEMBER_PROXY(Value);
				CS_CTOR_SET_MEMBER_PROXY(Application);
			}

			FInt::~FInt()
			{
				// ICsGetInterfaceMap
				delete InterfaceMap;
			}

			using ApplicationMapType = NCsModifier::NValue::NNumeric::EMApplication;

			// ICsIsValid
			#pragma region

			bool FInt::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
				return true;
			}

			bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsWeaponModifier, FECsWeaponModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
			#pragma region

			void FInt::Copy(const CsWeaponModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FInt* FromImpl = CsWeaponModifierLibrary::PureStaticCastChecked<FInt>(Context, From);

				SetType(FromImpl->GetType());
				SetValue(FromImpl->GetValue());
				SetApplication(FromImpl->GetApplication());
			}

			#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsWeaponModifier_Int

// FCsWeaponModifier_Float
#pragma region

namespace NCsWeaponModifier_Float
{
	using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

	void FImpl::CopyToModifier(ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY(Modifier, Type);
		CS_THIS_COPY_TO_PROXY(Modifier, Value);
		CS_THIS_COPY_TYPE_TO_PROXY(Modifier, Application, ApplicationType);
	}

	void FImpl::CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Type);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Value);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Modifier, Application, ApplicationType);
	}
}

bool FCsWeaponModifier_Float::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, Application)
	return true;
}

bool FCsWeaponModifier_Float::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsWeaponModifier, FECsWeaponModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, Application)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsWeapon::NModifier::NFloat::FFloat);

	// NCsWeapon::NModifier::NFloat::NFloat
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NFloat, Float)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsWeapon::NModifier::NFloat::FFloat, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NFloat
		{
			FFloat::FFloat() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NNumeric::EApplication::Multiply)
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FFloat);

				CS_INTERFACE_MAP_ADD(CsModifierType);
				CS_INTERFACE_MAP_ADD(CsFloatModifierType);
				CS_INTERFACE_MAP_ADD(CsWeaponModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetWeaponModifierType);
				CS_INTERFACE_MAP_ADD(ICsIsValid);
				CS_INTERFACE_MAP_ADD(CopyType);
				CS_INTERFACE_MAP_ADD(ICsReset);

				CS_CTOR_SET_MEMBER_PROXY(Type);
				CS_CTOR_SET_MEMBER_PROXY(Value);
				CS_CTOR_SET_MEMBER_PROXY(Application);
			}

			FFloat::~FFloat()
			{
				// ICsGetInterfaceMap
				delete InterfaceMap;
			}

			using ApplicationMapType = NCsModifier::NValue::NNumeric::EMApplication;

			// ICsIsValid
			#pragma region

			bool FFloat::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
				return true;
			}

			bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsWeaponModifier, FECsWeaponModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
			#pragma region

			void FFloat::Copy(const CsWeaponModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FFloat* FromImpl = CsWeaponModifierLibrary::PureStaticCastChecked<FFloat>(Context, From);

				SetType(FromImpl->GetType());
				SetValue(FromImpl->GetValue());
				SetApplication(FromImpl->GetApplication());
			}

			#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsWeaponModifier_Float

// FCsWeaponModifier_Toggle
#pragma region

namespace NCsWeaponModifier_Toggle
{
	void FImpl::CopyToModifier(ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY(Modifier, Type);
		CS_THIS_COPY_TO_PROXY(Modifier, bEnable);
	}

	void FImpl::CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Type);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, bEnable);
	}
}

bool FCsWeaponModifier_Toggle::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)
	return true;
}

bool FCsWeaponModifier_Toggle::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsWeaponModifier, FECsWeaponModifier, Type)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsWeapon::NModifier::NToggle::FToggle);

	// NCsWeapon::NModifier::NToggle::NToggle
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NToggle, Toggle)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsWeapon::NModifier::NToggle::FToggle, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NToggle
		{
			FToggle::FToggle() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bEnable, false)
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FToggle);

				CS_INTERFACE_MAP_ADD(CsModifierType);
				CS_INTERFACE_MAP_ADD(CsToggleModifierType);
				CS_INTERFACE_MAP_ADD(CsWeaponModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetWeaponModifierType);
				CS_INTERFACE_MAP_ADD(ICsIsValid);
				CS_INTERFACE_MAP_ADD(CopyType);
				CS_INTERFACE_MAP_ADD(ICsReset);

				CS_CTOR_SET_MEMBER_PROXY(Type);
				CS_CTOR_SET_MEMBER_PROXY(bEnable);
			}

			FToggle::~FToggle()
			{
				// ICsGetInterfaceMap
				delete InterfaceMap;
			}

			// ICsIsValid
			#pragma region

			bool FToggle::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, GetType())
				return true;
			}

			bool FToggle::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsWeaponModifier, FECsWeaponModifier, GetType())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
			#pragma region

			void FToggle::Copy(const CsWeaponModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FToggle* FromImpl = CsWeaponModifierLibrary::PureStaticCastChecked<FToggle>(Context, From);

				SetType(FromImpl->GetType());
				SetbEnable(FromImpl->GetbEnable());
			}

			#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsWeaponModifier_Toggle

// FCsWeaponModifierInfo
#pragma region

namespace NCsWeaponModifierInfo
{
	using IntModifierType = NCsWeapon::NModifier::NInt::FInt;
	using FloatModifierType = NCsWeapon::NModifier::NFloat::FFloat;
	using ToggleModifierType = NCsWeapon::NModifier::NToggle::FToggle;

	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		Info->Ints.Reset(This->Ints.Num());

		for (FCsWeaponModifier_Int& From : This->Ints)
		{
			IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		// Floats
		Info->Floats.Reset(This->Floats.Num());

		for (FCsWeaponModifier_Float& From : This->Floats)
		{
			FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		// Toggles
		Info->Toggles.Reset(This->Toggles.Num());

		for (FCsWeaponModifier_Toggle& From : This->Toggles)
		{
			ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		Info->PopulateModifiers();
	}

	void FImpl::CopyToInfoAsValue(const ThisType* This, InfoType* Info)
	{
		Info->Ints.Reset(This->Ints.Num());

		for (const FCsWeaponModifier_Int& From : This->Ints)
		{
			IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		// Floats
		Info->Floats.Reset(This->Floats.Num());

		for (const FCsWeaponModifier_Float& From : This->Floats)
		{
			FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		// Toggles
		Info->Toggles.Reset(This->Toggles.Num());

		for (const FCsWeaponModifier_Toggle& From : This->Toggles)
		{
			ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		Info->PopulateModifiers();
	}
}

bool FCsWeaponModifierInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	for (const FCsWeaponModifier_Int& Modifier : Ints)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsWeaponModifier_Float& Modifier : Floats)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsWeaponModifier_Toggle& Modifier : Toggles)
	{
		CS_IS_VALID(Modifier)
	}
	return true;
}

namespace NCsWeapon
{
	namespace NModifier
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			const int32 Total = Ints.Num() + Floats.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE_CHECKED(Modifiers, ModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
		{
			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID(Modifier)
			}

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID(Modifier)
			}

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID(Modifier)
			}

			const int32 Total = Ints.Num() + Floats.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE(Modifiers, ModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL(Modifiers, ModifierType)
			return true;
		}
	}
}

#pragma endregion FCsWeaponModifierInfo