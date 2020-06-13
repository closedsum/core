// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Types/CsTypes.h"
#include "UI/CsTypes_UI.h"
#include "Managers/Input/CsTypes_Input.h"
#include "Types/Property/Multi/CsProperty_Multi_FString_Enum_ThreeParams.h"
#include "CsUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsUserWidget_OnNativeTick, const FGeometry&, MyGeometry, const float&, InDeltaTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_OnOpenChild, const uint8&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUserWidget_OnOpenChild, const FECsWidgetType&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_OnCloseChild, const uint8&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUserWidget_OnCloseChild, const FECsWidgetType&);
// ProcessGameEventInfo
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_Override_ProcessGameEventInfo, const FCsGameEventInfo&, Info);

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
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

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
class CSCOREDEPRECATED_API UCsUserWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void OnNativeConstruct();

	UPROPERTY(Transient)
	bool HasNativeContructed;

	virtual void Init();
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnNativeTick OnNativeTick_ScriptEvent;

	UPROPERTY(Transient)
	bool HasInitFinished;

	virtual void OnPostProcessInput(const float &DeltaTime);
	virtual void OnUpdate(const float &DeltaSeconds);
	virtual void OnLastTick(const float &DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OO Default")
	FName ShortCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OO Default")
	FECsWidgetType Type;

protected:

	TWeakObjectPtr<AActor> MyOwner;

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetMyOwner(AActor* InOwner);
	UFUNCTION(BlueprintCallable, Category = "UI")
	AActor* GetMyOwner();

	template<typename T>
	T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

	UFUNCTION(BlueprintCallable, Category = "UI")
	class ACsPlayerController* GetMyController();

	template<typename T>
	T* GetMyController()
	{
		return Cast<T>(GetMyController());
	}

	UPROPERTY()
	int32 Focus;

	//UFUNCTION(BlueprintCallable, Category = "UI")
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

	TArray<FECsWidgetType> ChildWidgetTypes;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<UCsUserWidget*> ChildWidgets;

	TMap<FECsWidgetType, TArray<UCsUserWidget*>> ChildWidgetsMap;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<UCsUserWidget*> ActiveChildWidgets;

	TMap<FECsWidgetType, TArray<UCsUserWidget*>> ActiveChildWidgetsMap;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;

// Get
#pragma region
public:

	virtual UCsUserWidget* GetChildWidget(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual UCsUserWidget* GetChildWidget_Script(const uint8 &WidgetType);

	virtual UCsUserWidget* GetActiveChildWidget(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual UCsUserWidget* GetActiveChildWidget_Script(const uint8 &WidgetType);

#pragma endregion Get

	virtual void SetChildFocus(const FECsWidgetType &WidgetType, const int32 &InFocus);

// Open / Close Child
#pragma region
public:

	// Open
#pragma region
public:

	virtual bool OpenChild(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool OpenChild_Script(const uint8 &WidgetType);

	FBindableEvent_CsUserWidget_OnOpenChild OnOpenChild_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnOpenChild OnOpenChild_ScriptEvent;

	TMap<FECsWidgetType, FCsInputActionMapRule> OpenChildActionMapRules;
	TMap<FECsWidgetType, bool> OpenChildShowMouseCursorRules;

	virtual bool IsChildOpened(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsChildOpened_Script(const uint8 &WidgetType);

#pragma endregion Open

	// Close
#pragma region

	virtual bool CloseChild(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool CloseChild_Script(const uint8 &WidgetType);

	FBindableEvent_CsUserWidget_OnCloseChild OnCloseChild_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnCloseChild OnCloseChild_ScriptEvent;

	TMap<FECsWidgetType, FCsInputActionMapRule> CloseChildActionMapRules;
	TMap<FECsWidgetType, bool> CloseChildShowMouseCursorRules;

	virtual void CloseAllChildrenExcept(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void CloseAllChildrenExcept_Script(const uint8 &WidgetType);

	virtual bool IsChildClosed(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsChildClosed_Script(const uint8 &WidgetType);

#pragma endregion Close

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
public:

	virtual bool ProcessInputFrame(FCsInputFrame &InputFrame);

	virtual bool ChildWidgets_ProcessInputFrame(FCsInputFrame &InputFrame);

#pragma endregion Raw Inputs

// Game Event
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool ProcessGameEventInfo(const FCsGameEventInfo &Info);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_Override_ProcessGameEventInfo Override_ProcessGameEventInfo_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool ChildWidgets_ProcessGameEventInfo(const FCsGameEventInfo &Info);

#pragma endregion Game Event

// Inventory
#pragma region
public:

	class ACsManager_Inventory* GetMyManager_Inventory();

	template<typename T>
	T* GetMyManager_Inventory()
	{
		return Cast<T>(GetMyManager_Inventory());
	}

#pragma endregion Inventory
};