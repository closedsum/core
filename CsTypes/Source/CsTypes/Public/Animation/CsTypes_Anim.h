// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
#include "CsMacro_Misc.h"
#include "CsMacro_StructOps.h"
#include "Types/CsTypes_View.h"
#include "Animation/AnimEnums.h"
#include "Animation/AnimTypes.h"
// Log
#include "Utility/CsTypesLog.h"

#include "CsTypes_Anim.generated.h"

namespace NCsAnimCached
{
	namespace Str
	{
		extern CSTYPES_API const FString Empty;// = TEXT("");

		extern CSTYPES_API const FString AnimSequence;// = TEXT("AnimSequence");
		extern CSTYPES_API const FString Anim_Sequence;// = TEXT("Anim Sequence");
		extern CSTYPES_API const FString AnimMontage;// = TEXT("AnimMontage");
		extern CSTYPES_API const FString Anim_Montage;// = TEXT("Anim Montage");
		extern CSTYPES_API const FString BlendSpace1D;// = TEXT("BlendSpace1D");
		extern CSTYPES_API const FString Blend_Space_1D;// = TEXT("Blend Space 1D");
		extern CSTYPES_API const FString BlendSpace;// = TEXT("BlendSpace");
		extern CSTYPES_API const FString Blend_Space;// = TEXT("Blend Space");
		extern CSTYPES_API const FString AimOffsetBlendSpace;// = TEXT("AimOffsetBlendSpace");
		extern CSTYPES_API const FString Aim_Offset_Blend_Space;// = TEXT("Aim Offset Blend Space");
	}
}

// FpvAnimMember
#pragma region

UENUM(BlueprintType)
enum class ECsFpvAnimMember : uint8
{
	Anim1P					UMETA(DisplayName = "Anim1P"),
	Anim3P					UMETA(DisplayName = "Anim3P"),
	Anim3P_Low				UMETA(DisplayName = "Anim3P_Low"),
	AnimVR					UMETA(DisplayName = "AnimVR"),
	ECsFpvAnimMember_MAX	UMETA(Hidden),
};


struct CSTYPES_API EMCsFpvAnimMember: public TCsEnumMap<ECsFpvAnimMember>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFpvAnimMember, ECsFpvAnimMember)
};

namespace NCsFpvAnimMember
{
	typedef ECsFpvAnimMember Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Anim1P;
		extern CSTYPES_API const Type Anim3P;
		extern CSTYPES_API const Type Anim3P_Low;
		extern CSTYPES_API const Type AnimVR;
		extern CSTYPES_API const Type ECsFpvAnimMember_MAX;
	}

	extern CSTYPES_API const uint8 MAX;

	FORCEINLINE const FString& ToStringFromViewType(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimMember::Get().ToString(Ref::Anim3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimMember::Get().ToString(Ref::AnimVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#pragma endregion FpvAnimMember

// FCsAnimSequence
#pragma region

class UAnimSequence;

/**
*/
USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimSequence> Anim;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anim_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "CsCore|Anim")
	UAnimSequence* Anim_Internal;

public:

	FCsAnimSequence() :
		Anim(nullptr),
		Anim_LoadFlags(0),
		Anim_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UAnimSequence asset.
	*
	* return Anim Sequence
	*/
	FORCEINLINE UAnimSequence* Get() const { return Anim_Internal; }

	/**
	* Get the pointer to the Hard reference to the UAnimSequence asset.
	*
	* return Anim Sequence
	*/
	FORCEINLINE UAnimSequence** GetPtr() { return &Anim_Internal; }

	/**
	* Get the Hard reference to the UAnimSequence asset.
	*
	* @param Context	The calling context.
	* return			Anim Sequence
	*/
	FORCEINLINE UAnimSequence* GetChecked(const FString& Context) const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("%s: Anim's Path is NOT Valid."), *Context);
		checkf(Anim_Internal, TEXT("%s: Anim has NOT been loaded from Path @ %s."), *Context, *(Anim.ToSoftObjectPath().ToString()));

		return Anim_Internal;
	}

	/**
	* Get the Hard reference to the UAnimSequence asset.
	*
	* return			Anim Sequence
	*/
	FORCEINLINE UAnimSequence* GetChecked() const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("FCsAnimSequence::GetChecked: Anim Path's is NOT Valid."));
		checkf(Anim_Internal, TEXT("FCsAnimSequence::GetChecked: Failed to load Anim @ %s."), *(Anim.ToSoftObjectPath().ToString()));

		return Anim_Internal;
	}

	/**
	* Safely get the Hard reference to the UAnimSequence asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Anim Sequence
	*/
	UAnimSequence* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Anim.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim is NULL."), *Context));
			return nullptr;
		}

		if (!Anim_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim has NOT been loaded from Path @ %s."), *Context, *(Anim.ToSoftObjectPath().ToString())));
		}
		return Anim_Internal;
	}

	/**
	* Safely get the Hard reference to the UAnimSequence asset.
	*
	* return Anim Sequence
	*/
	UAnimSequence* GetSafe()
	{
		if (!Anim.ToSoftObjectPath().IsValid())
			return nullptr;
		return Anim_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsAnimSequence)
	CS_STRUCT_OPS_IS_VALID(FCsAnimSequence)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsAnimSequence)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsAnimSequence)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("%s: Anim's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Anim.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsAnimSequence)

	FORCEINLINE void Unload()
	{
		Anim.ResetWeakPtr();
		Anim_Internal = nullptr;
	}
};

#pragma endregion FCsAnimSequence

// FCsAnimSequenceInfo
#pragma region

struct FCsAnimSequenceInfo;

// NCsAnim::NSequence::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnim, NSequence, FInfo)

namespace NCsAnimSequenceInfo
{
	using ThisType = FCsAnimSequenceInfo;
	using InfoType = NCsAnim::NSequence::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSTYPES_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

// NCsAnim::NSequence::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnim, NSequence, FInfo)

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimSequenceInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	FCsAnimSequence Anim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	float PlayRate;

	FCsAnimSequenceInfo() :
		Anim(),
		PlayRate(1.0f)
	{
	}

	using InfoType = NCsAnim::NSequence::FInfo;
	using _Impl = NCsAnimSequenceInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)			{ _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info)	{ _Impl::CopyToInfoAsValue(this, Info); }

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsAnimSequenceInfo)
	CS_STRUCT_OPS_IS_VALID(FCsAnimSequenceInfo)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsAnimSequenceInfo)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsAnimSequenceInfo)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsAnimSequenceInfo)

	FORCEINLINE void Unload()
	{
		Anim.Unload();
	}
};

class UAnimSequence;

