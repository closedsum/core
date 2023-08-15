// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Log
#include "Utility/CsUILog.h"

#include "CsTypes_WidgetComponent.generated.h"

// FCsWidgetComponent_CameraInfo
#pragma region

// NCsWidgetComponent::NCamera::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWidgetComponent, NCamera, FInfo)

/**
* Describes any information related to the Camera for a WidgetComponent.
*  WidgetComponent is an object that inherits from UCsWidgetComponent
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsWidgetComponent_CameraInfo
{
	GENERATED_USTRUCT_BODY()

	/** How fast to interpolate the the rotation of the Widget Actor to face
		the Player Camera. 
		LerpRate == 0.0f -> Instance / Snap to face Camera. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component", meta = (UIMIn = "0.0", ClampMin = "0.0"))
	float LerpRate;

	/** Which Axes to Lock, which should NOT Snap to the Player Camera. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsRotationRules"))
	int32 LockAxes;

	/** Any rotation offset to apply after the Widget Actor has been oriented to face
		the Player Camera. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component")
	FRotator3f Rotation;

	FCsWidgetComponent_CameraInfo() :
		LerpRate(0.0f),
		LockAxes(4), // Roll (1 << 2)
		Rotation(0.0f)
	{
	}

#define InfoType NCsWidgetComponent::NCamera::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

namespace NCsWidgetComponent
{
	namespace NCamera
	{
		/**
		* Describes any information related to the Camera for a WidgetComponent.
		*  WidgetComponent is an object that inherits from UCsWidgetComponent
		*/
		struct CSUI_API FInfo
		{
		private:

			/** How fast to interpolate the the rotation of the Widget Actor to face
				the Player Camera.
				LerpRate == 0.0f -> Instance / Snap to face Camera. */
			CS_DECLARE_MEMBER_WITH_PROXY(LerpRate, float)
			/** Which Axes to Lock, which should NOT Snap to the Player Camera. */
			CS_DECLARE_MEMBER_WITH_PROXY(LockAxes, int32)
			/** Any rotation offset to apply after the Widget Actor has been oriented to face
				the Player Camera. */
			CS_DECLARE_MEMBER_WITH_PROXY(Rotation, FRotator3f)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(LerpRate, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(LockAxes, 4), // Roll (1 << 2)
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Rotation, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(LerpRate);
				CS_CTOR_SET_MEMBER_PROXY(LockAxes);
				CS_CTOR_SET_MEMBER_PROXY(Rotation);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LerpRate, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LockAxes, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Rotation, FRotator3f)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsWidgetComponent_CameraInfo

// FCsWidgetComponentInfo
#pragma region

// NCsWidgetComponent::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsWidgetComponent, FInfo)

/**
* Describes any information related to a WidgetComponent.
*  WidgetComponent is an object that inherits from UCsWidgetComponent
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsWidgetComponentInfo
{
	GENERATED_USTRUCT_BODY()

	/** The Widget to display. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component")
	FCsUserWidgetPtr Widget;

	/** Causes the render target to automatically match the desired size.
	  
		WARNING: If you change this every frame, it will be very expensive.  If you need
		that effect, you should keep the outer widget's sized locked and dynamically
		scale or resize some inner widget.

		TRUE = Use DrawSize. 
		FALSE = Use Desired Size from Widget. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component", meta = (ScriptName = "m_bDrawSize", InlineEditConditionToggle))
	bool bDrawSize;

	/** The size of the displayed Widget. 
		This is NOT the Desired Size of the Widget (as displayed in Editor). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component", meta = (ScriptName = "m_DrawSize", editcondition = "bDrawSize"))
	FVector2D DrawSize;

	/** Rules for how to attach Component to parent for each member of Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor")
	FCsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the WidgetComponent is attached to an Object with
	    Bone or Socket. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component")
	FName Bone;

	/** Which of the members of Transform to apply to the WidgetComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsTransformRules"))
	int32 TransformRules;

	/** Describes the space (Relative, World, ... etc) in which to apply the members of Transform. */
	UPROPERTY(EditAnywhere, Category = "CsUI|Widget Component")
	ECsTransformSpace TransformSpaces[(uint8)ECsTransform::ECsTransform_MAX];

	/** The Transform to apply to the WidgetComponent.
		If the WidgetActor is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component")
	FTransform3f Transform;

	/** Whether to use CameraInfo or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component", meta = (ScriptName = "m_bCameraInfo", InlineEditConditionToggle))
	bool bCameraInfo;

	/** Describes any information related to the Camera. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Component", meta = (ScriptName = "m_CameraInfo", editcondition = "bCameraInfo"))
	FCsWidgetComponent_CameraInfo CameraInfo;

public:

	FCsWidgetComponentInfo() :
		Widget(),
		bDrawSize(false),
		DrawSize(0.0f),
		AttachmentTransformRules(FCsAttachmentTransformRules::KeepRelativeTransform),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform3f::Identity),
		bCameraInfo(true),
		CameraInfo()
	{
		TransformSpaces[(uint8)ECsTransform::Translation] = ECsTransformSpace::Relative;
		TransformSpaces[(uint8)ECsTransform::Rotation]	  = ECsTransformSpace::Relative;
		TransformSpaces[(uint8)ECsTransform::Scale]		  = ECsTransformSpace::Relative;
	}

#define InfoType NCsWidgetComponent::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

class UUserWidget;

namespace NCsWidgetComponent
{
	/**
	* Describes any information related to a WidgetComponent.
	*  WidgetComponent is an object that inherits from UCsWidgetComponent
	*/
	struct CSUI_API FInfo
	{
	#define CameraInfoType NCsWidgetComponent::NCamera::FInfo

	private:

		/** The Widget to display. */
		CS_DECLARE_MEMBER_WITH_PROXY(Widget, UClass*)
		/** Causes the render target to automatically match the desired size.

			WARNING: If you change this every frame, it will be very expensive.  If you need
			that effect, you should keep the outer widget's sized locked and dynamically
			scale or resize some inner widget.

			TRUE = Use DrawSize.
			FALSE = Use Desired Size from Widget. */
		CS_DECLARE_MEMBER_WITH_PROXY(bDrawSize, bool)
		/** The size of the displayed Widget. 
			This is NOT the Desired Size of the Widget (as displayed in Editor). */
		CS_DECLARE_MEMBER_WITH_PROXY(DrawSize, FVector2D)
		CS_DECLARE_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
		/** Valid only when the WidgetComponent is attached to an Object with
			Bone or Socket. */
		CS_DECLARE_MEMBER_WITH_PROXY(Bone, FName)
		/** Which of the members of Transform to apply to the WidgetComponent. */
		CS_DECLARE_MEMBER_WITH_PROXY(TransformRules, int32)
		/** Describes the space (Relative, World, ... etc) in which to apply the members of Transform. */
		ECsTransformSpace TransformSpaces[(uint8)ECsTransform::ECsTransform_MAX];
		ECsTransformSpace(*TransformSpaces_Proxy)[(uint8)ECsTransform::ECsTransform_MAX];
		/** The Transform to apply to the WidgetComponent.
			If the WidgetActor is attached to a parent object, the Transform is applied as a Relative Transform
			after the attachment.
			Else, the Transform is applied as a World Transform. */
		CS_DECLARE_MEMBER_WITH_PROXY(Transform, FTransform3f)
		/** Whether to use CameraInfo or not. */
		CS_DECLARE_MEMBER_WITH_PROXY(bCameraInfo, bool)
		/** Describes any information related to the Camera. */
		CameraInfoType CameraInfo;

	public:

		FInfo() :
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Widget, nullptr),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(bDrawSize, false),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(DrawSize, 0.0f),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules::KeepRelativeTransform),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Bone, NAME_None),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(TransformRules, 7), // NCsTransformRules::All
			TransformSpaces_Proxy(nullptr),
			CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Transform),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(bCameraInfo, false),
			CameraInfo()
		{
			CS_CTOR_SET_MEMBER_PROXY(Widget);
			CS_CTOR_SET_MEMBER_PROXY(bDrawSize);
			CS_CTOR_SET_MEMBER_PROXY(DrawSize);
			CS_CTOR_SET_MEMBER_PROXY(AttachmentTransformRules);
			CS_CTOR_SET_MEMBER_PROXY(Bone);
			CS_CTOR_SET_MEMBER_PROXY(TransformRules);
			TransformSpaces_Proxy = &TransformSpaces;
			CS_CTOR_SET_MEMBER_PROXY(Transform);
			CS_CTOR_SET_MEMBER_PROXY(bCameraInfo);
		}

		CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Widget, UClass)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bDrawSize, bool)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DrawSize, FVector2D)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AttachmentTransformRules, FAttachmentTransformRules)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Bone, FName)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TransformRules, int32)
		FORCEINLINE void SetTransformSpaces(const ECsTransformSpace (&__value)[(uint8)ECsTransform::ECsTransform_MAX])
		{
			const int32 Count = (int32)ECsTransform::ECsTransform_MAX;

			for (int32 I = 0; I < Count; ++I)
			{
				TransformSpaces[I] = __value[I];
			}
			TransformSpaces_Proxy = &TransformSpaces;
		}
		FORCEINLINE void SetTransformSpaces(ECsTransformSpace(*__value)[(uint8)ECsTransform::ECsTransform_MAX])
		{
			TransformSpaces_Proxy = __value;
		}
		FORCEINLINE const ECsTransformSpace (&GetTransformSpaces() const) [(uint8)ECsTransform::ECsTransform_MAX] { return *TransformSpaces_Proxy; }
		FORCEINLINE ECsTransformSpace (*GetTransformSpacesPtr()) [(uint8)ECsTransform::ECsTransform_MAX] { return TransformSpaces_Proxy; }
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Transform, FTransform3f)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCameraInfo, bool)
		FORCEINLINE const CameraInfoType& GetCameraInfo() const { return CameraInfo; }
		FORCEINLINE CameraInfoType* GetCameraInfoPtr() { return &CameraInfo; }

		FORCEINLINE void SetTransform(USceneComponent* Component) const { NCsTransformRules::SetTransform(Component, GetTransform(), GetTransformRules(), GetTransformSpaces()); }

		void AttachChecked(const FString& Context, USceneComponent* Parent, USceneComponent* Child, const FName& BoneOrSocket = NAME_None) const;
		void AttachChecked(const FString& Context, AActor* Parent, USceneComponent* Child, const FName& BoneOrSocket = NAME_None) const;

		bool IsValidChecked(const FString& Context) const;
		bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

	#undef CameraInfoType
	};
}
#pragma endregion FCsWidgetComponentInfo