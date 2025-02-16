// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Modifier/CsDamageModifierImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Modifier/CsLibrary_DamageModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsDamageModifierImpl)

// FCsDamageModifier_Int
#pragma region

namespace NCsDamageModifier_Int
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

bool FCsDamageModifier_Int::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, Application)
	CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, WhitelistByDataTypeSet)
	return true;
}

bool FCsDamageModifier_Int::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, Application)
	CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, WhitelistByDataTypeSet)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsDamage::NModifier::NInt::FInt);

	// NCsDamage::NModifier::NInt::NInt
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NInt, Int)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NModifier::NInt::FInt, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsDamage
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
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, ApplicationType::Multiply),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(WhitelistByDataTypeSet)
			{
				InterfaceMap = new FCsInterfaceMap();
			
				CS_INTERFACE_MAP_SET_ROOT(FInt);

				CS_INTERFACE_MAP_ADD(CsModifierType);
				CS_INTERFACE_MAP_ADD(CsIntModifierType);
				CS_INTERFACE_MAP_ADD(CsDamageModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetDamageModifierType);
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
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
				CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
				return true;
			}

			bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
				CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsDamage::NModifier::NCopy::ICopy)
			#pragma region
			void FInt::Copy(const CsDamageModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FInt* FromImpl = CsDamageModifierLibrary::PureStaticCastChecked<FInt>(Context, From);

				SetType(FromImpl->GetType());
				SetValue(FromImpl->GetValue());
				SetApplication(FromImpl->GetApplication());
				SetWhitelistByDataTypeSet(FromImpl->GetWhitelistByDataTypeSet());
			}

			#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsDamageModifier_Int

// FCsDamageModifier_Float
#pragma region

namespace NCsDamageModifier_Float
{
	using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

	void FImpl::CopyToModifier(ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY(Modifier, Type);
		CS_THIS_COPY_TO_PROXY(Modifier, Value);
		CS_THIS_COPY_TYPE_TO_PROXY(Modifier, Application, ApplicationType);
		CS_THIS_COPY_TO_PROXY(Modifier, WhitelistByDataTypeSet);
	}

	void FImpl::CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Type);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Value);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Modifier, Application, ApplicationType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, WhitelistByDataTypeSet);
	}
}

bool FCsDamageModifier_Float::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, Application)
	CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, WhitelistByDataTypeSet)
	return true;
}

bool FCsDamageModifier_Float::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, Application)
	CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, WhitelistByDataTypeSet)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsDamage::NModifier::NFloat::FFloat);

	// NCsDamage::NModifier::NFloat::NFloat
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NFloat, Float)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NModifier::NFloat::FFloat, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsDamage
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
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NNumeric::EApplication::Multiply),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(WhitelistByDataTypeSet)
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FFloat);

				CS_INTERFACE_MAP_ADD(CsModifierType);
				CS_INTERFACE_MAP_ADD(CsFloatModifierType);
				CS_INTERFACE_MAP_ADD(CsDamageModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetDamageModifierType);
				CS_INTERFACE_MAP_ADD(ICsIsValid);
				CS_INTERFACE_MAP_ADD(CopyType);
				CS_INTERFACE_MAP_ADD(ICsReset);

				CS_CTOR_SET_MEMBER_PROXY(Type);
				CS_CTOR_SET_MEMBER_PROXY(Value);
				CS_CTOR_SET_MEMBER_PROXY(Application);
				CS_CTOR_SET_MEMBER_PROXY(WhitelistByDataTypeSet);
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
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks
				CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
				CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
				return true;
			}

			bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
				CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsDamage::NModifier::NCopy::ICopy)
			#pragma region

			void FFloat::Copy(const CsDamageModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FFloat* FromImpl = CsDamageModifierLibrary::PureStaticCastChecked<FFloat>(Context, From);

				SetType(FromImpl->GetType());
				SetValue(FromImpl->GetValue());
				SetApplication(FromImpl->GetApplication());
				SetWhitelistByDataTypeSet(FromImpl->GetWhitelistByDataTypeSet());
			}

			#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsDamageModifier_Float

// FCsDamageModifier_Float_Range
#pragma region

namespace NCsDamageModifier_Float_Range
{
	using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

	void FImpl::CopyToModifier(ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY(Modifier, Type);
		CS_THIS_COPY_TO_PROXY(Modifier, Min);
		CS_THIS_COPY_TO_PROXY(Modifier, Max);
		CS_THIS_COPY_TYPE_TO_PROXY(Modifier, MinApplication, ApplicationType);
		CS_THIS_COPY_TYPE_TO_PROXY(Modifier, MaxApplication, ApplicationType);
		CS_THIS_COPY_TO_PROXY(Modifier, WhitelistByDataTypeSet);
	}

