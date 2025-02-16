// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsProjectileModifierImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsProjectileModifierImpl)

// FCsProjectileModifier_Int
#pragma region

namespace NCsProjectileModifier_Int
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

bool FCsProjectileModifier_Int::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, Application)
	return true;
}

bool FCsProjectileModifier_Int::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsProjectileModifier, FECsProjectileModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, Application)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NModifier::NInt::FInt);

	// NCsProjectile::NModifier::NInt::NInt
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NInt, Int)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsProjectile::NModifier::NInt::FInt, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsProjectile
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
				CS_INTERFACE_MAP_ADD(PrjModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetProjectileModifierType);
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
			using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

			// ICsIsValid
			#pragma region

			bool FInt::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks
				CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
				return true;
			}

			bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsProjectileModifier, FECsProjectileModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks
				CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
			#pragma region

			void FInt::Copy(const PrjModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FInt* FromImpl = CsProjectileModifierLibrary::PureStaticCastChecked<FInt>(Context, From);

				SetType(FromImpl->GetType());
				SetValue(FromImpl->GetValue());
				SetApplication(FromImpl->GetApplication());
			}

			#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsProjectileModifier_Int

// FCsProjectileModifier_Float
#pragma region

namespace NCsProjectileModifier_Float
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

bool FCsProjectileModifier_Float::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, Application)
	return true;
}

bool FCsProjectileModifier_Float::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsProjectileModifier, FECsProjectileModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, Application)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NModifier::NFloat::FFloat);

	// NCsProjectile::NModifier::NFloat::NFloat
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NFloat, Float)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsProjectile::NModifier::NFloat::FFloat, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsProjectile
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
				CS_INTERFACE_MAP_ADD(PrjModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetProjectileModifierType);
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
			using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

			// ICsIsValid
			#pragma region

			bool FFloat::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks
				CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
				return true;
			}

			bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsProjectileModifier, FECsProjectileModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks
				CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
			#pragma region

			void FFloat::Copy(const PrjModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FFloat* FromImpl = CsProjectileModifierLibrary::PureStaticCastChecked<FFloat>(Context, From);

				SetType(FromImpl->GetType());
				SetValue(FromImpl->GetValue());
				SetApplication(FromImpl->GetApplication());
			}

			#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsProjectileModifier_Float

// FCsProjectileModifier_Toggle
#pragma region

namespace NCsProjectileModifier_Toggle
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

bool FCsProjectileModifier_Toggle::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, Type)
	return true;
}

bool FCsProjectileModifier_Toggle::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsProjectileModifier, FECsProjectileModifier, Type)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NModifier::NToggle::FToggle);

	// NCsProjectile::NModifier::NToggle::NToggle
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NToggle, Toggle)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsProjectile::NModifier::NToggle::FToggle, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsProjectile
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
				CS_INTERFACE_MAP_ADD(PrjModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetProjectileModifierType);
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
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, GetType())
				return true;
			}

			bool FToggle::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsProjectileModifier, FECsProjectileModifier, GetType())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
			#pragma region

			void FToggle::Copy(const PrjModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FToggle* FromImpl = CsProjectileModifierLibrary::PureStaticCastChecked<FToggle>(Context, From);

				SetType(FromImpl->GetType());
				SetbEnable(FromImpl->GetbEnable());
			}

			#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsProjectileModifier_Toggle

// FCsProjectileModifierInfo
#pragma region

namespace NCsProjectileModifierInfo
{
	using IntModifierType = NCsProjectile::NModifier::NInt::FInt;
	using FloatModifierType = NCsProjectile::NModifier::NFloat::FFloat;
	using ToggleModifierType = NCsProjectile::NModifier::NToggle::FToggle;

	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		// Ints
		Info->Ints.Reset(This->Ints.Num());

