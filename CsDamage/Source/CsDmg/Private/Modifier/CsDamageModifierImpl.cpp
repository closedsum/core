// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Modifier/CsDamageModifierImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Modifier/CsLibrary_DamageModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

// FCsDamageModifier_Int
#pragma region

#define ModifierType NCsDamage::NModifier::FInt

void FCsDamageModifier_Int::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
	Modifier->SetWhitelistByDataTypeSet(&WhitelistByDataTypeSet);
}

void FCsDamageModifier_Int::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
	Modifier->SetWhitelistByDataTypeSet(WhitelistByDataTypeSet);
}

#undef ModifierType

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

const FName NCsDamage::NModifier::FInt::Name = FName("NCsDamage::NModifier::FInt");

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NInt
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::FInt, Copy);
				}
			}
		}

		FInt::FInt() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NNumeric::EApplication::Multiply),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(WhitelistByDataTypeSet)
		{
			InterfaceMap = new FCsInterfaceMap();
			
			InterfaceMap->SetRoot<FInt>(this);

			typedef NCsModifier::IModifier ModifierType;
			typedef NCsModifier::NInt::IInt IntModifierType;
			typedef NCsDamage::NModifier::IModifier DmgModifierType;
			typedef NCsDamage::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<IntModifierType>(static_cast<IntModifierType*>(this));
			InterfaceMap->Add<DmgModifierType>(static_cast<DmgModifierType*>(this));
			InterfaceMap->Add<ICsGetDamageModifierType>(static_cast<ICsGetDamageModifierType*>(this));
			InterfaceMap->Add<ICsIsValid>(static_cast<ICsIsValid*>(this));
			InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
			InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

			CS_CTOR_SET_MEMBER_PROXY(Type);
			CS_CTOR_SET_MEMBER_PROXY(Value);
			CS_CTOR_SET_MEMBER_PROXY(Application);
		}

		FInt::~FInt()
		{
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}

		// ICsIsValid
		#pragma region

		bool FInt::IsValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

			CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
			CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
			return true;
		}

		bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
			CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsDamage::NModifier::NCopy::ICopy)
		#pragma region

		#define DmgModifierType NCsDamage::NModifier::IModifier
		void FInt::Copy(const DmgModifierType* From)
		{
		#undef DmgModifierType

			using namespace NCsDamage::NModifier::NInt::NCached;

			const FString& Context = Str::Copy;

			typedef NCsDamage::NModifier::FLibrary DmgModifierLibrary;

			const FInt* FromImpl = DmgModifierLibrary::PureStaticCastChecked<FInt>(Context, From);

			SetType(FromImpl->GetType());
			SetValue(FromImpl->GetValue());
			SetApplication(FromImpl->GetApplication());
			SetWhitelistByDataTypeSet(FromImpl->GetWhitelistByDataTypeSet());
		}

		#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsDamageModifier_Int

// FCsDamageModifier_Float
#pragma region

#define ModifierType NCsDamage::NModifier::FFloat

void FCsDamageModifier_Float::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
	Modifier->SetWhitelistByDataTypeSet(&WhitelistByDataTypeSet);
}

void FCsDamageModifier_Float::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
	Modifier->SetWhitelistByDataTypeSet(WhitelistByDataTypeSet);
}

#undef ModifierType

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

