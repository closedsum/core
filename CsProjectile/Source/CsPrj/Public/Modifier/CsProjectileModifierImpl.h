// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "CsMacro_Cached.h"
#include "CsTypes_Modifier.h"
#include "Modifier/Types/CsTypes_ProjectileModifier.h"
// Interface
#include "ICsModifier.h"
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
#include "CsModifier_Toggle.h"
#include "Modifier/CsProjectileModifier.h"
#include "Modifier/Types/CsGetProjectileModifierType.h"
#include "Valid/CsIsValid.h"
#include "Modifier/Copy/CsProjectileModifier_Copy.h"
#include "Reset/CsReset.h"
// Projectile
#include "Modifier/CsAllocated_ProjectileModifier.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsProjectileModifierImpl.generated.h"

// FCsProjectileModifier_Int
#pragma region

struct FCsProjectileModifier_Int;

// ModifierType (NCsProjectile::NModifier::NInt::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NInt, FInt)

namespace NCsProjectileModifier_Int
{
	using ThisType = FCsProjectileModifier_Int;
	using ModifierType = NCsProjectile::NModifier::NInt::FInt;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// NCsProjectile::NModifier::NInt::FInt
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NInt, FInt)

/**
* Describes how to modify any int properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	FECsProjectileModifier Type;

	/** The value to apply to the Int property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier", meta = (UIMin = "0", ClampMin = "0"))
	int32 Value;

	/** How Value is applied to the existing Int property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	ECsNumericValueModifierApplication Application;

	FCsProjectileModifier_Int() :
		Type(),
		Value(0),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

	using ModifierType = NCsProjectile::NModifier::NInt::FInt;
	using _Impl = NCsProjectileModifier_Int::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NInt, Int)

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NInt
		{
			using PrjModifierType = NCsProjectile::NModifier::IModifier;
			using CopyType = NCsProjectile::NModifier::NCopy::ICopy;

			/**
			* Describes how to modify any int properties on a Projectile.
			*  Projectile is an object that implements the interface: ICsProjectile.
			*/
			struct CSPRJ_API FInt : public CsModifierType,
									public CsIntModifierType,
									public PrjModifierType,
									public ICsGetProjectileModifierType,
									public ICsIsValid,
									public CopyType,
									public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NInt, Int);

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
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

			// ICsGetProjectileModifierType
			#pragma region
			public:

				FORCEINLINE const FECsProjectileModifier& GetProjectileModifierType() const { return GetType(); }

			#pragma endregion ICsGetProjectileModifierType

			// ICsIsValid
			#pragma region
			public:

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#pragma endregion ICsIsValid

			// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
			#pragma region
			public:

				void Copy(const PrjModifierType* From);

			#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				FORCEINLINE void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Type, EMCsProjectileModifier::Get().GetMAX())
					CS_RESET_MEMBER_WITH_PROXY(Value, 0)
					CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
				}

			#pragma endregion ICsReset

			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_Int

// FCsProjectileModifier_Float
#pragma region

struct FCsProjectileModifier_Float;

// ModifierType (NCsProjectile::NModifier::NFloat::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NFloat, FFloat)

namespace NCsProjectileModifier_Float
{
	using ThisType = FCsProjectileModifier_Float;
	using ModifierType = NCsProjectile::NModifier::NFloat::FFloat;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsProjectile::NModifier::NFloat::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NFloat, FFloat)

/**
* Describes how to modify any float properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	FECsProjectileModifier Type;

	/** The value to apply to the Float property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing Float property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	ECsNumericValueModifierApplication Application;

	FCsProjectileModifier_Float() :
		Type(),
		Value(0.0f),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

	using ModifierType = NCsProjectile::NModifier::NFloat::FFloat;
	using _Impl = NCsProjectileModifier_Float::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NFloat, Float)

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NFloat
		{
			using PrjModifierType = NCsProjectile::NModifier::IModifier;
			using CopyType = NCsProjectile::NModifier::NCopy::ICopy;

			/**
			* Describes how to modify any float properties on a Projectile.
			*  Projectile is an object that implements the interface: ICsProjectile.
			*/
			struct CSPRJ_API FFloat : public CsModifierType,
									  public CsFloatModifierType,
									  public PrjModifierType,
									  public ICsGetProjectileModifierType,
									  public ICsIsValid,
									  public CopyType,
									  public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NFloat, Float);

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
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

			// ICsGetProjectileModifierType
			#pragma region
			public:

				FORCEINLINE const FECsProjectileModifier& GetProjectileModifierType() const { return GetType(); }

			#pragma endregion ICsGetProjectileModifierType

			// ICsIsValid
			#pragma region
			public:

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#pragma endregion ICsIsValid

			// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
			#pragma region
			public:

				void Copy(const PrjModifierType* From);

			#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				FORCEINLINE void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Type, EMCsProjectileModifier::Get().GetMAX())
					CS_RESET_MEMBER_WITH_PROXY(Value, 0.0)
					CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
				}

			#pragma endregion ICsREset

			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_Float