namespace NCsAnim
{
	namespace NSequence
	{
		struct CSTYPES_API FInfo
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Anim, UAnimSequence*)
			CS_DECLARE_MEMBER_WITH_PROXY(PlayRate, float)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Anim, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, 1.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(Anim);
				CS_CTOR_SET_MEMBER_PROXY(PlayRate);
			}

			FORCEINLINE FInfo(FInfo& B)
			{
				SetAnim(B.GetAnim());
				SetPlayRate(B.GetPlayRate());
			}

			FORCEINLINE FInfo(const FInfo& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Anim, UAnimSequence)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayRate, float)

			FORCEINLINE void Copy(const FInfo& B)
			{
				SetAnim(B.GetAnim());
				SetPlayRate(B.GetPlayRate());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
			bool IsTopValidChecked(const FString& Context) const;
			bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsAnimSequenceInfo

// FCsFpvAnimSequence
#pragma region

class UAnimSequence;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsFpvAnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimSequence> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimSequence> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimSequence> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimSequence> AnimVR;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anim1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anim3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anim3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 AnimVR_LoadFlags;

	UPROPERTY(Transient)
	UAnimSequence* Anim1P_Internal;

	UPROPERTY(Transient)
	UAnimSequence* Anim3P_Internal;

	UPROPERTY(Transient)
	UAnimSequence* Anim3P_Low_Internal;

	UPROPERTY(Transient)
	UAnimSequence* AnimVR_Internal;

public:

	FCsFpvAnimSequence() :
		Anim1P(nullptr),
		Anim3P(nullptr),
		Anim3P_Low(nullptr),
		AnimVR(nullptr),
		Anim1P_LoadFlags(0),
		Anim3P_LoadFlags(0),
		Anim3P_Low_LoadFlags(0),
		AnimVR_LoadFlags(0),
		Anim1P_Internal(nullptr),
		Anim3P_Internal(nullptr),
		Anim3P_Low_Internal(nullptr),
		AnimVR_Internal(nullptr)
	{
	}

	FORCEINLINE TSoftObjectPtr<UAnimSequence> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low : Anim3P;
		if (ViewType == ECsViewType::VR)
			return AnimVR;
		return Anim3P;
	}

	FORCEINLINE UAnimSequence* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFpvAnimSequence)

	FORCEINLINE void Unload()
	{
		Anim1P.ResetWeakPtr();
		Anim3P.ResetWeakPtr();
		Anim3P_Low.ResetWeakPtr();
		AnimVR.ResetWeakPtr();
		Anim1P_Internal = nullptr;
		Anim3P_Internal = nullptr;
		Anim3P_Low_Internal = nullptr;
		AnimVR_Internal = nullptr;
	}
};

#pragma endregion FCsFpvAnimSequence

// FCsAnimMontage
#pragma region

class UAnimMontage;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimMontage> Anim;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anim_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "CsCore|Anim")
	UAnimMontage* Anim_Internal;

public:

	FCsAnimMontage() :
		Anim(nullptr),
		Anim_LoadFlags(0),
		Anim_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UAnimMontage asset.
	*
	* return Anim Montage
	*/
	FORCEINLINE UAnimMontage* Get() const { return Anim_Internal; }

	/**
	* Get the pointer to the Hard reference to the UAnimMontage asset.
	*
	* return Anim Montage
	*/
	FORCEINLINE UAnimMontage** GetPtr() { return &Anim_Internal; }

	/**
	* Get the Hard reference to the UAnimMontage asset.
	*
	* @param Context	The calling context.
	* return			Anim Montage
	*/
	FORCEINLINE UAnimMontage* GetChecked(const FString& Context) const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("%s: Anim's Path is NOT Valid."), *Context);
		checkf(Anim_Internal, TEXT("%s: Failed to load Anim @ %s."), *Context, *(Anim.ToSoftObjectPath().ToString()));

		return Anim_Internal;
	}

	/**
	* Get the Hard reference to the UAnimMontage asset.
	*
	* return			Anim Montage
	*/
	FORCEINLINE UAnimMontage* GetChecked() const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("FCsAnimMontage::GetChecked: Anim's Path is NOT Valid."));
		checkf(Anim_Internal, TEXT("FCsAnimMontage::GetChecked: Failed to load Anim @ %s."), *(Anim.ToSoftObjectPath().ToString()));

		return Anim_Internal;
	}

	/**
	* Safely get the Hard reference to the UAnimMontage asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Anim Montage
	*/
	UAnimMontage* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Anim.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Anim_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim has NOT been loaded from Path @ %s."), *Context, *(Anim.ToSoftObjectPath().ToString())));
		}
		return Anim_Internal;
	}

	UAnimMontage* GetSafe()
	{
		if (!Anim.ToSoftObjectPath().IsValid())
			return nullptr;
		return Anim_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsAnimMontage)
	CS_STRUCT_OPS_IS_VALID(FCsAnimMontage)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsAnimMontage)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsAnimMontage)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Anim.ToSoftObjectPath().IsValid(), TEXT("%s: Anim's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Anim.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Anim's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsAnimMontage)

	FORCEINLINE void Unload()
	{
		Anim.ResetWeakPtr();
		Anim_Internal = nullptr;
	}
};

#pragma endregion FCsAnimMontage

// FCsAnimMontageInfo
#pragma region

struct FCsAnimMontageInfo;

// NCsAnim::NMontage::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnim, NMontage, FInfo)

namespace NCsAnimMontageInfo
{
	using ThisType = FCsAnimMontageInfo;
	using InfoType = NCsAnim::NMontage::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSTYPES_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

// NCsAnim::NMontage::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnim, NMontage, FInfo)

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimMontageInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	FCsAnimMontage Anim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	float PlayRate;

	FCsAnimMontageInfo() :
		Anim(),
		PlayRate(1.0f)
	{
	}

	using InfoType = NCsAnim::NMontage::FInfo;
	using _Impl = NCsAnimMontageInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)			{ _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info)	{ _Impl::CopyToInfoAsValue(this, Info); }

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsAnimMontageInfo)
	CS_STRUCT_OPS_IS_VALID(FCsAnimMontageInfo)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsAnimMontageInfo)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsAnimMontageInfo)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsAnimMontageInfo)

	FORCEINLINE void Unload()
	{
		Anim.Unload();
	}
};

class UAnimMontage;