const FName NCsDamage::NModifier::FFloat::Name = FName("NCsDamage::NModifier::FFloat");

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NFloat
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::FFloat, Copy);
				}
			}
		}

		FFloat::FFloat() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NNumeric::EApplication::Multiply),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(WhitelistByDataTypeSet)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FFloat>(this);

			typedef NCsModifier::IModifier ModifierType;
			typedef NCsModifier::NFloat::IFloat FloatModifierType;
			typedef NCsDamage::NModifier::IModifier DmgModifierType;
			typedef NCsDamage::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<FloatModifierType>(static_cast<FloatModifierType*>(this));
			InterfaceMap->Add<DmgModifierType>(static_cast<DmgModifierType*>(this));
			InterfaceMap->Add<ICsGetDamageModifierType>(static_cast<ICsGetDamageModifierType*>(this));
			InterfaceMap->Add<ICsIsValid>(static_cast<ICsIsValid*>(this));
			InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
			InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

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

		// ICsIsValid
		#pragma region

		bool FFloat::IsValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

			CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
			CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
			return true;
		}

		bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
			CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsDamage::NModifier::NCopy::ICopy)
		#pragma region

		#define DmgModifierType NCsDamage::NModifier::IModifier
		void FFloat::Copy(const DmgModifierType* From)
		{
		#undef DmgModifierType

			using namespace NCsDamage::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			typedef NCsDamage::NModifier::FLibrary DmgModifierLibrary;

			const FFloat* FromImpl = DmgModifierLibrary::PureStaticCastChecked<FFloat>(Context, From);

			SetType(FromImpl->GetType());
			SetValue(FromImpl->GetValue());
			SetApplication(FromImpl->GetApplication());
			SetWhitelistByDataTypeSet(FromImpl->GetWhitelistByDataTypeSet());
		}

		#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsDamageModifier_Float

// FCsDamageModifier_Float_Range
#pragma region

#define ModifierType NCsDamage::NModifier::NFloat::FRange

void FCsDamageModifier_Float_Range::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetMin(&Min);
	Modifier->SetMax(&Max);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetMinApplication((ApplicationType*)(&MinApplication));
	Modifier->SetMaxApplication((ApplicationType*)(&MaxApplication));
	Modifier->SetWhitelistByDataTypeSet(&WhitelistByDataTypeSet);
}

void FCsDamageModifier_Float_Range::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetMin(Min);
	Modifier->SetMax(Max);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetMinApplication((ApplicationType)MinApplication);
	Modifier->SetMaxApplication((ApplicationType)MaxApplication);
	Modifier->SetWhitelistByDataTypeSet(WhitelistByDataTypeSet);
}

#undef ModifierType

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

const FName NCsDamage::NModifier::NFloat::FRange::Name = FName("NCsDamage::NModifier::NFloat::FRange");

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NFloat
		{
			namespace NRange
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::NFloat::FRange, Copy);
					}
				}
			}

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

				InterfaceMap->SetRoot<FRange>(this);

				typedef NCsModifier::IModifier ModifierType;
				typedef NCsModifier::NFloat::NRange::IRange FloatRangeModifierType;
				typedef NCsDamage::NModifier::IModifier DmgModifierType;
				typedef NCsDamage::NModifier::NCopy::ICopy CopyType;

				InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
				InterfaceMap->Add<FloatRangeModifierType>(static_cast<FloatRangeModifierType*>(this));
				InterfaceMap->Add<DmgModifierType>(static_cast<DmgModifierType*>(this));
				InterfaceMap->Add<ICsGetDamageModifierType>(static_cast<ICsGetDamageModifierType*>(this));
				InterfaceMap->Add<ICsIsValid>(static_cast<ICsIsValid*>(this));
				InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
				InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

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

			// ICsIsValid
			#pragma region

			bool FRange::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

				CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetMinApplication())
				CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetMaxApplication())
				CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
				return true;
			}

			bool FRange::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsDamageModifier, FECsDamageModifier, GetType())

				// TODO: FUTURE: Check Modifier Type and do appropriate checks

				typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
				typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

				CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetMinApplication())
				CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetMaxApplication())
				CS_IS_ENUM_STRUCT_SET_UNIQUE(EMCsDamageData, FECsDamageData, GetWhitelistByDataTypeSet())
				return true;
			}

			#pragma endregion ICsIsValid

			// CopyType (NCsDamage::NModifier::NCopy::ICopy)
			#pragma region

			#define DmgModifierType NCsDamage::NModifier::IModifier
			void FRange::Copy(const DmgModifierType* From)
			{
			#undef DmgModifierType

				using namespace NCsDamage::NModifier::NFloat::NCached;

				const FString& Context = Str::Copy;

				typedef NCsDamage::NModifier::FLibrary DmgModifierLibrary;

				const FRange* FromImpl = DmgModifierLibrary::PureStaticCastChecked<FRange>(Context, From);

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

#pragma endregion FCsDamageModifier_Float_Range

// FCsDamageModifier_Toggle
#pragma region

#define ModifierType NCsDamage::NModifier::FToggle

void FCsDamageModifier_Toggle::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetbEnable(&bEnable);
	Modifier->SetWhitelistByDataTypeSet(&WhitelistByDataTypeSet);
}

