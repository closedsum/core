// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Modifier/CsSpawnerModifierImpl.h"

// Library
#include "Spawner/Modifier/CsLibrary_SpawnerModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

// FCsSpawnerModifier_Int
#pragma region

#define ModifierType NCsSpawner::NModifier::FInt

void FCsSpawnerModifier_Int::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
}

void FCsSpawnerModifier_Int::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
}

#undef ModifierType

bool FCsSpawnerModifier_Int::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, Application)
	return true;
}

bool FCsSpawnerModifier_Int::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsSpawnerModifier, FECsSpawnerModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, Application)
	return true;
}

const FName NCsSpawner::NModifier::FInt::Name = FName("NCsSpawner::NModifier::FInt");

namespace NCsSpawner
{
	namespace NModifier
	{
		namespace NInt
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NModifier::FInt, Copy);
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
			typedef NCsSpawner::NModifier::IModifier SpawnerModifierType;
			typedef NCsSpawner::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<IntModifierType>(static_cast<IntModifierType*>(this));
			InterfaceMap->Add<SpawnerModifierType>(static_cast<SpawnerModifierType*>(this));
			InterfaceMap->Add<ICsGetSpawnerModifierType>(static_cast<ICsGetSpawnerModifierType*>(this));
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
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

			CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
			return true;
		}

		bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsSpawnerModifier, FECsSpawnerModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsSpawner::NModifier::NCopy::ICopy)
		#pragma region

		#define SpawnerModifierType NCsSpawner::NModifier::IModifier
		void FInt::Copy(const SpawnerModifierType* From)
		{
		#undef SpawnerModifierType

			using namespace NCsSpawner::NModifier::NInt::NCached;

			const FString& Context = Str::Copy;

			typedef NCsSpawner::NModifier::FLibrary SpawnerModifierLibrary;

			const FInt* FromImpl = SpawnerModifierLibrary::PureStaticCastChecked<FInt>(Context, From);

			SetType(FromImpl->GetType());
			SetValue(FromImpl->GetValue());
			SetApplication(FromImpl->GetApplication());
		}

		#pragma endregion CopyType (NCsSpawner::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsSpawnerModifier_Int

// FCsSpawnerModifier_Float
#pragma region

#define ModifierType NCsSpawner::NModifier::FFloat

void FCsSpawnerModifier_Float::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
}

void FCsSpawnerModifier_Float::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
}

#undef ModifierType

bool FCsSpawnerModifier_Float::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID_CHECKED(EMCsNumericValueModifierApplication, Application)
	return true;
}

bool FCsSpawnerModifier_Float::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsSpawnerModifier, FECsSpawnerModifier, Type)

	// TODO: FUTURE: Check Modifier Type and do appropriate checks

	CS_IS_ENUM_VALID(EMCsNumericValueModifierApplication, ECsNumericValueModifierApplication, Application)
	return true;
}

const FName NCsSpawner::NModifier::FFloat::Name = FName("NCsSpawner::NModifier::FFloat");

namespace NCsSpawner
{
	namespace NModifier
	{
		namespace NFloat
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NModifier::FFloat, Copy);
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
			typedef NCsSpawner::NModifier::IModifier SpawnerModifierType;
			typedef NCsSpawner::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<FloatModifierType>(static_cast<FloatModifierType*>(this));
			InterfaceMap->Add<SpawnerModifierType>(static_cast<SpawnerModifierType*>(this));
			InterfaceMap->Add<ICsGetSpawnerModifierType>(static_cast<ICsGetSpawnerModifierType*>(this));
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
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;

			CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
			return true;
		}

		bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsSpawnerModifier, FECsSpawnerModifier, GetType())

			// TODO: FUTURE: Check Modifier Type and do appropriate checks

			typedef NCsModifier::NValue::NNumeric::EMApplication ApplicationMapType;
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsSpawner::NModifier::NCopy::ICopy)
		#pragma region

		#define SpawnerModifierType NCsSpawner::NModifier::IModifier
		void FFloat::Copy(const SpawnerModifierType* From)
		{
		#undef SpawnerModifierType

			using namespace NCsSpawner::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			typedef NCsSpawner::NModifier::FLibrary SpawnerModifierLibrary;

			const FFloat* FromImpl = SpawnerModifierLibrary::PureStaticCastChecked<FFloat>(Context, From);

			SetType(FromImpl->GetType());
			SetValue(FromImpl->GetValue());
			SetApplication(FromImpl->GetApplication());
		}

		#pragma endregion CopyType (NCsSpawner::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsSpawnerModifier_Float

// FCsSpawnerModifier_Toggle
#pragma region

#define ModifierType NCsSpawner::NModifier::FToggle

void FCsSpawnerModifier_Toggle::CopyToModifier(ModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetbEnable(&bEnable);
}