// FCsProjectileModifier_Toggle
#pragma region

struct FCsProjectileModifier_Toggle;

// ModifierType (NCsProjectile::NModifier::NToggel::FToggle)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NToggle, FToggle)

namespace NCsProjectileModifier_Toggle
{
	using ThisType = FCsProjectileModifier_Toggle;
	using ModifierType = NCsProjectile::NModifier::NToggle::FToggle;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsProjectile::NModifier::NToggel::FToggle)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NToggle, FToggle)

/**
* Describes whether to toggle any properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Toggle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	FECsProjectileModifier Type;

	/** Whether the property associated with Type is enabled or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	bool bEnable;

	FCsProjectileModifier_Toggle() :
		Type(),
		bEnable(false)
	{
	}

	using ModifierType = NCsProjectile::NModifier::NToggle::FToggle;
	using _Impl = NCsProjectileModifier_Toggle::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NToggle, Toggle)

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NToggle
		{
			using PrjModifierType = NCsProjectile::NModifier::IModifier;
			using CopyType = NCsProjectile::NModifier::NCopy::ICopy;

			/**
			* Describes whether to toggle any properties on a Projectile.
			*  Projectile is an object that implements the interface: ICsProjectile.
			*/
			struct CSPRJ_API FToggle : public CsModifierType,
									   public CsToggleModifierType,
									   public PrjModifierType,
									   public ICsGetProjectileModifierType,
									   public ICsIsValid,
									   public CopyType,
									   public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NModifier, NToggle, Toggle);

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
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

			// ICsGetProjectileModifierType
			#pragma region
			public:

				FORCEINLINE const FECsProjectileModifier& GetProjectileModifierType() const { return GetType(); }

			#pragma endregion ICsGetProjectileModifierType

			// ICsIsValid
			#pragma region
			public:

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#pragma endregion ICsIsValid

			// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
			#pragma region
			public:

				void Copy(const PrjModifierType* From);

			#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				FORCEINLINE void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Type, EMCsProjectileModifier::Get().GetMAX())
					CS_RESET_MEMBER_WITH_PROXY(bEnable, false)
				}

			#pragma endregion ICsREset

			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bEnable, bool)
			};
		}
	}
}

#pragma endregion FCsWeaponModifier_Toggle

// FCsProjectileModifierInfo
#pragma region

struct FCsProjectileModifierInfo;

// InfoType (NCsProjectile::NModifier::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FInfo)

namespace NCsProjectileModifierInfo
{
	using ThisType = FCsProjectileModifierInfo;
	using InfoType = NCsProjectile::NModifier::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

// InfoType (NCsProjectile::NModifier::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FInfo)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifierInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Float> Floats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Toggle> Toggles;

	FCsProjectileModifierInfo() :
		Ints(),
		Floats(),
		Toggles()
	{
	}

