// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsProjectileModifierImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsProjectileModifierImpl)

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

// FCsProjectileModifierInfo
#pragma region

#define InfoType NCsProjectile::NModifier::FInfo

void FCsProjectileModifierInfo::CopyToInfo(InfoType* Info)
{
	// Ints
	typedef NCsProjectile::NModifier::FInt IntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (FCsProjectileModifier_Int& From : Ints)
	{
		IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	// Floats
	typedef NCsProjectile::NModifier::FFloat FloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (FCsProjectileModifier_Float& From : Floats)
	{
		FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	// Toggles
	typedef NCsProjectile::NModifier::FToggle ToggleModifierType;

	Info->Toggles.Reset(Toggles.Num());

	for (FCsProjectileModifier_Toggle& From : Toggles)
	{
		ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
		From.CopyToModifier(&To);
	}
	Info->PopulateModifiers();
}

void FCsProjectileModifierInfo::CopyToInfoAsValue(InfoType* Info) const
{
	// Ints
	typedef NCsProjectile::NModifier::FInt IntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (const FCsProjectileModifier_Int& From : Ints)
	{
		IntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	// Floats
	typedef NCsProjectile::NModifier::FFloat FloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (const FCsProjectileModifier_Float& From : Floats)
	{
		FloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	// Toggles
	typedef NCsProjectile::NModifier::FToggle ToggleModifierType;

	Info->Toggles.Reset(Toggles.Num());

	for (const FCsProjectileModifier_Toggle& From : Toggles)
	{
		ToggleModifierType& To = Info->Toggles.AddDefaulted_GetRef();
		From.CopyToModifierAsValue(&To);
	}
	Info->PopulateModifiers();
}

#undef InfoType

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
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			typedef NCsProjectile::NModifier::FInt IntModifierType;

			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsProjectile::NModifier::FFloat FloatModifierType;

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsProjectile::NModifier::FToggle ToggleModifierType;

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID_CHECKED(Modifier);
			}

			typedef NCsProjectile::NModifier::IModifier ModifierType;

			const int32 Total = Ints.Num() + Floats.Num() + Toggles.Num();

			CS_IS_TARRAY_SIZE_CHECKED(Modifiers, ModifierType*, Total)
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
		{
			typedef NCsProjectile::NModifier::FInt IntModifierType;

			for (const IntModifierType& Modifier : Ints)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsProjectile::NModifier::FFloat FloatModifierType;

			for (const FloatModifierType& Modifier : Floats)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsProjectile::NModifier::FToggle ToggleModifierType;

			for (const ToggleModifierType& Modifier : Toggles)
			{
				CS_IS_VALID(Modifier)
			}

			typedef NCsProjectile::NModifier::IModifier ModifierType;

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

#define CreateModifierType NCsProjectile::NModifier::NCreate::FInt

void FCsProjectileModifier_Create_Int::CopyToCreateModifier(CreateModifierType* CreateModifier)
{
	typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

	CreateModifier->SetType((CreateType*)(&Type));
	CreateModifier->SetValue(&Value);
	Modifier.CopyToModifier(CreateModifier->GetModifierPtr());
}

void FCsProjectileModifier_Create_Int::CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const
{
	typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

	CreateModifier->SetType((CreateType)Type);
	CreateModifier->SetValue(Value);
	Modifier.CopyToModifierAsValue(CreateModifier->GetModifierPtr());
}

#undef CreateModifierType

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
			#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
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

			bool FInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
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

#pragma endregion FCsProjectileModifier_Create_Int

// FCsProjectileModifier_Create_Float
#pragma region

#define CreateModifierType NCsProjectile::NModifier::NCreate::FFloat

void FCsProjectileModifier_Create_Float::CopyToCreateModifier(CreateModifierType* CreateModifier)
{
	typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

	CreateModifier->SetType((CreateType*)(&Type));
	CreateModifier->SetValue(&Value);
	Modifier.CopyToModifier(CreateModifier->GetModifierPtr());
}

void FCsProjectileModifier_Create_Float::CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const
{
	typedef NCsModifier::NValue::NNumeric::ECreate CreateType;

	CreateModifier->SetType((CreateType)Type);
	CreateModifier->SetValue(Value);
	Modifier.CopyToModifierAsValue(CreateModifier->GetModifierPtr());
}

#undef CreateModifierType

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
			#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
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

			bool FFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
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

#pragma endregion FCsProjectileModifier_Create_Float

// FCsProjectileModifier_CreateInfo
#pragma region

#define InfoType NCsProjectile::NModifier::NCreate::FInfo

void FCsProjectileModifier_CreateInfo::CopyToInfo(InfoType* Info)
{
	// Int
	typedef NCsProjectile::NModifier::NCreate::FInt CreateIntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (FCsProjectileModifier_Create_Int& From : Ints)
	{
		CreateIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToCreateModifier(&To);
	}
	// Float
	typedef NCsProjectile::NModifier::NCreate::FFloat CreateFloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (FCsProjectileModifier_Create_Float& From : Floats)
	{
		CreateFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToCreateModifier(&To);
	}
}

void FCsProjectileModifier_CreateInfo::CopyToInfoAsValue(InfoType* Info) const
{
	// Int
	typedef NCsProjectile::NModifier::NCreate::FInt CreateIntModifierType;

	Info->Ints.Reset(Ints.Num());

	for (const FCsProjectileModifier_Create_Int& From : Ints)
	{
		CreateIntModifierType& To = Info->Ints.AddDefaulted_GetRef();
		From.CopyToCreateModifierAsValue(&To);
	}
	// Float
	typedef NCsProjectile::NModifier::NCreate::FFloat CreateFloatModifierType;

	Info->Floats.Reset(Floats.Num());

	for (const FCsProjectileModifier_Create_Float& From : Floats)
	{
		CreateFloatModifierType& To = Info->Floats.AddDefaulted_GetRef();
		From.CopyToCreateModifierAsValue(&To);
	}
}

#undef InfoType

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
			#define AllocatedModifierType NCsProjectile::NModifier::FAllocated

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

					typedef NCsProjectile::NModifier::NCreate::FInt CreateIntModifierType;

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

					typedef NCsProjectile::NModifier::NCreate::FFloat CreateFloatModifierType;

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
				typedef NCsProjectile::NModifier::NCreate::FInt CreateIntModifierType;

				for (const CreateIntModifierType& CreateModifier : Ints)
				{
					CS_IS_VALID_CHECKED(CreateModifier);
				}
				// Float
				typedef NCsProjectile::NModifier::NCreate::FFloat CreateFloatModifierType;

				for (const CreateFloatModifierType& CreateModifier : Floats)
				{
					CS_IS_VALID_CHECKED(CreateModifier);
				}
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				// Int
				typedef NCsProjectile::NModifier::NCreate::FInt CreateIntModifierType;

				for (const CreateIntModifierType& CreateModifier : Ints)
				{
					CS_IS_VALID(CreateModifier)
				}
				// Float
				typedef NCsProjectile::NModifier::NCreate::FFloat CreateFloatModifierType;

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