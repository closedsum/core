// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsWeaponModifierImpl.h"

// Library
#include "Modifier/CsLibrary_WeaponModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

// FCsWeaponModifier_Int
#pragma region

#define ModifierType NCsWeapon::NModifier::FInt

void FCsWeaponModifier_Int::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
}

void FCsWeaponModifier_Int::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
}

#undef ModifierType

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

const FName NCsWeapon::NModifier::FInt::Name = FName("NCsWeapon::NModifier::FInt");

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NInt
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NModifier::FInt, Copy);
				}
			}
		}

		FInt::FInt() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NNumeric::EApplication::Multiply)
		{
			InterfaceMap = new FCsInterfaceMap();
			
			InterfaceMap->SetRoot<FInt>(this);

			typedef NCsModifier::IModifier ModifierType;
			typedef NCsModifier::NInt::IInt IntModifierType;
			typedef NCsWeapon::NModifier::IModifier WeaponModifierType;
			typedef NCsWeapon::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<IntModifierType>(static_cast<IntModifierType*>(this));
			InterfaceMap->Add<WeaponModifierType>(static_cast<WeaponModifierType*>(this));
			InterfaceMap->Add<ICsGetWeaponModifierType>(static_cast<ICsGetWeaponModifierType*>(this));
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
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

			CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
			return true;
		}

		bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsWeaponModifier, FECsWeaponModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
		#pragma region

		#define WeaponModifierType NCsWeapon::NModifier::IModifier
		void FInt::Copy(const WeaponModifierType* From)
		{
		#undef WeaponModifierType

			using namespace NCsWeapon::NModifier::NInt::NCached;

			const FString& Context = Str::Copy;

			typedef NCsWeapon::NModifier::FLibrary WeaponModifierLibrary;

			const FInt* FromImpl = WeaponModifierLibrary::PureStaticCastChecked<FInt>(Context, From);

			SetType(FromImpl->GetType());
			SetValue(FromImpl->GetValue());
			SetApplication(FromImpl->GetApplication());
		}

		#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsWeaponModifier_Int

// FCsWeaponModifier_Float
#pragma region

#define ModifierType NCsWeapon::NModifier::FFloat

void FCsWeaponModifier_Float::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
}

void FCsWeaponModifier_Float::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
}

#undef ModifierType

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

const FName NCsWeapon::NModifier::FFloat::Name = FName("NCsWeapon::NModifier::FFloat");

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NFloat
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NModifier::FFloat, Copy);
				}
			}
		}

		FFloat::FFloat() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NNumeric::EApplication::Multiply)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FFloat>(this);

			typedef NCsModifier::IModifier ModifierType;
			typedef NCsModifier::NFloat::IFloat FloatModifierType;
			typedef NCsWeapon::NModifier::IModifier WeaponModifierType;
			typedef NCsWeapon::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<FloatModifierType>(static_cast<FloatModifierType*>(this));
			InterfaceMap->Add<WeaponModifierType>(static_cast<WeaponModifierType*>(this));
			InterfaceMap->Add<ICsGetWeaponModifierType>(static_cast<ICsGetWeaponModifierType*>(this));
			InterfaceMap->Add<ICsIsValid>(static_cast<ICsIsValid*>(this));
			InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
			InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

			CS_CTOR_SET_MEMBER_PROXY(Type);
			CS_CTOR_SET_MEMBER_PROXY(Value);
			CS_CTOR_SET_MEMBER_PROXY(Application);
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
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

			CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
			return true;
		}

		bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsWeaponModifier, FECsWeaponModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
		#pragma region

		#define WeaponModifierType NCsWeapon::NModifier::IModifier
		void FFloat::Copy(const WeaponModifierType* From)
		{
		#undef WeaponModifierType

			using namespace NCsWeapon::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			typedef NCsWeapon::NModifier::FLibrary WeaponModifierLibrary;

			const FFloat* FromImpl = WeaponModifierLibrary::PureStaticCastChecked<FFloat>(Context, From);

			SetType(FromImpl->GetType());
			SetValue(FromImpl->GetValue());
			SetApplication(FromImpl->GetApplication());
		}

		#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsWeaponModifier_Float

// FCsWeaponModifier_Toggle
#pragma region

#define ModifierType NCsWeapon::NModifier::FToggle

void FCsWeaponModifier_Toggle::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetbEnable(&bEnable);
}

void FCsWeaponModifier_Toggle::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetbEnable(bEnable);
}

#undef ModifierType

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

const FName NCsWeapon::NModifier::FToggle::Name = FName("NCsWeapon::NModifier::FToggle");

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NToggle
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NModifier::FToggle, Copy);
				}
			}
		}

		FToggle::FToggle() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(bEnable, false)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FToggle>(this);

			typedef NCsModifier::IModifier ModifierType;
			typedef NCsModifier::NToggle::IToggle ToggleModifierType;
			typedef NCsWeapon::NModifier::IModifier WeaponModifierType;
			typedef NCsWeapon::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<ToggleModifierType>(static_cast<ToggleModifierType*>(this));
			InterfaceMap->Add<WeaponModifierType>(static_cast<WeaponModifierType*>(this));
			InterfaceMap->Add<ICsGetWeaponModifierType>(static_cast<ICsGetWeaponModifierType*>(this));
			InterfaceMap->Add<ICsIsValid>(static_cast<ICsIsValid*>(this));
			InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
			InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

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

		#define WeaponModifierType NCsWeapon::NModifier::IModifier
		void FToggle::Copy(const WeaponModifierType* From)
		{
		#undef WeaponModifierType

			using namespace NCsWeapon::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			typedef NCsWeapon::NModifier::FLibrary WeaponModifierLibrary;

			const FToggle* FromImpl = WeaponModifierLibrary::PureStaticCastChecked<FToggle>(Context, From);

			SetType(FromImpl->GetType());
			SetbEnable(FromImpl->GetbEnable());
		}

		#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsWeaponModifier_Toggle