	void FImpl::CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Type);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Min);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Max);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Modifier, MinApplication, ApplicationType);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Modifier, MaxApplication, ApplicationType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, WhitelistByDataTypeSet);
	}
}

bool FCsDamageModifier_Float_Range::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, MinApplication)
	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, MaxApplication)
	CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, WhitelistByDataTypeSet)
	return true;
}

bool FCsDamageModifier_Float_Range::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, MinApplication)
	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, MaxApplication)
	CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, WhitelistByDataTypeSet)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsDamage::NModifier::NFloat::NRange::FRange);

	// NCsDamage::NModifier::NFloat::NRange::NRange
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_4(NCsDamage, NModifier, NFloat, NRange, Range)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NModifier::NFloat::NRange::FRange, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_4

#pragma endregion Cached

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NFloat
		{
			namespace NRange
			{

				FRange::FRange() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Min, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MinApplication, NCsModifier::NValue::NNumeric::EApplication::Multiply),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Max, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxApplication, NCsModifier::NValue::NNumeric::EApplication::Multiply),
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(WhitelistByDataTypeSet)
				{
					InterfaceMap = new FCsInterfaceMap();
			
					CS_INTERFACE_MAP_SET_ROOT(FRange);

					CS_INTERFACE_MAP_ADD(CsModifierType);
					CS_INTERFACE_MAP_ADD(CsFloatRangeModifierType);
					CS_INTERFACE_MAP_ADD(CsDamageModifierType);
					CS_INTERFACE_MAP_ADD(ICsGetDamageModifierType);
					CS_INTERFACE_MAP_ADD(ICsIsValid);
					CS_INTERFACE_MAP_ADD(CopyType);
					CS_INTERFACE_MAP_ADD(ICsReset);

					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(Min);
					CS_CTOR_SET_MEMBER_PROXY(MinApplication);
					CS_CTOR_SET_MEMBER_PROXY(Max);
					CS_CTOR_SET_MEMBER_PROXY(MaxApplication);
					CS_CTOR_SET_MEMBER_PROXY(WhitelistByDataTypeSet);
				}

				FRange::~FRange()
				{
					// ICsGetInterfaceMap
					delete InterfaceMap;
				}

				using ApplicationMapType = NCsModifier::NValue::NNumeric::EMApplication;

				// ICsIsValid
				#pragma region

				bool FRange::IsValidChecked(const FString& Context) const
				{
					CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, GetType())

					// TODO: FUTURE: Check Modifier Type and do appropriate checks

					CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetMinApplication())
					CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetMaxApplication())
					CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
					return true;
				}

				bool FRange::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
				{
					CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, GetType())

					// TODO: FUTURE: Check Modifier Type and do appropriate checks

					CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetMinApplication())
					CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetMaxApplication())
					CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
					return true;
				}

				#pragma endregion ICsIsValid

				// CopyType (NCsDamage::NModifier::NCopy::ICopy)
				#pragma region

				void FRange::Copy(const CsDamageModifierType* From)
				{
					CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

					const FRange* FromImpl = CsDamageModifierLibrary::PureStaticCastChecked<FRange>(Context, From);

					SetType(FromImpl->GetType());
					SetMin(FromImpl->GetMin());
					SetMinApplication(FromImpl->GetMinApplication());
					SetMax(FromImpl->GetMax());
					SetMaxApplication(FromImpl->GetMaxApplication());
					SetWhitelistByDataTypeSet(FromImpl->GetWhitelistByDataTypeSet());
				}

				#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)
			}
		}
	}
}

#pragma endregion FCsDamageModifier_Float_Range

// FCsDamageModifier_Toggle
#pragma region

namespace NCsDamageModifier_Toggle
{
	using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

	void FImpl::CopyToModifier(ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY(Modifier, Type);
		CS_THIS_COPY_TO_PROXY(Modifier, bEnable);
		CS_THIS_COPY_TO_PROXY(Modifier, WhitelistByDataTypeSet);
	}

	void FImpl::CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, Type);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, bEnable);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Modifier, WhitelistByDataTypeSet);
	}
}

bool FCsDamageModifier_Toggle::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, Type)
	CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, WhitelistByDataTypeSet)
	return true;
}

