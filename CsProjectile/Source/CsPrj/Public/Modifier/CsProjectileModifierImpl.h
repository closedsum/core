// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Modifier/CsTypes_Modifier.h"
#include "Modifier/Types/CsTypes_ProjectileModifier.h"
// Interface
#include "Modifier/CsModifier.h"
#include "Modifier/CsModifier_Int.h"
#include "Modifier/CsModifier_Float.h"
#include "Modifier/CsModifier_Toggle.h"
#include "Modifier/CsProjectileModifier.h"
#include "Modifier/Types/CsGetProjectileModifierType.h"
#include "Valid/CsIsValid.h"
#include "Modifier/Copy/CsProjectileModifier_Copy.h"
#include "Reset/CsReset.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsProjectileModifierImpl.generated.h"

// FCsProjectileModifier_Int
#pragma region

// NCsProjectile::NModifier::FInt
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FInt)

/**
* Describes how to modify any int properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsProjectileModifier Type;

	/** The value to apply to the Int property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0", ClampMin = "0"))
	int32 Value;

	/** How Value is applied to the existing Int property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsNumericValueModifierApplication Application;

	FCsProjectileModifier_Int() :
		Type(),
		Value(0),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsProjectile::NModifier::FInt
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define IntModifierType NCsModifier::NInt::IInt
	#define PrjModifierType NCsProjectile::NModifier::IModifier
	#define CopyType NCsProjectile::NModifier::NCopy::ICopy

		/**
		* Describes how to modify any int properties on a Projectile.
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		struct CSPRJ_API FInt : public ModifierType,
								public IntModifierType,
								public PrjModifierType,
								public ICsGetProjectileModifierType,
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

		// IntModifierType (NCsModifier::NInt::IInt)
		#pragma region
		public:

			FORCEINLINE int32 Modify(const int32& InValue) const
			{
				return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
			}

		#pragma endregion IntModifierType (NCsModifier::NInt::IInt)

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

		#undef ApplicationType
		};

	#undef ModifierType
	#undef IntModifierType
	#undef PrjModifierType
	#undef CopyType
	}
}

#pragma endregion FCsProjectileModifier_Int

// FCsProjectileModifier_Float
#pragma region

// NCsProjectile::NModifier::FFloat
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FFloat)

/**
* Describes how to modify any float properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsProjectileModifier Type;

	/** The value to apply to the Float property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing Float property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsNumericValueModifierApplication Application;

	FCsProjectileModifier_Float() :
		Type(),
		Value(0.0f),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsProjectile::NModifier::FFloat
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define FloatModifierType NCsModifier::NFloat::IFloat
	#define PrjModifierType NCsProjectile::NModifier::IModifier
	#define CopyType NCsProjectile::NModifier::NCopy::ICopy

		/**
		* Describes how to modify any float properties on a Projectile.
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		struct CSPRJ_API FFloat : public ModifierType,
								  public FloatModifierType,
								  public PrjModifierType,
								  public ICsGetProjectileModifierType,
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

		// FloatModifierType (NCsModifier::NFloat::IFloat)
		#pragma region
		public:

			FORCEINLINE float Modify(const float& InValue) const
			{
				return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
			}

		#pragma endregion FloatModifierType (NCsModifier::NFloat::IFloat)

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
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef FloatModifierType
	#undef PrjModifierType
	#undef CopyType
	}
}

#pragma endregion FCsProjectileModifier_Float

// FCsProjectileModifier_Toggle
#pragma region

// NCsProjectile::NModifier::FToggle
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FToggle)

/**
* Describes whether to toggle any properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Toggle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsProjectileModifier Type;

	/** Whether the property associated with Type is enabled or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	bool bEnable;

	FCsProjectileModifier_Toggle() :
		Type(),
		bEnable(false)
	{
	}

#define ModifierType NCsProjectile::NModifier::FToggle
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define ToggleModifierType NCsModifier::NToggle::IToggle
	#define PrjModifierType NCsProjectile::NModifier::IModifier
	#define CopyType NCsProjectile::NModifier::NCopy::ICopy

		/**
		* Describes whether to toggle any properties on a Projectile.
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		struct CSPRJ_API FToggle : public ModifierType,
								   public ToggleModifierType,
								   public PrjModifierType,
								   public ICsGetProjectileModifierType,
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

		// ToggleModifierType (NCsModifier::NToggle::IToggle)
		#pragma region
		public:

			FORCEINLINE bool IsEnabled() const { return GetbEnable(); }

		#pragma endregion ToggleModifierType (NCsModifier::NToggle::IToggle)

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

		#undef ApplicationType
		};

	#undef ModifierType
	#undef ToggleModifierType
	#undef PrjModifierType
	#undef CopyType
	}
}

#pragma endregion FCsWeaponModifier_Toggle

// FCsProjectileModifierInfo
#pragma region

// NCsProjectile::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifierInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Int> IntModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Float> FloatModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Toggle> ToggleModifiers;

	FCsProjectileModifierInfo() :
		IntModifiers(),
		FloatModifiers(),
		ToggleModifiers()
	{
	}

#define ModifierType NCsProjectile::NModifier::IModifier
	void ConstructModifiers(TArray<ModifierType*>& OutModifiers);
#undef ModifierType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsProjectileModifierInfo

// FCsProjectileModifier_Create_Int
#pragma region

// NCsProjectile::NModifier::NCreate::FInt
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

#define CreateModifierType NCsProjectile::NModifier::NCreate::FInt
	void CopyToCreateModifier(CreateModifierType* CreateModifier);
	void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const;
#undef CreateModifierType

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
			#define CreateType NCsModifier::NValue::NNumeric::ECreate
			#define ModifierType NCsProjectile::NModifier::FInt

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

			#define PrjModifierType NCsProjectile::NModifier::IModifier
				PrjModifierType* CreateChecked(const FString& Context, const UObject* WorldContext, const int32& InValue);
			#undef PrjModifierType

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef CreateType
			#undef ModifierType
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_Int