namespace NCsAnim
{
	namespace NMontage
	{
		struct CSTYPES_API FInfo
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Anim, UAnimMontage*)
			CS_DECLARE_MEMBER_WITH_PROXY(PlayRate, float)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Anim, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, 1.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(Anim);
				CS_CTOR_SET_MEMBER_PROXY(PlayRate);
			}

			FORCEINLINE FInfo(FInfo& B)
			{
				SetAnim(B.GetAnim());
				SetPlayRate(B.GetPlayRate());
			}

			FORCEINLINE FInfo(const FInfo& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Anim, UAnimMontage)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayRate, float)

			FORCEINLINE void Copy(const FInfo& B)
			{
				SetAnim(B.GetAnim());
				SetPlayRate(B.GetPlayRate());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
			bool IsTopValidChecked(const FString& Context) const;
			bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsAnimMontageInfo

// FCsFpvAnimMontage
#pragma region

class UAnimMontage;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsFpvAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimMontage> Anim1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimMontage> Anim3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimMontage> Anim3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimMontage> AnimVR;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anim1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anim3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anim3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 AnimVR_LoadFlags;

	UPROPERTY(Transient)
	UAnimMontage* Anim1P_Internal;

	UPROPERTY(Transient)
	UAnimMontage* Anim3P_Internal;

	UPROPERTY(Transient)
	UAnimMontage* Anim3P_Low_Internal;

	UPROPERTY(Transient)
	UAnimMontage* AnimVR_Internal;

public:

	FCsFpvAnimMontage() :
		Anim1P(nullptr),
		Anim3P(nullptr),
		Anim3P_Low(nullptr),
		AnimVR(nullptr),
		Anim1P_LoadFlags(0),
		Anim3P_LoadFlags(0),
		Anim3P_Low_LoadFlags(0),
		AnimVR_LoadFlags(0),
		Anim1P_Internal(nullptr),
		Anim3P_Internal(nullptr),
		Anim3P_Low_Internal(nullptr),
		AnimVR_Internal(nullptr)
	{
	}

	FORCEINLINE TSoftObjectPtr<UAnimMontage> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low : Anim3P;
		if (ViewType == ECsViewType::VR)
			return AnimVR;
		return Anim3P;
	}

	FORCEINLINE UAnimMontage* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Anim1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Anim3P_Low_Internal : Anim3P_Internal;
		if (ViewType == ECsViewType::VR)
			return AnimVR_Internal;
		return Anim3P_Internal;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFpvAnimMontage)

	FORCEINLINE void Unload()
	{
		Anim1P.ResetWeakPtr();
		Anim3P.ResetWeakPtr();
		Anim3P_Low.ResetWeakPtr();
		AnimVR.ResetWeakPtr();
		Anim1P_Internal = nullptr;
		Anim3P_Internal = nullptr;
		Anim3P_Low_Internal = nullptr;
		AnimVR_Internal = nullptr;
	}
};

#pragma endregion FCsFpvAnimMontage

// FCsTArrayAnimMontage
#pragma region

class UAnimMontage;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsTArrayAnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TArray<TSoftObjectPtr<UAnimMontage>> Anims;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Anims_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "CsCore|Material")
	TArray<UAnimMontage*> Anims_Internal;