void FCsDamageModifier_Toggle::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetbEnable(bEnable);
	Modifier->SetWhitelistByDataTypeSet(WhitelistByDataTypeSet);
}

#undef ModifierType

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

const FName NCsDamage::NModifier::FToggle::Name = FName("NCsDamage::NModifier::FToggle");

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NToggle
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::FToggle, Copy);
				}
			}
		}

		FToggle::FToggle() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(bEnable, false),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(WhitelistByDataTypeSet)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FToggle>(this);

			typedef NCsModifier::IModifier ModifierType;
			typedef NCsModifier::NToggle::IToggle ToggleModifierType;
			typedef NCsDamage::NModifier::IModifier DmgModifierType;
			typedef NCsDamage::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<ToggleModifierType>(static_cast<ToggleModifierType*>(this));
			InterfaceMap->Add<DmgModifierType>(static_cast<DmgModifierType*>(this));
			InterfaceMap->Add<ICsGetDamageModifierType>(static_cast<ICsGetDamageModifierType*>(this));
			InterfaceMap->Add<ICsIsValid>(static_cast<ICsIsValid*>(this));
			InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
			InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

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

		#define DmgModifierType NCsDamage::NModifier::IModifier
		void FToggle::Copy(const DmgModifierType* From)
		{
		#undef DmgModifierType

			using namespace NCsDamage::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			typedef NCsDamage::NModifier::FLibrary DmgModifierLibrary;

			const FToggle* FromImpl = DmgModifierLibrary::PureStaticCastChecked<FToggle>(Context, From);

			SetType(FromImpl->GetType());
			SetbEnable(FromImpl->GetbEnable());
			SetWhitelistByDataTypeSet(FromImpl->GetWhitelistByDataTypeSet());
		}

		#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsDamageModifier_Toggle

// FCsDamageModifierInfo
#pragma region

#define InfoType NCsDamage::NModifier::FInfo