	using InfoType = NCsProjectile::NModifier::FInfo;
	using _Impl = NCsProjectileModifierInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)					{ _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info) const	{ _Impl::CopyToInfoAsValue(this, Info); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NModifier
	{
		struct CSPRJ_API FInfo
		{
		private:

			using IntModifierType = NCsProjectile::NModifier::NInt::FInt;
			using FloatModifierType = NCsProjectile::NModifier::NFloat::FFloat;
			using ToggleModifierType = NCsProjectile::NModifier::NToggle::FToggle;
			using ModifierType = NCsProjectile::NModifier::IModifier;

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

			FORCEINLINE int32 GetTotalSize() const { return Ints.Num() + Floats.Num() + Toggles.Num(); }

			FORCEINLINE void PopulateModifiers()
			{
				Modifiers.Reset(GetTotalSize());

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
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsProjectileModifierInfo

// FCsProjectileModifier_Create_Int
#pragma region

struct FCsProjectileModifier_Create_Int;

// CreateModifierType (NCsProjectile::NModifier::NCreate::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FInt)

namespace NCsProjectileModifier_Create_Int
{
	using ThisType = FCsProjectileModifier_Create_Int;
	using CreateModifierType = NCsProjectile::NModifier::NCreate::FInt;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToCreateModifier(ThisType* This, CreateModifierType* CreateModifier);
		static void CopyToCreateModifierAsValue(const ThisType* This, CreateModifierType* CreateModifier);
	};
}

// CreateModifierType (NCsProjectile::NModifier::NCreate::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FInt)

/**
* Describes how to create a modifier for an int properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Create_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	ECsNumericValueCreateModifier Type;

	/** Used another value determined by Type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FCsProjectileModifier_Int Modifier;

	FCsProjectileModifier_Create_Int() :
		Type(),
		Value(0),
		Modifier()
	{
	}

	using CreateModifierType = NCsProjectile::NModifier::NCreate::FInt;
	using _Impl = NCsProjectileModifier_Create_Int::FImpl;

	FORCEINLINE void CopyToCreateModifier(CreateModifierType* CreateModifier)				{ _Impl::CopyToCreateModifier(this, CreateModifier); }
	FORCEINLINE void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const	{ _Impl::CopyToCreateModifierAsValue(this, CreateModifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSPRJ_API FInt
			{
			private:

				using CreateType = NCsModifier::NValue::NNumeric::ECreate;
				using ModifierType = NCsProjectile::NModifier::NInt::FInt;
				using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Type, CreateType)
				CS_DECLARE_MEMBER_WITH_PROXY(Value, int32)

			public:

				ModifierType Modifier;

				FInt() :
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0),
					Modifier()
				{
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, CreateType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)
				FORCEINLINE ModifierType* GetModifierPtr() { return &Modifier; }
	
				void CreateChecked(const FString& Context, const UObject* WorldContext, const int32& InValue, AllocatedModifierType& OutModifier);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_Int

// FCsProjectileModifier_Create_Float
#pragma region

struct FCsProjectileModifier_Create_Float;

// CreateModifierType (NCsProjectile::NModifier::NCreate::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FFloat)

namespace NCsProjectileModifier_Create_Float
{
	using ThisType = FCsProjectileModifier_Create_Float;
	using CreateModifierType = NCsProjectile::NModifier::NCreate::FFloat;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToCreateModifier(ThisType* This, CreateModifierType* CreateModifier);
		static void CopyToCreateModifierAsValue(const ThisType* This, CreateModifierType* CreateModifier);
	};
}

// CreateModifierType (NCsProjectile::NModifier::NCreate::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FFloat)

/**
* Describes how to create a modifier for an float properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Create_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	ECsNumericValueCreateModifier Type;

	/** Used another value determined by Type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FCsProjectileModifier_Float Modifier;

	FCsProjectileModifier_Create_Float() :
		Type(),
		Value(0.0f),
		Modifier()
	{
	}

	using CreateModifierType = NCsProjectile::NModifier::NCreate::FFloat;
	using _Impl = NCsProjectileModifier_Create_Float::FImpl;

	FORCEINLINE void CopyToCreateModifier(CreateModifierType* CreateModifier)				{ _Impl::CopyToCreateModifier(this, CreateModifier); }
	FORCEINLINE void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const	{ _Impl::CopyToCreateModifierAsValue(this, CreateModifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSPRJ_API FFloat
			{
			private:

				using CreateType = NCsModifier::NValue::NNumeric::ECreate;
				using ModifierType = NCsProjectile::NModifier::NFloat::FFloat;
				using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Type, CreateType)
				CS_DECLARE_MEMBER_WITH_PROXY(Value, float)

			public:

				ModifierType Modifier;

				FFloat() :
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
					Modifier()
				{
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, CreateType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)
				FORCEINLINE ModifierType* GetModifierPtr() { return &Modifier; }
			
				void CreateChecked(const FString& Context, const UObject* WorldContext, const float& InValue, AllocatedModifierType& OutModifier);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_Float

// FCsProjectileModifier_CreateInfo
#pragma region

struct FCsProjectileModifier_CreateInfo;

// InfoType (NCsProjectile::NModifier::NCreate::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FInfo)

namespace NCsProjectileModifier_CreateInfo
{
	using ThisType = FCsProjectileModifier_CreateInfo;
	using InfoType = NCsProjectile::NModifier::NCreate::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSPRJ_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

// InfoType (NCsProjectile::NModifier::NCreate::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FInfo)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_CreateInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Create_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Create_Float> Floats;

	FCsProjectileModifier_CreateInfo() :
		Ints(),
		Floats()
	{
	}

	using InfoType = NCsProjectile::NModifier::NCreate::FInfo;
	using _Impl = NCsProjectileModifier_CreateInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)					{ _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info) const	{ _Impl::CopyToInfoAsValue(this, Info); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSPRJ_API FInfo
			{
			private:

				using CreateIntModifierType = NCsProjectile::NModifier::NCreate::FInt;
				using CreateFloatModifierType = NCsProjectile::NModifier::NCreate::FFloat;
				using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;

			public:

				TArray<CreateIntModifierType> Ints;

				TArray<CreateFloatModifierType> Floats;

			public:

				FInfo() :
					Ints(),
					Floats()
				{
				}

				FORCEINLINE int32 GetTotalSize() const { return Ints.Num() + Floats.Num(); }
			
				void CreateChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers);
				void AddChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_CreateInfo