public:

	FCsTArrayAnimMontage() :
		Anims(),
		Anims_LoadFlags(0),
		Anims_Internal()
	{
	}

	/**
	* Get the Hard reference to the TArray<UAnimMontage>.
	*
	* return Array of Anim Montages
	*/
	FORCEINLINE const TArray<UAnimMontage*>& Get() const { return Anims_Internal; }

	/**
	* Get the pointer to the Hard reference to the TArray<UAnimMontage>.
	*
	* return Array of Anim Montages
	*/
	FORCEINLINE TArray<UAnimMontage*>* GetPtr() { return &Anims_Internal; }
	FORCEINLINE const TArray<UAnimMontage*>* GetPtr() const { return &Anims_Internal; }

	/**
	* Get the Hard reference to the UAnimMontage at Index.
	*
	* #param Index
	* return Anim Montage
	*/
	FORCEINLINE UAnimMontage* Get(const int32& Index) const { return Index < Anims_Internal.Num() ? Anims_Internal[Index] : nullptr; }

	/**
	* Find which Index in the Array of Anim Montages the Anim is located.
	*
	* #param Anim
	* return Index
	*/
	FORCEINLINE int32 Find(UAnimMontage* Anim) const
	{
		int32 index;
		if (Anims_Internal.Find(Anim, index))
			return (uint8)index;
		else
			return INDEX_NONE;
	}

	/**
	* Get the Hard references to the array of Anims of type: UAnimMontage.
	*
	* @param Context	The calling context.
	* return			Anims
	*/
	FORCEINLINE const TArray<UAnimMontage*>& GetChecked(const FString& Context) const
	{ 
		checkf(Anims.Num() > CS_EMPTY, TEXT("%s: No Anims set."), *Context);
		checkf(Anims.Num() == Anims_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to anims, %d != %d."), *Context, Anims.Num(), Anims_Internal.Num());

		const int32 Count = Anims.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UAnimMontage>& SoftObject = Anims[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Anims[%d]'s Path is NOT Valid."), *Context, I);

			UAnimMontage* Anim = Anims_Internal[I];
	
			checkf(Anim, TEXT("%s: Anims[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Anims_Internal;
	}

	/**
	* Get the Hard references to the array of Anims of type: UAnimMontage.
	*
	* @param Context	The calling context.
	* return			Anims
	*/
	FORCEINLINE const TArray<UAnimMontage*>& GetChecked() const
	{
		checkf(Anims.Num() > CS_EMPTY, TEXT("FCsTArrayAnimMontage::GetChecked: No Anims set."));
		checkf(Anims.Num() == Anims_Internal.Num(), TEXT("FCsTArrayAnimMontage::GetChecked: Mismatch between Soft and Hard references to anims, %d != %d."), Anims.Num(), Anims_Internal.Num());

		const int32 Count = Anims.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UAnimMontage>& SoftObject = Anims[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("FCsTArrayAnimMontage::GetChecked: Anims[%d]'s Path is NOT Valid."), I);

			UAnimMontage* Anim = Anims_Internal[I];

			checkf(Anim, TEXT("FCsTArrayAnimMontage::GetChecked: Anims[%d] has NOT been loaded from Path @ %s."), I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Anims_Internal;
	}

	/**
	* Get the Hard reference to the Anim at Index of type: UAnimMontage.
	*
	* @param Context	The calling context.
	* @param Index
	* return			Anim
	*/
	FORCEINLINE UAnimMontage* GetChecked(const FString& Context, const int32& Index) const
	{
		checkf(Index >= 0 && Index < Anims_Internal.Num(), TEXT("%s: Index: %d is NOT in the range [0, %d)."), *Context, Index, Anims_Internal.Num());

		return GetChecked(Context)[Index];
	}

	/**
	* Get the Hard reference to the Anim at Index of type: UAnimMontage.
	*
	* @param Index
	* return			Anim
	*/
	FORCEINLINE UAnimMontage* GetChecked(const int32& Index) const
	{
		checkf(Index >= 0 && Index < Anims_Internal.Num(), TEXT("FCsTArrayAnimMontage::GetChecked: Index: %d is NOT in the range [0, %d)."), Index, Anims_Internal.Num());

		return GetChecked()[Index];
	}

	/**
	* Safely get the Hard reference to the array of Anims of type: UAnimMontage.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Anims
	*/
	const TArray<UAnimMontage*>* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (Anims.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Anims set."), *Context));
			return nullptr;
		}

		if (Anims.Num() != Anims_Internal.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Mismatch between Soft and Hard references to anims, %d != %d."), *Context, Anims.Num(), Anims_Internal.Num()));
			return nullptr;
		}

		const int32 Count = Anims.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UAnimMontage>& SoftObject = Anims[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Anims[%d]'s Path is NOT Valid."), *Context, I));
				return nullptr;
			}

			UAnimMontage* Anim = Anims_Internal[I];

			if (!Anim)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Anims[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString())));
				return nullptr;
			}
		}
		return &Anims_Internal;
	}

	/**
	* Safely get the Hard reference to the Anim at Index of type: UAnimMontage.
	*
	* @param Context	The calling context.
	* @param Index
	* @param Log		(optional)
	* return			Anim
	*/
	FORCEINLINE UAnimMontage* GetSafe(const FString& Context, const int32& Index, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		const TArray<UAnimMontage*>* Mons = GetSafe(Context, Log);

		if (!Mons)
			return nullptr;

		if (Index < 0 || Index > Mons->Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Index: %d is NOT in the range [0, %d)."), *Context, Index, Mons->Num()));
			return nullptr;
		}
		return (*(Mons))[Index];
	}

	/**
	* Get the Hard reference to a random Anim of type: UAnimMontage in Anims.
	*
	* @param Context	The calling context.
	* return			Anim
	*/
	FORCEINLINE UAnimMontage* GetRandomChecked(const FString& Context) const
	{
		return GetChecked(Context)[FMath::RandRange(0, Anims_Internal.Num() - 1)];
	}

	/**
	* Get the Hard reference to a random Anim of type: UAnimMontage in Anims.
	*
	* return			Anim
	*/
	FORCEINLINE UAnimMontage* GetRandomChecked() const
	{
		return GetChecked()[FMath::RandRange(0, Anims_Internal.Num() - 1)];
	}

	/**
	* Get the Hard reference to a random Anim of type: UAnimMontage in Anims.
	*
	* @param Context	The calling context.
	* @param OutIndex
	* return			Anim
	*/
	FORCEINLINE UAnimMontage* GetRandomChecked(const FString& Context, int32& OutIndex) const
	{
		OutIndex = FMath::RandRange(0, Anims_Internal.Num() - 1);
		return GetChecked(Context)[OutIndex];
	}

	/**
	* Get the Hard reference to a random Anim of type: UAnimMontage in Anims.
	*
	* return			Anim
	*/
	FORCEINLINE UAnimMontage* GetRandomChecked(int32& OutIndex) const
	{
		OutIndex = FMath::RandRange(0, Anims_Internal.Num() - 1);
		return GetChecked()[OutIndex];
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsTArrayAnimMontage)
	CS_STRUCT_OPS_IS_VALID(FCsTArrayAnimMontage)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsTArrayAnimMontage)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsTArrayAnimMontage)

	bool IsValidChecked(const FString& Context) const
	{
		checkf(Anims.Num() > CS_EMPTY, TEXT("%s: No Anims set."), *Context);
		checkf(Anims.Num() == Anims_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to anims, %d != %d."), *Context, Anims.Num(), Anims_Internal.Num());

		const int32 Count = Anims.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UAnimMontage>& SoftObject = Anims[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Anims[%d]'s Path is NOT Valid."), *Context, I);

			UAnimMontage* Material = Anims_Internal[I];

			checkf(Material, TEXT("%s: Anims[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (Anims.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Anims set."), *Context));
			return false;
		}

		if (Anims.Num() != Anims_Internal.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Mismatch between Soft and Hard references to anims, %d != %d."), *Context, Anims.Num(), Anims_Internal.Num()));
			return false;
		}

		const int32 Count = Anims.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UAnimMontage>& SoftObject = Anims[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Anims[%d]'s Path is NOT Valid."), *Context, I));
				return false;
			}

			UAnimMontage* Anim = Anims_Internal[I];

			if (!Anim)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Anims[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString())));
				return false;
			}
		}
		return true;
	}

	bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Anims.Num() > CS_EMPTY, TEXT("%s: No Anims set."), *Context);
		checkf(Anims.Num() == Anims_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to anims, %d != %d."), *Context, Anims.Num(), Anims_Internal.Num());

		const int32 Count = Anims.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UAnimMontage>& SoftObject = Anims[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Anims[%d]'s Path is NOT Valid."), *Context, I);
		}
		return true;
	}

	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (Anims.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Anims set."), *Context));
			return false;
		}

		const int32 Count = Anims.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UAnimMontage>& SoftObject = Anims[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Anims[%d]'s Path is NOT Valid."), *Context, I));
				return false;
			}
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsTArrayAnimMontage)

	FORCEINLINE void Unload()
	{
		for (TSoftObjectPtr<UAnimMontage>& Anim : Anims)
		{
			Anim.ResetWeakPtr();
		}
		Anims_Internal.Reset();
	}
};

#pragma endregion FCsTArrayAnimMontage

// FpvAnimBlueprintMember
#pragma region

UENUM(BlueprintType)
enum class ECsFpvAnimBlueprintMember : uint8
{
	Blueprint1P						UMETA(DisplayName = "Blueprint1P"),
	Blueprint3P						UMETA(DisplayName = "Blueprint3P"),
	Blueprint3P_Low					UMETA(DisplayName = "Blueprint3P_Low"),
	BlueprintVR						UMETA(DisplayName = "BlueprintVR"),
	ECsFpvAnimBlueprintMember_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsFpvAnimBlueprintMember : public TCsEnumMap<ECsFpvAnimBlueprintMember>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFpvAnimBlueprintMember, ECsFpvAnimBlueprintMember)
};

