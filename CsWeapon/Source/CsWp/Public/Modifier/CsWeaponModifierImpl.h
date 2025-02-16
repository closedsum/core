// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "CsMacro_Cached.h"
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

struct FCsWeaponModifier_Int;

// ModifierType (NCsWeapon::NModifier::NInt::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NModifier, NInt, FInt)

namespace NCsWeaponModifier_Int
{
	using ThisType = FCsWeaponModifier_Int;
	using ModifierType = NCsWeapon::NModifier::NInt::FInt;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsWeapon::NModifier::NInt::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NModifier, NInt, FInt)

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

	using ModifierType = NCsWeapon::NModifier::NInt::FInt;
	using _Impl = NCsWeaponModifier_Int::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NInt, Int)

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NInt
		{
			using CopyType = NCsWeapon::NModifier::NCopy::ICopy;

			struct CSWP_API FInt : public CsModifierType,
								   public CsIntModifierType,
								   public CsWeaponModifierType,
								   public ICsGetWeaponModifierType,
								   public ICsIsValid,
								   public CopyType,
								   public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NInt, Int);

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

			// CsIntModifierType (NCsModifier::NInt::IInt)
			#pragma region
			public:

				FORCEINLINE int32 Modify(const int32& InValue) const
				{
					return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
				}

			#pragma endregion CsIntModifierType (NCsModifier::NInt::IInt)

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

				void Copy(const CsWeaponModifierType* From);

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
			};
		}
	}
}

#pragma endregion FCsWeaponModifier_Int

// FCsWeaponModifier_Float
#pragma region

struct FCsWeaponModifier_Float;

// ModifierType (NCsWeapon::NModifier::NFloat::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NModifier, NFloat, FFloat)

namespace NCsWeaponModifier_Float
{
	using ThisType = FCsWeaponModifier_Float;
	using ModifierType = NCsWeapon::NModifier::NFloat::FFloat;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsWeapon::NModifier::NFloat::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NModifier, NFloat, FFloat)

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

	using ModifierType = NCsWeapon::NModifier::NFloat::FFloat;
	using _Impl = NCsWeaponModifier_Float::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NFloat, Float)

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NFloat
		{
			using CopyType = NCsWeapon::NModifier::NCopy::ICopy;

			struct CSWP_API FFloat : public CsModifierType,
									 public CsFloatModifierType,
									 public CsWeaponModifierType,
									 public ICsGetWeaponModifierType,
									 public ICsIsValid,
									 public CopyType,
									 public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NFloat, Float);

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

			// CsFloatModifierType (NCsModifier::NFloat::IFloat)
			#pragma region
			public:

				FORCEINLINE float Modify(const float& InValue) const
				{
					return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

			#pragma endregion CsFloatModifierType (NCsModifier::NFloat::IFloat)

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

				void Copy(const CsWeaponModifierType* From);

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
			};
		}
	}
}

#pragma endregion FCsWeaponModifier_Float

// FCsWeaponModifier_Toggle
#pragma region

struct FCsWeaponModifier_Toggle;

// ModifierType (NCsWeapon::NModifier::NToggle::FToggle)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NModifier, NToggle, FToggle)

namespace NCsWeaponModifier_Toggle
{
	using ThisType = FCsWeaponModifier_Toggle;
	using ModifierType = NCsWeapon::NModifier::NToggle::FToggle;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsWeapon::NModifier::NToggle::FToggle)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NModifier, NToggle, FToggle)

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

	using ModifierType = NCsWeapon::NModifier::NToggle::FToggle;
	using _Impl = NCsWeaponModifier_Toggle::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NToggle, Toggle)

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NToggle
		{
			using CopyType = NCsWeapon::NModifier::NCopy::ICopy;

			struct CSWP_API FToggle : public CsModifierType,
									  public CsToggleModifierType,
									  public CsWeaponModifierType,
									  public ICsGetWeaponModifierType,
									  public ICsIsValid,
									  public CopyType,
									  public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsWeapon, NModifier, NToggle, Toggle);

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

			// CsToggleModifierType (NCsModifier::NToggle::IToggle)
			#pragma region
			public:

				FORCEINLINE bool IsEnabled() const { return GetbEnable(); }

			#pragma endregion CsToggleModifierType (NCsModifier::NToggle::IToggle)

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

				void Copy(const CsWeaponModifierType* From);

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
			};
		}
	}
}

#pragma endregion FCsWeaponModifier_Toggle

// FCsWeaponModifierInfo
#pragma region

struct FCsWeaponModifierInfo;

// InfoType (NCsWeapon::NModifier::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, FInfo)

namespace NCsWeaponModifierInfo
{
	using ThisType = FCsWeaponModifierInfo;
	using InfoType = NCsWeapon::NModifier::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

// InfoType (NCsWeapon::NModifier::FInfo)
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

	using InfoType = NCsWeapon::NModifier::FInfo;
	using _Impl = NCsWeaponModifierInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)				 { _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info) const { _Impl::CopyToInfoAsValue(this, Info); }

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NModifier
	{
		struct CSWP_API FInfo
		{
		private:

			using IntModifierType = NCsWeapon::NModifier::NInt::FInt;
			using FloatModifierType = NCsWeapon::NModifier::NFloat::FFloat;
			using ToggleModifierType = NCsWeapon::NModifier::NToggle::FToggle;
			using ModifierType = NCsWeapon::NModifier::IModifier;

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
		};
	}
}

#pragma endregion FCsWeaponModifierInfo