void FCsSpawnerModifier_Toggle::CopyToModifierAsValue(ModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetbEnable(bEnable);
}

#undef ModifierType

bool FCsSpawnerModifier_Toggle::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, Type)
	return true;
}

bool FCsSpawnerModifier_Toggle::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsSpawnerModifier, FECsSpawnerModifier, Type)
	return true;
}

const FName NCsSpawner::NModifier::FToggle::Name = FName("NCsSpawner::NModifier::FToggle");

namespace NCsSpawner
{
	namespace NModifier
	{
		namespace NToggle
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NModifier::FToggle, Copy);
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
			typedef NCsSpawner::NModifier::IModifier SpawnerModifierType;
			typedef NCsSpawner::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
			InterfaceMap->Add<ToggleModifierType>(static_cast<ToggleModifierType*>(this));
			InterfaceMap->Add<SpawnerModifierType>(static_cast<SpawnerModifierType*>(this));
			InterfaceMap->Add<ICsGetSpawnerModifierType>(static_cast<ICsGetSpawnerModifierType*>(this));
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
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, GetType())
			return true;
		}

		bool FToggle::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsSpawnerModifier, FECsSpawnerModifier, GetType())
			return true;
		}

		#pragma endregion ICsIsValid

		// CopyType (NCsSpawner::NModifier::NCopy::ICopy)
		#pragma region

		#define SpawnerModifierType NCsSpawner::NModifier::IModifier
		void FToggle::Copy(const SpawnerModifierType* From)
		{
		#undef SpawnerModifierType

			using namespace NCsSpawner::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			typedef NCsSpawner::NModifier::FLibrary SpawnerModifierLibrary;

			const FToggle* FromImpl = SpawnerModifierLibrary::PureStaticCastChecked<FToggle>(Context, From);

			SetType(FromImpl->GetType());
			SetbEnable(FromImpl->GetbEnable());
		}

		#pragma endregion CopyType (NCsSpawner::NModifier::NCopy::ICopy)
	}
}

#pragma endregion FCsSpawnerModifier_Toggle

// FCsSpawnerModifierInfo
#pragma region

#define InfoType NCsSpawner::NModifier::FInfo

void FCsSpawnerModifierInfo::CopyToInfo(InfoType* Info)
{
	// Ints
	typedef NCsSpawner::NModifier::FInt IntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (FCsSpawnerModifier_Int& From : Ints)
	{
		IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	// Floats
	typedef NCsSpawner::NModifier::FFloat FloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (FCsSpawnerModifier_Float& From : Floats)
	{
		FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	// Toggles
	typedef NCsSpawner::NModifier::FToggle ToggleModifierType;

	Info->Toggles.Reset(Toggles.Num());

	for (FCsSpawnerModifier_Toggle& From : Toggles)
	{
		ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	Info->PopulateModifiers();
}

void FCsSpawnerModifierInfo::CopyToInfoAsValue(InfoType* Info)
{
	// Ints
	typedef NCsSpawner::NModifier::FInt IntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (const FCsSpawnerModifier_Int& From : Ints)
	{
		IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	// Floats
	typedef NCsSpawner::NModifier::FFloat FloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (const FCsSpawnerModifier_Float& From : Floats)
	{
		FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	// Toggles
	typedef NCsSpawner::NModifier::FToggle ToggleModifierType;

	Info->Toggles.Reset(Toggles.Num());

	for (const FCsSpawnerModifier_Toggle& From : Toggles)
	{
		ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	Info->PopulateModifiers();
}

#undef InfoType

bool FCsSpawnerModifierInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	for (const FCsSpawnerModifier_Int& Modifier : Ints)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsSpawnerModifier_Float& Modifier : Floats)
	{
		CS_IS_VALID(Modifier)
	}
	for (const FCsSpawnerModifier_Toggle& Modifier : Toggles)
	{
		CS_IS_VALID(Modifier)
	}
	return true;
}

namespace NCsSpawner
{
	namespace NModifier
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			typedef NCsSpawner::NModifier::FInt IntModifierType;

			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsSpawner::NModifier::FFloat FloatModifierType;

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsSpawner::NModifier::FToggle ToggleModifierType;

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsSpawner::NModifier::IModifier ModifierType;

			const int32 Total = Ints.Num() + Floats.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE_CHECKED(Modifiers, ModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			typedef NCsSpawner::NModifier::FInt IntModifierType;

			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsSpawner::NModifier::FFloat FloatModifierType;

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsSpawner::NModifier::FToggle ToggleModifierType;

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsSpawner::NModifier::IModifier ModifierType;

			const int32 Total = Ints.Num() + Floats.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE(Modifiers, ModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL(Modifiers, ModifierType)
			return true;
		}
	}
}

#pragma endregion FCsSpawnerModifierInfo