namespace NCsFpvAnimBlueprintMember
{
	typedef ECsFpvAnimBlueprintMember Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Blueprint1P;
		extern CSTYPES_API const Type Blueprint3P;
		extern CSTYPES_API const Type Blueprint3P_Low;
		extern CSTYPES_API const Type BlueprintVR;
		extern CSTYPES_API const Type ECsFpvAnimBlueprintMember_MAX;
	}

	extern CSTYPES_API const uint8 MAX;

	FORCEINLINE const FString& ToStringFromViewType(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::Blueprint3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimBlueprintMember::Get().ToString(Ref::BlueprintVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#pragma endregion FpvAnimBlueprintMember

// FCsAnimBlueprint
#pragma region

class UAnimBlueprint;
class UAnimBlueprintGeneratedClass;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimBlueprint> Blueprint;

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "CsCore|Anim")
	UAnimBlueprintGeneratedClass* Blueprint_Internal;

public:

	FCsAnimBlueprint() :
		Blueprint(nullptr),
		Blueprint_LoadFlags(0),
		Blueprint_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the Class associated with the UAnimBlueprint asset.
	*
	* return UAnimBlueprintGeneratedClass
	*/
	FORCEINLINE UAnimBlueprintGeneratedClass* Get() const { return Blueprint_Internal; }

	/**
	* Get the pointer to the Hard reference to the Class associated with the UAnimBlueprint asset.
	*
	* return UAnimBlueprintGeneratedClass
	*/
	FORCEINLINE UAnimBlueprintGeneratedClass** GetPtr() { return &Blueprint_Internal; }

	/**
	* Get the Hard reference to the Class associated with the UAnimBlueprint asset.
	*
	* @param Context	The calling context.
	* return			UAnimBlueprintGeneratedClass
	*/
	FORCEINLINE UAnimBlueprintGeneratedClass* GetChecked(const FString& Context) const
	{
		checkf(Blueprint.ToSoftObjectPath().IsValid(), TEXT("%s: Blueprint's Path is NOT Valid."), *Context);
		checkf(Blueprint_Internal, TEXT("%s: Failed to load Blueprint @ %s."), *Context, *(Blueprint.ToSoftObjectPath().ToString()));

		return Blueprint_Internal;
	}

	/**
	* Get the Hard reference to the Class associated with the UAnimBlueprint asset.
	*
	* return			UAnimBlueprintGeneratedClass
	*/
	FORCEINLINE UAnimBlueprintGeneratedClass* GetChecked() const
	{
		checkf(Blueprint.ToSoftObjectPath().IsValid(), TEXT("FCsAnimBlueprint::GetChecked: Blueprint's Path is NOT Valid."));
		checkf(Blueprint_Internal, TEXT("FCsAnimBlueprint::GetChecked: Failed to load Blueprint @ %s."), *(Blueprint.ToSoftObjectPath().ToString()));

		return Blueprint_Internal;
	}

	/**
	* Safely get the Hard reference to the Class associated with the UAnimBlueprint asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			UAnimBlueprintGeneratedClass
	*/
	UAnimBlueprintGeneratedClass* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Blueprint.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blueprint's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Blueprint_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blueprint has NOT been loaded from Path @ %s."), *Context, *(Blueprint.ToSoftObjectPath().ToString())));
		}
		return Blueprint_Internal;
	}

	/**
	* Safely get the Hard reference to the Class associated with the UAnimBlueprint asset.
	*
	* return			UAnimBlueprintGeneratedClass
	*/
	UAnimBlueprintGeneratedClass* GetSafe()
	{
		if (!Blueprint.ToSoftObjectPath().IsValid())
			return nullptr;
		return Blueprint_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsAnimBlueprint)
	CS_STRUCT_OPS_IS_VALID(FCsAnimBlueprint)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsAnimBlueprint)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsAnimBlueprint)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		checkf(Blueprint.ToSoftObjectPath().IsValid(), TEXT("%s: Blueprint's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Blueprint.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blueprint is NULL."), *Context));
			return false;
		}
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsAnimBlueprint)

	FORCEINLINE void Unload()
	{
		Blueprint.ResetWeakPtr();
		Blueprint_Internal = nullptr;
	}
};

#pragma endregion FCsAnimBlueprint

// FCsFpvAnimBlueprint
#pragma region

class UAnimBlueprint;
class UAnimBlueprintGeneratedClass;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsFpvAnimBlueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimBlueprint> Blueprint1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimBlueprint> Blueprint3P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimBlueprint> Blueprint3P_Low;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TSoftObjectPtr<UAnimBlueprint> BlueprintVR;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blueprint1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blueprint3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blueprint3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 BlueprintVR_LoadFlags;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* Blueprint1P_Internal;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* Blueprint3P_Internal;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* Blueprint3P_Low_Internal;

	UPROPERTY(Transient)
	UAnimBlueprintGeneratedClass* BlueprintVR_Internal;

public:

	FCsFpvAnimBlueprint() :
		Blueprint1P(nullptr),
		Blueprint3P(nullptr),
		Blueprint3P_Low(nullptr),
		BlueprintVR(nullptr),
		Blueprint1P_LoadFlags(0),
		Blueprint3P_LoadFlags(0),
		Blueprint3P_Low_LoadFlags(0),
		BlueprintVR_LoadFlags(0),
		Blueprint1P_Internal(nullptr),
		Blueprint3P_Internal(nullptr),
		Blueprint3P_Low_Internal(nullptr),
		BlueprintVR_Internal(nullptr)
	{
	}

	FORCEINLINE UAnimBlueprintGeneratedClass* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blueprint1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blueprint3P_Low_Internal : Blueprint3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlueprintVR_Internal;
		return Blueprint3P_Internal;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFpvAnimBlueprint)

	FORCEINLINE void Unload()
	{
		Blueprint1P.ResetWeakPtr();
		Blueprint3P.ResetWeakPtr();
		Blueprint3P_Low.ResetWeakPtr();
		BlueprintVR.ResetWeakPtr();
		Blueprint1P_Internal = nullptr;
		Blueprint3P_Internal = nullptr;
		Blueprint3P_Low_Internal = nullptr;
		BlueprintVR_Internal = nullptr;
	}
};

#pragma endregion FCsFpvAnimBlueprint

// FpvAnimBlendSpaceMember
#pragma region

UENUM(BlueprintType)
enum class ECsFpvAnimBlendSpaceMember : uint8
{
	Blend1P							UMETA(DisplayName = "Blend1P"),
	Blend3P							UMETA(DisplayName = "Blend3P"),
	Blend3P_Low						UMETA(DisplayName = "Blend3P_Low"),
	BlendVR							UMETA(DisplayName = "BlendVR"),
	ECsFpvAnimBlendSpaceMember_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsFpvAnimBlendSpaceMember : public TCsEnumMap<ECsFpvAnimBlendSpaceMember>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFpvAnimBlendSpaceMember, ECsFpvAnimBlendSpaceMember)
};

