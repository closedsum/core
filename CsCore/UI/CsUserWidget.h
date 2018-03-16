// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_UI.h"
#include "Types/CsTypes_Input.h"
#include "CsUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsUserWidget_OnNativeTick, const FGeometry&, MyGeometry, float, InDeltaTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_OnOpenChild, const uint8&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUserWidget_OnOpenChild, const TEnumAsByte<ECsWidgetType::Type>&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_OnCloseChild, const uint8&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUserWidget_OnCloseChild, const TEnumAsByte<ECsWidgetType::Type>&);
// ProcessGameEvent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_Override_ProcessGameEvent, const uint8&, GameEvent);

#define CS_WIDGET_DEFINE_TYPE(TYPE)	Type = ECsWidgetType::TYPE; \
									Type_Script = (uint8)Type; \
									WidgetType_MAX = ECsWidgetType::ECsWidgetType_MAX; \
									WidgetTypeToString = &ECsWidgetType::ToString; \
									StringToWidgetType = &ECsWidgetType::ToType;

// Enums
#pragma region

namespace ECsUserWidgetRoutine
{
	enum Type
	{
		ECsUserWidgetRoutine_MAX,
	};
}

namespace ECsUserWidgetRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		return Type::ECsUserWidgetRoutine_MAX;
	}
}

#define ECS_USER_WIDGET_ROUTINE_MAX (uint8)ECsUserWidgetRoutine::ECsUserWidgetRoutine_MAX
typedef ECsUserWidgetRoutine::Type TCsUserWidgetRoutine;

#pragma endregion Enums

UCLASS()
class CSCORE_API UCsUserWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void OnNativeConstruct();

	UPROPERTY()
	bool HasNativeContructed;

	virtual void Init();
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnNativeTick OnNativeTick_ScriptEvent;

	UPROPERTY()
	bool HasInitFinished;

	virtual void OnPostProcessInput(const float &DeltaTime);
	virtual void OnUpdate(const float &DeltaSeconds);
	virtual void OnLastTick(const float &DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OO Default")
	FName ShortCode;

	TCsWidgetType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OO Default")
	uint8 Type_Script;

protected:

	TWeakObjectPtr<AActor> MyOwner;

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetMyOwner(AActor* InOwner);
	UFUNCTION(BlueprintCallable, Category = "UI")
	AActor* GetMyOwner();

	UPROPERTY()
	int32 Focus;

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void SetFocus(const ECsWidgetFocus &InFocus);
	virtual void SetFocus(const int32 &InFocus);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ClearFocus();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetFocusAll();

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Show();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Hide();

	TCsWidgetType WidgetType_MAX;

	TCsWidgetTypeToString WidgetTypeToString;
	TCsStringToWidgetType StringToWidgetType;

	TArray<TCsWidgetType> ChildWidgetTypes;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<UCsUserWidget*> ChildWidgets;

	TMap<TCsWidgetType, TArray<UCsUserWidget*>> ChildWidgetsMap;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<UCsUserWidget*> ActiveChildWidgets;

	TMap<TCsWidgetType, TArray<UCsUserWidget*>> ActiveChildWidgetsMap;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;

// Get
#pragma region
public:

	virtual UCsUserWidget* GetChildWidget(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual UCsUserWidget* GetChildWidget_Script(const uint8 &WidgetType);

	virtual UCsUserWidget* GetActiveChildWidget(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual UCsUserWidget* GetActiveChildWidget_Script(const uint8 &WidgetType);

#pragma endregion Get

	virtual void SetChildFocus(const TCsWidgetType &WidgetType, const int32 &InFocus);

// Open / Close Child
#pragma region
public:

	virtual bool OpenChild(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool OpenChild_Script(const uint8 &WidgetType);

	FBindableEvent_CsUserWidget_OnOpenChild OnOpenChild_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnOpenChild OnOpenChild_ScriptEvent;

	virtual bool IsChildOpened(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsChildOpened_Script(const uint8 &WidgetType);

	virtual bool CloseChild(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool CloseChild_Script(const uint8 &WidgetType);

	FBindableEvent_CsUserWidget_OnCloseChild OnCloseChild_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnCloseChild OnCloseChild_ScriptEvent;

	virtual void CloseAllChildrenExcept(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void CloseAllChildrenExcept_Script(const uint8 &WidgetType);

	virtual bool IsChildClosed(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsChildClosed_Script(const uint8 &WidgetType);

#pragma endregion Open / Close Child

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InWidget, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

	static void RemoveRoutine(UObject* InWidget, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

#pragma endregion Routines

// Raw Inputs
#pragma region

	virtual bool ProcessInputFrame(FCsInputFrame &InputFrame);

	virtual bool ChildWidgets_ProcessInputFrame(FCsInputFrame &InputFrame);

#pragma endregion Raw Inputs

// Game Event
#pragma region

	virtual bool ProcessGameEvent(const TCsGameEvent &GameEvent);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool ProcessGameEvent_Script(const uint8 &GameEvent);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_Override_ProcessGameEvent Override_ProcessGameEvent_ScriptEvent;

	virtual bool ChildWidgets_ProcessGameEvent(const TCsGameEvent &GamEvent);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool ChildWidgets_ProcessGameEvent_Script(const uint8 &GameEvent);

#pragma endregion Game Event
};