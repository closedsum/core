// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsProjectileModifierImpl.h"

// Library
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

// FCsProjectileModifier_Int
#pragma region

#define ModifierType NCsProjectile::NModifier::FInt

void FCsProjectileModifier_Int::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
}

void FCsProjectileModifier_Int::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
}

#undef ModifierType

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

const FName NCsProjectile::NModifier::FInt::Name = FName("NCsProjectile::NModifier::FInt");

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NInt
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::FInt, Copy);
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
			typedef NCsProjectile::NModifier::IModifier PrjModifierType;
			typedef NCsProjectile::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<IntModifierType>(static_cast<IntModifierType*>(this));
			InterfaceMap->Add<PrjModifierType>(static_cast<PrjModifierType*>(this));
			InterfaceMap->Add<ICsGetProjectileModifierType>(static_cast<ICsGetProjectileModifierType*>(this));
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
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

			CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
			return true;
		}

		bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsProjectileModifier, FECsProjectileModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
		#pragma region

		#define PrjModifierType NCsProjectile::NModifier::IModifier
		void FInt::Copy(const PrjModifierType* From)
		{
		#undef PrjModifierType

			using namespace NCsProjectile::NModifier::NInt::NCached;

			const FString& Context = Str::Copy;

			typedef NCsProjectile::NModifier::FLibrary PrjModifierLibrary;

			const FInt* FromImpl = PrjModifierLibrary::PureStaticCastChecked<FInt>(Context, From);

			SetType(FromImpl->GetType());
			SetValue(FromImpl->GetValue());
			SetApplication(FromImpl->GetApplication());
		}

		#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsProjectileModifier_Int

// FCsProjectileModifier_Float
#pragma region

#define ModifierType NCsProjectile::NModifier::FFloat

void FCsProjectileModifier_Float::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
}

void FCsProjectileModifier_Float::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
}

#undef ModifierType

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

const FName NCsProjectile::NModifier::FFloat::Name = FName("NCsProjectile::NModifier::FFloat");

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NFloat
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::FFloat, Copy);
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
			typedef NCsProjectile::NModifier::IModifier PrjModifierType;
			typedef NCsProjectile::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<FloatModifierType>(static_cast<FloatModifierType*>(this));
			InterfaceMap->Add<PrjModifierType>(static_cast<PrjModifierType*>(this));
			InterfaceMap->Add<ICsGetProjectileModifierType>(static_cast<ICsGetProjectileModifierType*>(this));
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
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

			CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
			return true;
		}

		bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsProjectileModifier, FECsProjectileModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
		#pragma region

		#define PrjModifierType NCsProjectile::NModifier::IModifier
		void FFloat::Copy(const PrjModifierType* From)
		{
		#undef PrjModifierType

			using namespace NCsProjectile::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			typedef NCsProjectile::NModifier::FLibrary PrjModifierLibrary;

			const FFloat* FromImpl = PrjModifierLibrary::PureStaticCastChecked<FFloat>(Context, From);

			SetType(FromImpl->GetType());
			SetValue(FromImpl->GetValue());
			SetApplication(FromImpl->GetApplication());
		}

		#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsProjectileModifier_Float

// FCsProjectileModifier_Toggle
#pragma region

#define ModifierType NCsProjectile::NModifier::FToggle

void FCsProjectileModifier_Toggle::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetbEnable(&bEnable);
}

void FCsProjectileModifier_Toggle::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetbEnable(bEnable);
}

#undef ModifierType

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

const FName NCsProjectile::NModifier::FToggle::Name = FName("NCsProjectile::NModifier::FToggle");

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NToggle
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::FToggle, Copy);
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
			typedef NCsProjectile::NModifier::IModifier PrjModifierType;
			typedef NCsProjectile::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<ToggleModifierType>(static_cast<ToggleModifierType*>(this));
			InterfaceMap->Add<PrjModifierType>(static_cast<PrjModifierType*>(this));
			InterfaceMap->Add<ICsGetProjectileModifierType>(static_cast<ICsGetProjectileModifierType*>(this));
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

		#define PrjModifierType NCsProjectile::NModifier::IModifier
		void FToggle::Copy(const PrjModifierType* From)
		{
		#undef PrjModifierType

			using namespace NCsProjectile::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			typedef NCsProjectile::NModifier::FLibrary PrjModifierLibrary;

			const FToggle* FromImpl = PrjModifierLibrary::PureStaticCastChecked<FToggle>(Context, From);

			SetType(FromImpl->GetType());
			SetbEnable(FromImpl->GetbEnable());
		}

		#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsProjectileModifier_Toggle