namespace NCsFpvAnimBlendSpaceMember
{
	typedef ECsFpvAnimBlendSpaceMember Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Blend1P;
		extern CSTYPES_API const Type Blend3P;
		extern CSTYPES_API const Type Blend3P_Low;
		extern CSTYPES_API const Type BlendVR;
		extern CSTYPES_API const Type ECsFpvAnimBlendSpaceMember_MAX;
	}

	extern CSTYPES_API const uint8 MAX;

	FORCEINLINE const FString& ToStringFromViewType(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend1P); }
		if (ViewType == ECsViewType::ThirdPerson && !IsLow) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend3P); }
		if (ViewType == ECsViewType::ThirdPerson && IsLow) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::Blend3P_Low); }
		if (ViewType == ECsViewType::VR) { return EMCsFpvAnimBlendSpaceMember::Get().ToString(Type::BlendVR); }
		return CS_INVALID_ENUM_TO_STRING;
	}
}

#pragma endregion FpvAnimBlendSpaceMember

// FCsBlendSpace1D
#pragma region

class UBlendSpace1D;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsBlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace1D> Blend;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend_LoadFlags;

	UPROPERTY(Transient)
	UBlendSpace1D* Blend_Internal;

public:

	FCsBlendSpace1D() :
		Blend(nullptr),
		Blend_LoadFlags(0),
		Blend_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UBlendSpace1D asset.
	*
	* return Blend Space
	*/
	FORCEINLINE UBlendSpace1D* Get() const { return Blend_Internal; }

	/**
	* Get the pointer to the Hard reference to the UBlendSpace1D asset.
	*
	* return Blend Space
	*/
	FORCEINLINE UBlendSpace1D** GetPtr() { return &Blend_Internal; }

	/**
	* Get the Hard reference to the UBlendSpace1D asset.
	*
	* @param Context	The calling context.
	* return			Blend Space
	*/
	FORCEINLINE UBlendSpace1D* GetChecked(const FString& Context) const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("%s: Blend is NULL or the Path is NOT Valid."), *Context);

		checkf(Blend_Internal, TEXT("%s: Failed to load Blend @ %s."), *Context, *(Blend.ToSoftObjectPath().ToString()));

		return Blend_Internal;
	}

	/**
	* Get the Hard reference to the UBlendSpace1D asset.
	*
	* return			Blend Space
	*/
	FORCEINLINE UBlendSpace1D* GetChecked() const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("FCsBlendSpace1D::GetChecked: Blend is NULL or the Path is NOT Valid."));

		checkf(Blend_Internal, TEXT("FCsBlendSpace1D::GetChecked: Failed to load Blend @ %s."), *(Blend.ToSoftObjectPath().ToString()));

		return Blend_Internal;
	}

	/**
	* Safely get the Hard reference to the UBlendSpace1D asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Blend Space
	*/
	UBlendSpace1D* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Blend.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Blend_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend has NOT been loaded from Path @ %s."), *Context, *(Blend.ToSoftObjectPath().ToString())));
		}
		return Blend_Internal;
	}

	/**
	* Safely get the Hard reference to the UBlendSpace1D asset.
	*
	* return			Blend Space
	*/
	UBlendSpace1D* GetSafe()
	{
		if (!Blend.ToSoftObjectPath().IsValid())
			return nullptr;
		return Blend_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsBlendSpace1D)
	CS_STRUCT_OPS_IS_VALID(FCsBlendSpace1D)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsBlendSpace1D)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsBlendSpace1D)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("%s: Blend's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Blend.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsBlendSpace1D)

	FORCEINLINE void Unload()
	{
		Blend.ResetWeakPtr();
		Blend_Internal = nullptr;
	}
};

#pragma endregion FCsBlendSpace1D

// FCsFpvBlendSpace1D
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FCsFpvBlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace1D> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace1D> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace1D> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace1D> BlendVR;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 BlendVR_LoadFlags;

	UPROPERTY(Transient)
	UBlendSpace1D* Blend1P_Internal;

	UPROPERTY(Transient)
	UBlendSpace1D* Blend3P_Internal;

	UPROPERTY(Transient)
	UBlendSpace1D* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	UBlendSpace1D* BlendVR_Internal;

public:

	FCsFpvBlendSpace1D() :
		Blend1P(nullptr),
		Blend3P(nullptr),
		Blend3P_Low(nullptr),
		BlendVR(nullptr),
		Blend1P_LoadFlags(0),
		Blend3P_LoadFlags(0),
		Blend3P_Low_LoadFlags(0),
		BlendVR_LoadFlags(0),
		Blend1P_Internal(nullptr),
		Blend3P_Internal(nullptr),
		Blend3P_Low_Internal(nullptr),
		BlendVR_Internal(nullptr)
	{
	}

	FORCEINLINE UBlendSpace1D* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UBlendSpace1D> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFpvBlendSpace1D)

	FORCEINLINE void Unload()
	{
		Blend1P.ResetWeakPtr();
		Blend3P.ResetWeakPtr();
		Blend3P_Low.ResetWeakPtr();
		BlendVR.ResetWeakPtr();
		Blend1P_Internal = nullptr;
		Blend3P_Internal = nullptr;
		Blend3P_Low_Internal = nullptr;
		BlendVR_Internal = nullptr;
	}
};

#pragma endregion FCsFpvBlendSpace1D

// FCsBlendSpace
#pragma region

class UBlendSpace;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace> Blend;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend_LoadFlags;

	UPROPERTY(Transient)
	UBlendSpace* Blend_Internal;

