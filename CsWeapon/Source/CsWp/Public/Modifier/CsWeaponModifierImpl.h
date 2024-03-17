// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
#include "CsTypes_Modifier.h"
#include "Modifier/Types/CsTypes_WeaponModifier.h"
// Interface
#include "ICsModifier.h"
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
#include "CsModifier_Toggle.h"
#include "Modifier/CsWeaponModifier.h"
#include "Modifier/Types/CsGetWeaponModifierType.h"
#include "Valid/CsIsValid.h"
#include "Modifier/Copy/CsWeaponModifier_Copy.h"
#include "Reset/CsReset.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsWeaponModifierImpl.generated.h"

// FCsWeaponModifier_Int
#pragma region

// NCsWeapon::NModifier::FInt
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, FInt)

/**
* Describes how to modify any int properties on a Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponModifier_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Modifier")
	FECsWeaponModifier Type;

	/** The value to apply to the Int property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Modifier", meta = (UIMin = "0", ClampMin = "0"))
	int32 Value;

	/** How Value is applied to the existing Int property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Modifier")
	ECsNumericValueModifierApplication Application;

	FCsWeaponModifier_Int() :
		Type(),
		Value(0),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsWeapon::NModifier::FInt
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsWeapon
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define IntModifierType NCsModifier::NInt::IInt
	#define WeaponModifierType NCsWeapon::NModifier::IModifier
	#define CopyType NCsWeapon::NModifier::NCopy::ICopy

		struct CSWP_API FInt : public ModifierType,
								public IntModifierType,
								public WeaponModifierType,
								public ICsGetWeaponModifierType,
								public ICsIsValid,
								public CopyType,
								public ICsReset
		{
		public:

			static const FName Name;

		#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsWeaponModifier)
			CS_DECLARE_MEMBER_WITH_PROXY(Value, int32)
			CS_DECLARE_MEMBER_WITH_PROXY(Application, ApplicationType)

		public:

			FInt();
			~FInt();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// IntModifierType (NCsModifier::NInt::IInt)
		#pragma region
		public:

			FORCEINLINE int32 Modify(const int32& InValue) const
			{
				return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
			}

		#pragma endregion IntModifierType (NCsModifier::NInt::IInt)

		// ICsGetWeaponModifierType
		#pragma region
		public:

			FORCEINLINE const FECsWeaponModifier& GetWeaponModifierType() const { return GetType(); }

		#pragma endregion ICsGetWeaponModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const WeaponModifierType* From);

		#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsWeaponModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(Value, 0)
				CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
			}

		#pragma endregion ICsReset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsWeaponModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef IntModifierType
	#undef WeaponModifierType
	#undef CopyType
	}
}

#pragma endregion FCsWeaponModifier_Int

// FCsWeaponModifier_Float
#pragma region

// NCsWeapon::NModifier::FFloat
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, FFloat)

/**
* Describes how to modify any float properties on a Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponModifier_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Modifier")
	FECsWeaponModifier Type;

	/** The value to apply to the Float property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing Float property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Modifier")
	ECsNumericValueModifierApplication Application;

	FCsWeaponModifier_Float() :
		Type(),
		Value(0.0f),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsWeapon::NModifier::FFloat
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsWeapon
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define FloatModifierType NCsModifier::NFloat::IFloat
	#define WeaponModifierType NCsWeapon::NModifier::IModifier
	#define CopyType NCsWeapon::NModifier::NCopy::ICopy

		struct CSWP_API FFloat : public ModifierType,
								  public FloatModifierType,
								  public WeaponModifierType,
								  public ICsGetWeaponModifierType,
								  public ICsIsValid,
								  public CopyType,
								  public ICsReset
		{
		public:

			static const FName Name;

		#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsWeaponModifier)
			CS_DECLARE_MEMBER_WITH_PROXY(Value, float)
			CS_DECLARE_MEMBER_WITH_PROXY(Application, ApplicationType)

		public:

			FFloat();
			~FFloat();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// FloatModifierType (NCsModifier::NFloat::IFloat)
		#pragma region
		public:

			FORCEINLINE float Modify(const float& InValue) const
			{
				return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

		#pragma endregion FloatModifierType (NCsModifier::NFloat::IFloat)

		// ICsGetWeaponModifierType
		#pragma region
		public:

			FORCEINLINE const FECsWeaponModifier& GetWeaponModifierType() const { return GetType(); }

		#pragma endregion ICsGetWeaponModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const WeaponModifierType* From);

		#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsWeaponModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(Value, 0.0)
				CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsWeaponModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef FloatModifierType
	#undef WeaponModifierType
	#undef CopyType
	}
}

#pragma endregion FCsWeaponModifier_Float

// FCsWeaponModifier_Toggle
#pragma region

// NCsWeapon::NModifier::FToggle
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, FToggle)

/**
* Describes whether to toggle any properties on a Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponModifier_Toggle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Modifier")
	FECsWeaponModifier Type;

	/** Whether the property associated with Type is enabled or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	bool bEnable;

	FCsWeaponModifier_Toggle() :
		Type(),
		bEnable(false)
	{
	}

#define ModifierType NCsWeapon::NModifier::FToggle
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsWeapon
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define ToggleModifierType NCsModifier::NToggle::IToggle
	#define WeaponModifierType NCsWeapon::NModifier::IModifier
	#define CopyType NCsWeapon::NModifier::NCopy::ICopy

		struct CSWP_API FToggle : public ModifierType,
								  public ToggleModifierType,
								  public WeaponModifierType,
								  public ICsGetWeaponModifierType,
								  public ICsIsValid,
								  public CopyType,
								  public ICsReset
		{
		public:

			static const FName Name;

		#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsWeaponModifier)
			CS_DECLARE_MEMBER_WITH_PROXY(bEnable, bool)

		public:

			FToggle();
			~FToggle();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// ToggleModifierType (NCsModifier::NToggle::IToggle)
		#pragma region
		public:

			FORCEINLINE bool IsEnabled() const { return GetbEnable(); }

		#pragma endregion ToggleModifierType (NCsModifier::NToggle::IToggle)

		// ICsGetWeaponModifierType
		#pragma region
		public:

			FORCEINLINE const FECsWeaponModifier& GetWeaponModifierType() const { return GetType(); }

		#pragma endregion ICsGetWeaponModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsWeapon::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const WeaponModifierType* From);

		#pragma endregion CopyType (NCsWeapon::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsWeaponModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(bEnable, false)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsWeaponModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bEnable, bool)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef ToggleModifierType
	#undef WeaponModifierType
	#undef CopyType
	}
}

#pragma endregion FCsWeaponModifier_Toggle

// FCsWeaponModifierInfo
#pragma region

// NCsWeapon::NModifier::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, FInfo)

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponModifierInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Modifier")
	TArray<FCsWeaponModifier_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Modifier")
	TArray<FCsWeaponModifier_Float> Floats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Modifier")
	TArray<FCsWeaponModifier_Toggle> Toggles;

	FCsWeaponModifierInfo() :
		Ints(),
		Floats(),
		Toggles()
	{
	}

#define InfoType NCsWeapon::NModifier::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info);
#undef InfoType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NModifier
	{
		struct CSWP_API FInfo
		{
		#define IntModifierType NCsWeapon::NModifier::FInt
		#define FloatModifierType NCsWeapon::NModifier::FFloat
		#define ToggleModifierType NCsWeapon::NModifier::FToggle
		#define ModifierType NCsWeapon::NModifier::IModifier

		public:

			TArray<IntModifierType> Ints;

			TArray<FloatModifierType> Floats;

			TArray<ToggleModifierType> Toggles;

		private:

			TArray<ModifierType*> Modifiers;

		public:

			FInfo() :
				Ints(),
				Floats(),
				Toggles(),
				Modifiers()
			{
			}

			FORCEINLINE const TArray<ModifierType*>& GetModifiers() const { return Modifiers; }
			FORCEINLINE TArray<ModifierType*>* GetModifiersPtr() { return &Modifiers; }

			FORCEINLINE void PopulateModifiers()
			{
				Modifiers.Reset(Ints.Num() + Floats.Num() + Toggles.Num());

				for (IntModifierType& Modifier : Ints)
				{
					Modifiers.Add(&Modifier);
				}

				for (FloatModifierType& Modifier : Floats)
				{
					Modifiers.Add(&Modifier);
				}

				for (ToggleModifierType& Modifier : Toggles)
				{
					Modifiers.Add(&Modifier);
				}
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

		#undef IntModifierType
		#undef FloatModifierType
		#undef ToggleModifierType
		#undef ModifierType
		};
	}
}

#pragma endregion FCsWeaponModifierInfo