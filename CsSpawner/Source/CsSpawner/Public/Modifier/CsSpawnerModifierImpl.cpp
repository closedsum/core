// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Modifier/CsSpawnerModifierImpl.h"

// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Interface.h"
// Library
#include "Modifier/CsLibrary_SpawnerModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSpawnerModifierImpl)

// FCsSpawnerModifier_Int
#pragma region

void FCsSpawnerModifier_Int::CopyToModifier(CsSpawnerIntModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
}

void FCsSpawnerModifier_Int::CopyToModifierAsValue(CsSpawnerIntModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
}

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

			typedef NCsSpawner::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<CsModifierType>(static_cast<CsModifierType*>(this));
			InterfaceMap->Add<CsIntModifierType>(static_cast<CsIntModifierType*>(this));
			InterfaceMap->Add<CsSpawnerModifierType>(static_cast<CsSpawnerModifierType*>(this));
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

		void FInt::Copy(const CsSpawnerModifierType* From)
		{
			using namespace NCsSpawner::NModifier::NInt::NCached;

			const FString& Context = Str::Copy;

			const FInt* FromImpl = CsSpawnerModifierLibrary::PureStaticCastChecked<FInt>(Context, From);

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

void FCsSpawnerModifier_Float::CopyToModifier(CsSpawnerFloatModifierType* Modifier)
{
	Modifier->SetType(&Type);
	Modifier->SetValue(&Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType*)(&Application));
}

void FCsSpawnerModifier_Float::CopyToModifierAsValue(CsSpawnerFloatModifierType* Modifier) const
{
	Modifier->SetType(Type);
	Modifier->SetValue(Value);

	typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

	Modifier->SetApplication((ApplicationType)Application);
}

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

			typedef NCsSpawner::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<CsModifierType>(static_cast<CsModifierType*>(this));
			InterfaceMap->Add<CsFloatModifierType>(static_cast<CsFloatModifierType*>(this));
			InterfaceMap->Add<CsSpawnerModifierType>(static_cast<CsSpawnerModifierType*>(this));
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

		void FFloat::Copy(const CsSpawnerModifierType* From)
		{
			using namespace NCsSpawner::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			const FFloat* FromImpl = CsSpawnerModifierLibrary::PureStaticCastChecked<FFloat>(Context, From);

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

			typedef NCsSpawner::NModifier::NCopy::ICopy CopyType;

			InterfaceMap->Add<CsModifierType>(static_cast<CsModifierType*>(this));
			InterfaceMap->Add<CsToggleModifierType>(static_cast<CsToggleModifierType*>(this));
			InterfaceMap->Add<CsSpawnerModifierType>(static_cast<CsSpawnerModifierType*>(this));
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

		void FToggle::Copy(const CsSpawnerModifierType* From)
		{
			using namespace NCsSpawner::NModifier::NFloat::NCached;

			const FString& Context = Str::Copy;

			const FToggle* FromImpl = CsSpawnerModifierLibrary::PureStaticCastChecked<FToggle>(Context, From);

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
	Info->Ints.Reset(Ints.Num());

	for (FCsSpawnerModifier_Int& From : Ints)
	{
		CsSpawnerIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	// Floats
	Info->Floats.Reset(Floats.Num());

	for (FCsSpawnerModifier_Float& From : Floats)
	{
		CsSpawnerFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
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
	Info->Ints.Reset(Ints.Num());

	for (const FCsSpawnerModifier_Int& From : Ints)
	{
		CsSpawnerIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	// Floats
	Info->Floats.Reset(Floats.Num());

	for (const FCsSpawnerModifier_Float& From : Floats)
	{
		CsSpawnerFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
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
			for (const CsSpawnerIntModifierType& Modifier : Ints)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			for (const CsSpawnerFloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsSpawner::NModifier::FToggle ToggleModifierType;

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			const int32 Total = Ints.Num() + Floats.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE_CHECKED(Modifiers, CsSpawnerModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsSpawnerModifierType)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			for (const CsSpawnerIntModifierType& Modifier : Ints)
			{
				CS_IS_VALID(Modifier)
			}

			for (const CsSpawnerFloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsSpawner::NModifier::FToggle ToggleModifierType;

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID(Modifier)
			}

			const int32 Total = Ints.Num() + Floats.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE(Modifiers, CsSpawnerModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL(Modifiers, CsSpawnerModifierType)
			return true;
		}
	}
}

#pragma endregion FCsSpawnerModifierInfo