public:

	FCsBlendSpace() :
		Blend(nullptr),
		Blend_LoadFlags(0),
		Blend_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UBlendSpace asset.
	*
	* return Blend Space
	*/
	FORCEINLINE UBlendSpace* Get() const { return Blend_Internal; }

	/**
	* Get the pointer to the Hard reference to the UBlendSpace asset.
	*
	* return Blend Space
	*/
	FORCEINLINE UBlendSpace** GetPtr() { return &Blend_Internal; }

	/**
	* Get the Hard reference to the UBlendSpace asset.
	*
	* @param Context	The calling context.
	* return			Blend Space
	*/
	FORCEINLINE UBlendSpace* GetChecked(const FString& Context) const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("%s: Blend is NULL or the Path is NOT Valid."), *Context);
		checkf(Blend_Internal, TEXT("%s: Failed to load Blend @ %s."), *Context, *(Blend.ToSoftObjectPath().ToString()));

		return Blend_Internal;
	}

	/**
	* Get the Hard reference to the UBlendSpace asset.
	*
	* return			Blend Space
	*/
	FORCEINLINE UBlendSpace* GetChecked() const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("FCsBlendSpace1D::GetChecked: Blend is NULL or the Path is NOT Valid."));
		checkf(Blend_Internal, TEXT("FCsBlendSpace1D::GetChecked: Failed to load Blend @ %s."), *(Blend.ToSoftObjectPath().ToString()));

		return Blend_Internal;
	}

	/**
	* Safely get the Hard reference to the UBlendSpace asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Blend Space
	*/
	UBlendSpace* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Blend.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Blend_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend has NOT been loaded from Path @ %s."), *Context, *(Blend.ToSoftObjectPath().ToString())));
		}
		return Blend_Internal;
	}

	/**
	* Safely get the Hard reference to the UBlendSpace asset.
	*
	* return			Blend Space
	*/
	UBlendSpace* GetSafe()
	{
		if (!Blend.ToSoftObjectPath().IsValid())
			return nullptr;
		return Blend_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsBlendSpace)
	CS_STRUCT_OPS_IS_VALID(FCsBlendSpace)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsBlendSpace)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsBlendSpace)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("%s: Blend's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Blend.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsBlendSpace)

	FORCEINLINE void Unload()
	{
		Blend.ResetWeakPtr();
		Blend_Internal = nullptr;
	}
};

#pragma endregion FCsBlendSpace

// FCsFpvBlendSpace
#pragma region

class UBlendSpace;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsFpvBlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UBlendSpace> BlendVR;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 BlendVR_LoadFlags;

	UPROPERTY(Transient)
	UBlendSpace* Blend1P_Internal;

	UPROPERTY(Transient)
	UBlendSpace* Blend3P_Internal;

	UPROPERTY(Transient)
	UBlendSpace* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	UBlendSpace* BlendVR_Internal;

public:

	FCsFpvBlendSpace() :
		Blend1P(nullptr),
		Blend3P(nullptr),
		Blend3P_Low(nullptr),
		BlendVR(nullptr),
		Blend1P_LoadFlags(0),
		Blend3P_LoadFlags(0),
		Blend3P_Low_LoadFlags(0),
		BlendVR_LoadFlags(0),
		Blend1P_Internal(nullptr),
		Blend3P_Internal(nullptr),
		Blend3P_Low_Internal(nullptr),
		BlendVR_Internal(nullptr)
	{
	}

	FORCEINLINE UBlendSpace* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UBlendSpace> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFpvBlendSpace)

	FORCEINLINE void Unload()
	{
		Blend1P.ResetWeakPtr();
		Blend3P.ResetWeakPtr();
		Blend3P_Low.ResetWeakPtr();
		BlendVR.ResetWeakPtr();
		Blend1P_Internal = nullptr;
		Blend3P_Internal = nullptr;
		Blend3P_Low_Internal = nullptr;
		BlendVR_Internal = nullptr;
	}
};

#pragma endregion FCsFpvBlendSpace

// FCsAimOffset
#pragma region

class UAimOffsetBlendSpace;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAimOffset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend_LoadFlags;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* Blend_Internal;

public:

	FCsAimOffset() :
		Blend(nullptr),
		Blend_LoadFlags(0),
		Blend_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UAimOffsetBlendSpace asset.
	*
	* return Aim Offset Blend Space
	*/
	FORCEINLINE UAimOffsetBlendSpace* Get() const { return Blend_Internal; }

	/**
	* Get the Hard reference to the UAimOffsetBlendSpace asset.
	*
	* @param Context	The calling context.
	* return			Aim Offset Blend Space
	*/
	FORCEINLINE UAimOffsetBlendSpace* GetChecked(const FString& Context) const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("%s: Blend is NULL or the Path is NOT Valid."), *Context);
		checkf(Blend_Internal, TEXT("%s: Failed to load Blend @ %s."), *Context, *(Blend.ToSoftObjectPath().ToString()));

		return Blend_Internal;
	}

	/**
	* Get the Hard reference to the UAimOffsetBlendSpace asset.
	*
	* return			Aim Offset Blend Space
	*/
	FORCEINLINE UAimOffsetBlendSpace* GetChecked() const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("FCsAimOffset::GetChecked: Blend is NULL or the Path is NOT Valid."));
		checkf(Blend_Internal, TEXT("FCsAimOffset::GetChecked: Failed to load Blend @ %s."), *(Blend.ToSoftObjectPath().ToString()));

		return Blend_Internal;
	}

	/**
	* Safely get the Hard reference to the UAimOffsetBlendSpace asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Aim Offset Blend Space
	*/
	UAimOffsetBlendSpace* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Blend.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Blend_Internal)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend has NOT been loaded from Path @ %s."), *Context, *(Blend.ToSoftObjectPath().ToString())));
		}
		return Blend_Internal;
	}

	/**
	* Safely get the Hard reference to the UAimOffsetBlendSpace asset.
	*
	* return			Aim Offset Blend Space
	*/
	UAimOffsetBlendSpace* GetSafe()
	{
		if (!Blend.ToSoftObjectPath().IsValid())
			return nullptr;
		return Blend_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsAimOffset)
	CS_STRUCT_OPS_IS_VALID(FCsAimOffset)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsAimOffset)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsAimOffset)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Blend.ToSoftObjectPath().IsValid(), TEXT("%s: Blend's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const
	{
		if (!Blend.ToSoftObjectPath().IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Blend's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsAimOffset)

	FORCEINLINE void Unload()
	{
		Blend.ResetWeakPtr();
		Blend_Internal = nullptr;
	}
};

#pragma endregion FCsAimOffset

// FCsFpvAimOffset
#pragma region

class UAimOffsetBlendSpace;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsFpvAimOffset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend1P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend3P;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend3P_Low;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Anim")
	TSoftObjectPtr<UAimOffsetBlendSpace> BlendVR;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Blend3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Anim", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 BlendVR_LoadFlags;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* Blend1P_Internal;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* Blend3P_Internal;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* Blend3P_Low_Internal;

	UPROPERTY(Transient)
	UAimOffsetBlendSpace* BlendVR_Internal;

public:

	FCsFpvAimOffset() :
		Blend1P(nullptr),
		Blend3P(nullptr),
		Blend3P_Low(nullptr),
		BlendVR(nullptr),
		Blend1P_LoadFlags(0),
		Blend3P_LoadFlags(0),
		Blend3P_Low_LoadFlags(0),
		BlendVR_LoadFlags(0),
		Blend1P_Internal(nullptr),
		Blend3P_Internal(nullptr),
		Blend3P_Low_Internal(nullptr),
		BlendVR_Internal(nullptr)
	{
	}

	FORCEINLINE UAimOffsetBlendSpace* Get(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low_Internal : Blend3P_Internal;
		if (ViewType == ECsViewType::VR)
			return BlendVR_Internal;
		return Blend3P_Internal;
	}

	FORCEINLINE TSoftObjectPtr<UAimOffsetBlendSpace> GeTSoftObjectPtr(const ECsViewType& ViewType, const bool &IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Blend1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Blend3P_Low : Blend3P;
		if (ViewType == ECsViewType::VR)
			return BlendVR;
		return Blend3P;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFpvAimOffset)

	FORCEINLINE void Unload()
	{
		Blend1P.ResetWeakPtr();
		Blend3P.ResetWeakPtr();
		Blend3P_Low.ResetWeakPtr();
		BlendVR.ResetWeakPtr();
		Blend1P_Internal = nullptr;
		Blend3P_Internal = nullptr;
		Blend3P_Low_Internal = nullptr;
		BlendVR_Internal = nullptr;
	}
};

#pragma endregion FCsFpvAimOffset

// AdditiveBasePoseType
#pragma region

UENUM(BlueprintType)
enum class ECsAdditiveBasePoseType : uint8
{
	/** Will be deprecated. */
	ABPT_None		UMETA(DisplayName = "None"),
	/** Use the Skeleton's ref pose as base. */
	ABPT_RefPose	UMETA(DisplayName = "Skeleton Reference Pose"),
	/** Use a whole animation as a base pose. BasePoseSeq must be set. */
	ABPT_AnimScaled	UMETA(DisplayName = "Selected animation scaled"),
	/** Use one frame of an animation as a base pose. BasePoseSeq and RefFrameIndex must be set (RefFrameIndex will be clamped). */
	ABPT_AnimFrame	UMETA(DisplayName = "Selected animation frame"),
	ABPT_MAX		UMETA(Hidden),
};

struct CSTYPES_API EMCsAdditiveBasePoseType : public TCsEnumMap<ECsAdditiveBasePoseType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAdditiveBasePoseType, ECsAdditiveBasePoseType)
};