		for (FCsProjectileModifier_Int& From : This->Ints)
		{
			IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		// Floats
		Info->Floats.Reset(This->Floats.Num());

		for (FCsProjectileModifier_Float& From : This->Floats)
		{
			FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		// Toggles
		Info->Toggles.Reset(This->Toggles.Num());

		for (FCsProjectileModifier_Toggle& From : This->Toggles)
		{
			ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		Info->PopulateModifiers();
	}

	void FImpl::CopyToInfoAsValue(const ThisType* This, InfoType* Info)
	{
		// Ints
		Info->Ints.Reset(This->Ints.Num());

		for (const FCsProjectileModifier_Int& From : This->Ints)
		{
			IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		// Floats
		Info->Floats.Reset(This->Floats.Num());

		for (const FCsProjectileModifier_Float& From : This->Floats)
		{
			FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		// Toggles
		Info->Toggles.Reset(This->Toggles.Num());

		for (const FCsProjectileModifier_Toggle& From : This->Toggles)
		{
			ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		Info->PopulateModifiers();
	}
}

bool FCsProjectileModifierInfo::IsValidChecked(const FString& Context) const
{
	for (const FCsProjectileModifier_Int& Modifier : Ints)
	{
		CS_IS_VALID_CHECKED(Modifier);
	}
	for (const FCsProjectileModifier_Float& Modifier : Floats)
	{
		CS_IS_VALID_CHECKED(Modifier);
	}
	for (const FCsProjectileModifier_Toggle& Modifier : Toggles)
	{
		CS_IS_VALID_CHECKED(Modifier);
	}
	return true;
}

bool FCsProjectileModifierInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	for (const FCsProjectileModifier_Int& Modifier : Ints)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsProjectileModifier_Float& Modifier : Floats)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsProjectileModifier_Toggle& Modifier : Toggles)
	{
		CS_IS_VALID(Modifier)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NModifier
	{
		using IntModifierType = NCsProjectile::NModifier::NInt::FInt;
		using FloatModifierType = NCsProjectile::NModifier::NFloat::FFloat;
		using ToggleModifierType = NCsProjectile::NModifier::NToggle::FToggle;
		using ModifierType = NCsProjectile::NModifier::IModifier;

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

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
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

#pragma endregion FCsProjectileModifierInfo

// FCsProjectileModifier_Create_Int
#pragma region

namespace NCsProjectileModifier_Create_Int
{
	using CreateType = NCsModifier::NValue::NNumeric::ECreate;

	void FImpl::CopyToCreateModifier(ThisType* This, CreateModifierType* CreateModifier)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(CreateModifier, Type, CreateType);
		CS_THIS_COPY_TO_PROXY(CreateModifier, Value);
		This->Modifier.CopyToModifier(CreateModifier->GetModifierPtr());
	}

	void FImpl::CopyToCreateModifierAsValue(const ThisType* This, CreateModifierType* CreateModifier)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(CreateModifier, Type, CreateType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(CreateModifier, Value);
		This->Modifier.CopyToModifierAsValue(CreateModifier->GetModifierPtr());
	}
}

bool FCsProjectileModifier_Create_Int::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueCreateModifier, Type)
	CS_IS_VALID_CHECKED(Modifier);
	return true;
}

bool FCsProjectileModifier_Create_Int::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsNumericValueCreateModifier, ECsNumericValueCreateModifier, Type)
	CS_IS_VALID(Modifier)
	return true;
}

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;
			using CreateMapType = NCsModifier::NValue::NNumeric::EMCreate;
			using CreateType = NCsModifier::NValue::NNumeric::ECreate;

			void FInt::CreateChecked(const FString& Context, const UObject* WorldContext, const int32& InValue, AllocatedModifierType& OutModifier)
			{
				const int32 OldValue = Modifier.GetValue();
				const int32 NewValue = NCsModifier::NValue::NNumeric::NCreate::GetNewValue(GetType(), InValue, GetValue());

				Modifier.SetValue(NewValue);
				OutModifier.Copy(WorldContext, &Modifier);
				Modifier.SetValue(OldValue);
			}

			bool FInt::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_VALID_CHECKED(CreateMapType, GetType())
				CS_IS_VALID_CHECKED(Modifier);
				return true;
			}

			bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(CreateMapType, CreateType, GetType())
				CS_IS_VALID(Modifier)
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectileModifier_Create_Int

// FCsProjectileModifier_Create_Float
#pragma region

namespace NCsProjectileModifier_Create_Float
{
	using CreateType = NCsModifier::NValue::NNumeric::ECreate;

	void FImpl::CopyToCreateModifier(ThisType* This, CreateModifierType* CreateModifier)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(CreateModifier, Type, CreateType);
		CS_THIS_COPY_TO_PROXY(CreateModifier, Value);
		This->Modifier.CopyToModifier(CreateModifier->GetModifierPtr());
	}

	void FImpl::CopyToCreateModifierAsValue(const ThisType* This, CreateModifierType* CreateModifier)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(CreateModifier, Type, CreateType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(CreateModifier, Value);
		This->Modifier.CopyToModifierAsValue(CreateModifier->GetModifierPtr());
	}
}

bool FCsProjectileModifier_Create_Float::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueCreateModifier, Type)
	CS_IS_VALID_CHECKED(Modifier);
	return true;
}

bool FCsProjectileModifier_Create_Float::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsNumericValueCreateModifier, ECsNumericValueCreateModifier, Type)
	CS_IS_VALID(Modifier)
	return true;
}

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;
			using CreateMapType = NCsModifier::NValue::NNumeric::EMCreate;
			using CreateType = NCsModifier::NValue::NNumeric::ECreate;

			void FFloat::CreateChecked(const FString& Context, const UObject* WorldContext, const float& InValue, AllocatedModifierType& OutModifier)
			{
				const float OldValue = Modifier.GetValue();
				const float NewValue = NCsModifier::NValue::NNumeric::NCreate::GetNewValue(GetType(), InValue, GetValue());

				Modifier.SetValue(NewValue);

				OutModifier.Copy(WorldContext, &Modifier);

				Modifier.SetValue(OldValue);
			}

			bool FFloat::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_VALID_CHECKED(CreateMapType, GetType())
				CS_IS_VALID_CHECKED(Modifier);
				return true;
			}

			bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(CreateMapType, CreateType, GetType())
				CS_IS_VALID(Modifier)
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectileModifier_Create_Float