void FCsDamageModifierInfo::CopyToInfo(InfoType* Info)
{
	// Ints
	typedef NCsDamage::NModifier::FInt IntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (FCsDamageModifier_Int& From : Ints)
	{
		IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	// Floats
	typedef NCsDamage::NModifier::FFloat FloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (FCsDamageModifier_Float& From : Floats)
	{
		FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	// Floats
	typedef NCsDamage::NModifier::NFloat::FRange FloatRangeModifierType;

	Info->FloatRanges.Reset(FloatRanges.Num());

	for (FCsDamageModifier_Float_Range& From : FloatRanges)
	{
		FloatRangeModifierType& To = Info->FloatRanges.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	// Toggles
	typedef NCsDamage::NModifier::FToggle ToggleModifierType;

	Info->Toggles.Reset(Toggles.Num());

	for (FCsDamageModifier_Toggle& From : Toggles)
	{
		ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	Info->PopulateModifiers();
}

void FCsDamageModifierInfo::CopyToInfoAsValue(InfoType* Info) const
{
	// Ints
	typedef NCsDamage::NModifier::FInt IntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (const FCsDamageModifier_Int& From : Ints)
	{
		IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	// Floats
	typedef NCsDamage::NModifier::FFloat FloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (const FCsDamageModifier_Float& From : Floats)
	{
		FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	// Float Ranges
	typedef NCsDamage::NModifier::NFloat::FRange FloatRangeModifierType;

	Info->FloatRanges.Reset(FloatRanges.Num());

	for (const FCsDamageModifier_Float_Range& From : FloatRanges)
	{
		FloatRangeModifierType& To = Info->FloatRanges.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	// Toggles
	typedef NCsDamage::NModifier::FToggle ToggleModifierType;

	Info->Toggles.Reset(Toggles.Num());

	for (const FCsDamageModifier_Toggle& From : Toggles)
	{
		ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	Info->PopulateModifiers();
}

#undef InfoType

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
			typedef NCsDamage::NModifier::FInt IntModifierType;

			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsDamage::NModifier::FFloat FloatModifierType;

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsDamage::NModifier::NFloat::FRange FloatRangeModifierType;

			for (const FloatRangeModifierType& Modifier : FloatRanges)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsDamage::NModifier::FToggle ToggleModifierType;

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsDamage::NModifier::IModifier ModifierType;

			const int32 Total = Ints.Num() + Floats.Num() + FloatRanges.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE_CHECKED(Modifiers, ModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
		{
			typedef NCsDamage::NModifier::FInt IntModifierType;

			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsDamage::NModifier::FFloat FloatModifierType;

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsDamage::NModifier::NFloat::FRange FloatRangeModifierType;

			for (const FloatRangeModifierType& Modifier : FloatRanges)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsDamage::NModifier::FToggle ToggleModifierType;

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsDamage::NModifier::IModifier ModifierType;

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

#define CreateModifierType NCsDamage::NModifier::NCreate::FInt

void FCsDamageModifier_Create_Int::CopyToCreateModifier(CreateModifierType* CreateModifier)
{
	typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

	CreateModifier->SetType((CreateType*)(&Type));
	CreateModifier->SetValue(&Value);
	Modifier.CopyToModifier(CreateModifier->GetModifierPtr());
}

void FCsDamageModifier_Create_Int::CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const
{
	typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

	CreateModifier->SetType((CreateType)Type);
	CreateModifier->SetValue(Value);
	Modifier.CopyToModifierAsValue(CreateModifier->GetModifierPtr());
}

#undef CreateModifierType

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
			#define AllocatedModifierType NCsDamage::NModifier::FAllocated
			void FInt::CreateChecked(const FString& Context, const UObject* WorldContext, const int32& InValue, AllocatedModifierType& OutModifier)
			{
			#undef AllocatedModifierType
				
				const int32 OldValue = Modifier.GetValue();
				const int32 NewValue = NCsModifier::NValue::NNumeric::NCreate::GetNewValue(GetType(), InValue, GetValue());

				Modifier.SetValue(NewValue);

				OutModifier.Copy(WorldContext, &Modifier);

				Modifier.SetValue(OldValue);
			}

			bool FInt::IsValidChecked(const FString& Context) const
			{
				typedef NCsModifier::NValue::NNumeric::EMCreate CreateMapType;

				CS_IS_ENUM_VALID_CHECKED(CreateMapType, GetType())
				CS_IS_VALID_CHECKED(Modifier);
				return true;
			}

			bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				typedef NCsModifier::NValue::NNumeric::EMCreate CreateMapType;
				typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

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

#define CreateModifierType NCsDamage::NModifier::NCreate::FFloat

void FCsDamageModifier_Create_Float::CopyToCreateModifier(CreateModifierType* CreateModifier)
{
	typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

	CreateModifier->SetType((CreateType*)(&Type));
	CreateModifier->SetValue(&Value);
	Modifier.CopyToModifier(CreateModifier->GetModifierPtr());
}

void FCsDamageModifier_Create_Float::CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const
{
	typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

	CreateModifier->SetType((CreateType)Type);
	CreateModifier->SetValue(Value);
	Modifier.CopyToModifierAsValue(CreateModifier->GetModifierPtr());
}

#undef CreateModifierType

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
			#define AllocatedModifierType NCsDamage::NModifier::FAllocated
			void FFloat::CreateChecked(const FString& Context, const UObject* WorldContext, const float& InValue, AllocatedModifierType& OutModifier)
			{
			#undef AllocatedModifierType
				
				const float OldValue = Modifier.GetValue();
				const float NewValue = NCsModifier::NValue::NNumeric::NCreate::GetNewValue(GetType(), InValue, GetValue());

				Modifier.SetValue(NewValue);

				OutModifier.Copy(WorldContext, &Modifier);

				Modifier.SetValue(OldValue);
			}

			bool FFloat::IsValidChecked(const FString& Context) const
			{
				typedef NCsModifier::NValue::NNumeric::EMCreate CreateMapType;

				CS_IS_ENUM_VALID_CHECKED(CreateMapType, GetType())
				CS_IS_VALID_CHECKED(Modifier);
				return true;
			}

			bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				typedef NCsModifier::NValue::NNumeric::EMCreate CreateMapType;
				typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

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

#define InfoType NCsDamage::NModifier::NCreate::FInfo

void FCsDamageModifier_CreateInfo::CopyToInfo(InfoType* Info)
{
	// Int
	typedef NCsDamage::NModifier::NCreate::FInt CreateIntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (FCsDamageModifier_Create_Int& From : Ints)
	{
		CreateIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToCreateModifier(&To);
	}
	// Float
	typedef NCsDamage::NModifier::NCreate::FFloat CreateFloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (FCsDamageModifier_Create_Float& From : Floats)
	{
		CreateFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToCreateModifier(&To);
	}
}

void FCsDamageModifier_CreateInfo::CopyToInfoAsValue(InfoType* Info) const
{
	// Int
	typedef NCsDamage::NModifier::NCreate::FInt CreateIntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (const FCsDamageModifier_Create_Int& From : Ints)
	{
		CreateIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToCreateModifierAsValue(&To);
	}
	// Float
	typedef NCsDamage::NModifier::NCreate::FFloat CreateFloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (const FCsDamageModifier_Create_Float& From : Floats)
	{
		CreateFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToCreateModifierAsValue(&To);
	}
}

#undef InfoType

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
			#define AllocatedModifierType NCsDamage::NModifier::FAllocated

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

					typedef NCsDamage::NModifier::NCreate::FInt CreateIntModifierType;

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

					typedef NCsDamage::NModifier::NCreate::FFloat CreateFloatModifierType;

					for (int32 I = 0; I < Count; ++I)
					{
						CreateFloatModifierType& Float			 = Floats[I];
						AllocatedModifierType& AllocatedModifier = OutModifiers.AddDefaulted_GetRef();

						Float.CreateChecked(Context, WorldContext, FloatValues[I], AllocatedModifier);
					}
				}
			}

			#undef AllocatedModifierType

			bool FInfo::IsValidChecked(const FString& Context) const
			{
				// Int
				typedef NCsDamage::NModifier::NCreate::FInt CreateIntModifierType;

				for (const CreateIntModifierType& CreateModifier : Ints)
				{
					CS_IS_VALID_CHECKED(CreateModifier);
				}
				// Float
				typedef NCsDamage::NModifier::NCreate::FFloat CreateFloatModifierType;

				for (const CreateFloatModifierType& CreateModifier : Floats)
				{
					CS_IS_VALID_CHECKED(CreateModifier);
				}
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
			{
				// Int
				typedef NCsDamage::NModifier::NCreate::FInt CreateIntModifierType;

				for (const CreateIntModifierType& CreateModifier : Ints)
				{
					CS_IS_VALID(CreateModifier)
				}
				// Float
				typedef NCsDamage::NModifier::NCreate::FFloat CreateFloatModifierType;

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