namespace NCsAdditiveBasePoseType
{
	typedef ECsAdditiveBasePoseType Type;

	namespace Ref
	{
		extern CSTYPES_API const Type ABPT_None;
		extern CSTYPES_API const Type ABPT_RefPose;
		extern CSTYPES_API const Type ABPT_AnimScaled;
		extern CSTYPES_API const Type ABPT_AnimFrame;
		extern CSTYPES_API const Type ABPT_MAX;
	}

	extern CSTYPES_API const uint8 MAX;

	FORCEINLINE const FString& ToString(const EAdditiveBasePoseType &EType)
	{
		if (EType == EAdditiveBasePoseType::ABPT_None) { return EMCsAdditiveBasePoseType::Get().ToString(Ref::ABPT_None); }
		if (EType == EAdditiveBasePoseType::ABPT_RefPose) { return EMCsAdditiveBasePoseType::Get().ToString(Ref::ABPT_RefPose); }
		if (EType == EAdditiveBasePoseType::ABPT_AnimScaled) { return EMCsAdditiveBasePoseType::Get().ToString(Ref::ABPT_AnimScaled); }
		if (EType == EAdditiveBasePoseType::ABPT_AnimFrame) { return EMCsAdditiveBasePoseType::Get().ToString(Ref::ABPT_AnimFrame); }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE EAdditiveBasePoseType ToBaseType(const FString &String)
	{
		const Type& Enum = EMCsAdditiveBasePoseType::Get().ToType(String);

		if (Enum == Ref::ABPT_None) { return EAdditiveBasePoseType::ABPT_None; }
		if (Enum == Ref::ABPT_RefPose) { return EAdditiveBasePoseType::ABPT_RefPose; }
		if (Enum == Ref::ABPT_AnimScaled) { return EAdditiveBasePoseType::ABPT_AnimScaled; }
		if (Enum == Ref::ABPT_AnimFrame) { return EAdditiveBasePoseType::ABPT_AnimFrame; }
		return EAdditiveBasePoseType::ABPT_MAX;
	}
}

#pragma endregion AdditiveBasePoseType

// AdditiveAnimationType
#pragma region

UENUM(BlueprintType)
enum class ECsAdditiveAnimationType : uint8
{
	/** No additive. */
	AAT_None					UMETA(DisplayName = "None"),
	/* Create Additive from LocalSpace Base. */
	AAT_LocalSpaceBase			UMETA(DisplayName = "Local Space"),
	/* Create Additive from MeshSpace Rotation Only, Translation still will be LocalSpace. */
	AAT_RotationOffsetMeshSpace	UMETA(DisplayName = "Mesh Space"),
	AAT_MAX						UMETA(Hidden),
};

struct CSTYPES_API EMCsAdditiveAnimationType : public TCsEnumMap<ECsAdditiveAnimationType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAdditiveAnimationType, ECsAdditiveAnimationType)
};

namespace NCsAdditiveAnimationType
{
	typedef ECsAdditiveAnimationType Type;

	namespace Ref
	{
		extern CSTYPES_API const Type AAT_None;
		extern CSTYPES_API const Type AAT_LocalSpaceBase;
		extern CSTYPES_API const Type AAT_RotationOffsetMeshSpace;
		extern CSTYPES_API const Type AAT_MAX;
	}

	extern CSTYPES_API const uint8 MAX;

	FORCEINLINE const FString& ToString(const EAdditiveAnimationType &EType)
	{
		if (EType == EAdditiveAnimationType::AAT_None) { return EMCsAdditiveAnimationType::Get().ToString(Ref::AAT_None); }
		if (EType == EAdditiveAnimationType::AAT_LocalSpaceBase) { return EMCsAdditiveAnimationType::Get().ToString(Ref::AAT_LocalSpaceBase); }
		if (EType == EAdditiveAnimationType::AAT_RotationOffsetMeshSpace) { return EMCsAdditiveAnimationType::Get().ToString(Ref::AAT_RotationOffsetMeshSpace); }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE EAdditiveAnimationType ToBaseType(const FString &String)
	{
		const Type& Enum = EMCsAdditiveAnimationType::Get().ToType(String);

		if (Enum == Ref::AAT_None) { return EAdditiveAnimationType::AAT_None; }
		if (Enum == Ref::AAT_LocalSpaceBase) { return EAdditiveAnimationType::AAT_LocalSpaceBase; }
		if (Enum == Ref::AAT_RotationOffsetMeshSpace) { return EAdditiveAnimationType::AAT_RotationOffsetMeshSpace; }
		return EAdditiveAnimationType::AAT_MAX;
	}
}

#pragma endregion AdditiveAnimationType