bool FCsDamageModifier_Toggle::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, Type)
	CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, WhitelistByDataTypeSet)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsDamage::NModifier::NToggle::FToggle);

	// NCsDamage::NModifier::NToggle::FToggle
	//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NToggle, Toggle)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NModifier::NToggle::FToggle, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NToggle
		{
			FToggle::FToggle() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bEnable, false),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(WhitelistByDataTypeSet)
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FToggle);

				CS_INTERFACE_MAP_ADD(CsModifierType);
				CS_INTERFACE_MAP_ADD(CsToggleModifierType);
				CS_INTERFACE_MAP_ADD(CsDamageModifierType);
				CS_INTERFACE_MAP_ADD(ICsGetDamageModifierType);
				CS_INTERFACE_MAP_ADD(ICsIsValid);
				CS_INTERFACE_MAP_ADD(CopyType);
				CS_INTERFACE_MAP_ADD(ICsReset);

				CS_CTOR_SET_MEMBER_PROXY(Type);
				CS_CTOR_SET_MEMBER_PROXY(bEnable);
				CS_CTOR_SET_MEMBER_PROXY(WhitelistByDataTypeSet);
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
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, GetType())
				CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
				return true;
			}

			bool FToggle::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, GetType())
				CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsDamage::NModifier::NCopy::ICopy)
			#pragma region

			void FToggle::Copy(const CsDamageModifierType* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FToggle* FromImpl = CsDamageModifierLibrary::PureStaticCastChecked<FToggle>(Context, From);

				SetType(FromImpl->GetType());
				SetbEnable(FromImpl->GetbEnable());
				SetWhitelistByDataTypeSet(FromImpl->GetWhitelistByDataTypeSet());
			}

			#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)
		}
	}
}

#pragma endregion FCsDamageModifier_Toggle

// FCsDamageModifierInfo
#pragma region

namespace NCsDamageModifierInfo
{
	using IntModifierType = NCsDamage::NModifier::NInt::FInt;
	using FloatModifierType = NCsDamage::NModifier::NFloat::FFloat;
	using FloatRangeModifierType = NCsDamage::NModifier::NFloat::NRange::FRange;
	using ToggleModifierType = NCsDamage::NModifier::NToggle::FToggle;

	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		// Ints
		Info->Ints.Reset(This->Ints.Num());

		for (FCsDamageModifier_Int& From : This->Ints)
		{
			IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		// Floats
		Info->Floats.Reset(This->Floats.Num());

		for (FCsDamageModifier_Float& From : This->Floats)
		{
			FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		// Floats
		Info->FloatRanges.Reset(This->FloatRanges.Num());

		for (FCsDamageModifier_Float_Range& From : This->FloatRanges)
		{
			FloatRangeModifierType& To = Info->FloatRanges.AddDefaulted_GetRef();
			From.CopyToModifier(&To);
		}
		// Toggles
		Info->Toggles.Reset(This->Toggles.Num());

		for (FCsDamageModifier_Toggle& From : This->Toggles)
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

		for (const FCsDamageModifier_Int& From : This->Ints)
		{
			IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		// Floats
		Info->Floats.Reset(This->Floats.Num());

		for (const FCsDamageModifier_Float& From : This->Floats)
		{
			FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		// Floats
		Info->FloatRanges.Reset(This->FloatRanges.Num());

		for (const FCsDamageModifier_Float_Range& From : This->FloatRanges)
		{
			FloatRangeModifierType& To = Info->FloatRanges.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		// Toggles
		Info->Toggles.Reset(This->Toggles.Num());

		for (const FCsDamageModifier_Toggle& From : This->Toggles)
		{
			ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
			From.CopyToModifierAsValue(&To);
		}
		Info->PopulateModifiers();
	}
}

bool FCsDamageModifierInfo::IsValidChecked(const FString& Context) const
{
	for (const FCsDamageModifier_Int& Modifier : Ints)
	{
		CS_IS_VALID_CHECKED(Modifier);
	}
	for (const FCsDamageModifier_Float& Modifier : Floats)
	{
		CS_IS_VALID_CHECKED(Modifier);
	}
	for (const FCsDamageModifier_Float_Range& Modifier : FloatRanges)
	{
		CS_IS_VALID_CHECKED(Modifier);
	}
	for (const FCsDamageModifier_Toggle& Modifier : Toggles)
	{
		CS_IS_VALID_CHECKED(Modifier);
	}
	return true;
}

bool FCsDamageModifierInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	for (const FCsDamageModifier_Int& Modifier : Ints)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsDamageModifier_Float& Modifier : Floats)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsDamageModifier_Float_Range& Modifier : FloatRanges)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsDamageModifier_Toggle& Modifier : Toggles)
	{
		CS_IS_VALID(Modifier)
	}
	return true;
}