// FCsProjectileModifier_CreateInfo
#pragma region

namespace NCsProjectileModifier_CreateInfo
{
	using CreateIntModifierType = NCsProjectile::NModifier::NCreate::FInt;
	using CreateFloatModifierType = NCsProjectile::NModifier::NCreate::FFloat;

	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		// Int
		Info->Ints.Reset(This->Ints.Num());

		for (FCsProjectileModifier_Create_Int& From : This->Ints)
		{
			CreateIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToCreateModifier(&To);
		}
		// Float
		Info->Floats.Reset(This->Floats.Num());

		for (FCsProjectileModifier_Create_Float& From : This->Floats)
		{
			CreateFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToCreateModifier(&To);
		}
	}

	void FImpl::CopyToInfoAsValue(const ThisType* This, InfoType* Info)
	{
		// Int
		Info->Ints.Reset(This->Ints.Num());

		for (const FCsProjectileModifier_Create_Int& From : This->Ints)
		{
			CreateIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToCreateModifierAsValue(&To);
		}
		// Float
		Info->Floats.Reset(This->Floats.Num());

		for (const FCsProjectileModifier_Create_Float& From : This->Floats)
		{
			CreateFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToCreateModifierAsValue(&To);
		}
	}
}

bool FCsProjectileModifier_CreateInfo::IsValidChecked(const FString& Context) const
{
	// Int
	for (const FCsProjectileModifier_Create_Int& CreateModifier : Ints)
	{
		CS_IS_VALID_CHECKED(CreateModifier);
	}
	// Float
	for (const FCsProjectileModifier_Create_Float& CreateModifier : Floats)
	{
		CS_IS_VALID_CHECKED(CreateModifier);
	}
	return true;
}

bool FCsProjectileModifier_CreateInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	// Int
	for (const FCsProjectileModifier_Create_Int& CreateModifier : Ints)
	{
		CS_IS_VALID(CreateModifier)
	}
	// Float
	for (const FCsProjectileModifier_Create_Float& CreateModifier : Floats)
	{
		CS_IS_VALID(CreateModifier)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;
			using CreateIntModifierType = NCsProjectile::NModifier::NCreate::FInt;
			using CreateFloatModifierType = NCsProjectile::NModifier::NCreate::FFloat;

			void FInfo::CreateChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers)
			{
				OutModifiers.Reset(FMath::Max(OutModifiers.Max(), GetTotalSize()));
				AddChecked(Context, WorldContext, IntValues, FloatValues, OutModifiers);
			}

			void FInfo::AddChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers)
			{
				check(IsValidChecked(Context));
				checkf(Ints.Num() == IntValues.Num(), TEXT("%s: Mismatch between Ints.Num() != IntValues.Num() (%d != %d)."), *Context, Ints.Num(), IntValues.Num());
				checkf(Floats.Num() == FloatValues.Num(), TEXT("%s: Mismatch between Floats.Num() != FloatValues.Num() (%d != %d)."), *Context, Floats.Num(), FloatValues.Num());		
				checkf(OutModifiers.Max() - OutModifiers.Num() >= GetTotalSize(), TEXT("%s: OutModifiers does not have enough space."), *Context);

				// Ints
				{
					const int32 Count = Ints.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						CreateIntModifierType& Int				 = Ints[I];
						AllocatedModifierType& AllocatedModifier = OutModifiers.AddDefaulted_GetRef();

						Int.CreateChecked(Context, WorldContext, IntValues[I], AllocatedModifier);
					}
				}
				// Floats
				{
					const int32 Count = Floats.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						CreateFloatModifierType& Float			 = Floats[I];
						AllocatedModifierType& AllocatedModifier = OutModifiers.AddDefaulted_GetRef();

						Float.CreateChecked(Context, WorldContext, FloatValues[I], AllocatedModifier);
					}
				}
			}

			bool FInfo::IsValidChecked(const FString& Context) const
			{
				// Int
				for (const CreateIntModifierType& CreateModifier : Ints)
				{
					CS_IS_VALID_CHECKED(CreateModifier);
				}
				// Float
				for (const CreateFloatModifierType& CreateModifier : Floats)
				{
					CS_IS_VALID_CHECKED(CreateModifier);
				}
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				// Int
				for (const CreateIntModifierType& CreateModifier : Ints)
				{
					CS_IS_VALID(CreateModifier)
				}
				// Float
				for (const CreateFloatModifierType& CreateModifier : Floats)
				{
					CS_IS_VALID(CreateModifier)
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectileModifier_CreateInfo