namespace NCsDamage
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

			for (const FloatRangeModifierType& Modifier : FloatRanges)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			const int32 Total = Ints.Num() + Floats.Num() + FloatRanges.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE_CHECKED(Modifiers, ModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
		{
			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID(Modifier)
			}

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID(Modifier)
			}

			for (const FloatRangeModifierType& Modifier : FloatRanges)
			{
				CS_IS_VALID(Modifier)
			}

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID(Modifier)
			}

			const int32 Total = Ints.Num() + Floats.Num() + FloatRanges.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE(Modifiers, ModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL(Modifiers, ModifierType)
			return true;
		}
	}
}

#pragma endregion FCsDamageModifierInfo

// FCsDamageModifier_Create_Int
#pragma region

namespace NCsDamageModifier_Create_Int
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

bool FCsDamageModifier_Create_Int::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueCreateModifier, Type)
	CS_IS_VALID_CHECKED(Modifier);
	return true;
}

bool FCsDamageModifier_Create_Int::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsNumericValueCreateModifier, ECsNumericValueCreateModifier, Type)
	CS_IS_VALID(Modifier)
	return true;
}

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NCreate
		{
			using AllocatedModifierType = NCsDamage::NModifier::FAllocated;
			using CreateMapType = NCsModifier::NValue::NNumeric::EMCreate;

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

			bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(CreateMapType, CreateType, GetType())
				CS_IS_VALID(Modifier)
				return true;
			}
		}
	}
}

#pragma endregion FCsDamageModifier_Create_Int

// FCsDamageModifier_Create_Float
#pragma region

namespace NCsDamageModifier_Create_Float
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

bool FCsDamageModifier_Create_Float::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueCreateModifier, Type)
	CS_IS_VALID_CHECKED(Modifier);
	return true;
}

bool FCsDamageModifier_Create_Float::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsNumericValueCreateModifier, ECsNumericValueCreateModifier, Type)
	CS_IS_VALID(Modifier)
	return true;
}

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NCreate
		{
			using AllocatedModifierType = NCsDamage::NModifier::FAllocated;
			using CreateMapType = NCsModifier::NValue::NNumeric::EMCreate;

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

			bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				CS_IS_ENUM_VALID(CreateMapType, CreateType, GetType())
				CS_IS_VALID(Modifier)
				return true;
			}
		}
	}
}

#pragma endregion FCsDamageModifier_Create_Float

// FCsDamageModifier_CreateInfo
#pragma region

namespace NCsDamageModifier_CreateInfo
{
	using CreateIntModifierType = NCsDamage::NModifier::NCreate::FInt;
	using CreateFloatModifierType = NCsDamage::NModifier::NCreate::FFloat;

	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		// Int
		Info->Ints.Reset(This->Ints.Num());

		for (FCsDamageModifier_Create_Int& From : This->Ints)
		{
			CreateIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToCreateModifier(&To);
		}
		// Float
		Info->Floats.Reset(This->Floats.Num());

		for (FCsDamageModifier_Create_Float& From : This->Floats)
		{
			CreateFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToCreateModifier(&To);
		}
	}

	void FImpl::CopyToInfoAsValue(const ThisType* This, InfoType* Info)
	{
		// Int
		Info->Ints.Reset(This->Ints.Num());

		for (const FCsDamageModifier_Create_Int& From : This->Ints)
		{
			CreateIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
			From.CopyToCreateModifierAsValue(&To);
		}
		// Float
		Info->Floats.Reset(This->Floats.Num());

		for (const FCsDamageModifier_Create_Float& From : This->Floats)
		{
			CreateFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
			From.CopyToCreateModifierAsValue(&To);
		}
	}
}

bool FCsDamageModifier_CreateInfo::IsValidChecked(const FString& Context) const
{
	// Int
	for (const FCsDamageModifier_Create_Int& CreateModifier : Ints)
	{
		CS_IS_VALID_CHECKED(CreateModifier);
	}
	// Float
	for (const FCsDamageModifier_Create_Float& CreateModifier : Floats)
	{
		CS_IS_VALID_CHECKED(CreateModifier);
	}
	return true;
}

bool FCsDamageModifier_CreateInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	// Int
	for (const FCsDamageModifier_Create_Int& CreateModifier : Ints)
	{
		CS_IS_VALID(CreateModifier)
	}
	// Float
	for (const FCsDamageModifier_Create_Float& CreateModifier : Floats)
	{
		CS_IS_VALID(CreateModifier)
	}
	return true;
}

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NCreate
		{
			using AllocatedModifierType = NCsDamage::NModifier::FAllocated;
			using CreateIntModifierType = NCsDamage::NModifier::NCreate::FInt;
			using CreateFloatModifierType = NCsDamage::NModifier::NCreate::FFloat;

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

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
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

#pragma endregion FCsDamageModifier_CreateInfo