// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_SceneComponent.generated.h"

class USceneComponent;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_SceneComponent : public UObject
{
	GENERATED_UCLASS_BODY()

// Attach / Detach
#pragma region

	// Attach
#pragma region
public:

	/**
	* Attach this component to another scene component, optionally at a named socket. It is valid to call this on components whether or not they have been Registered.
	*
	* @param Context	The calling context
	* @param Child
	* @param Parent
	* @param Socket
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SceneComponent", meta = (AutoCreateRefTerm = "Context,Socket"))
	static bool AttachToComponent_KeepRelativeTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None);

	/**
	* Attach this component to another scene component, optionally at a named socket. It is valid to call this on components whether or not they have been Registered.
	*
	* @param Context	The calling context
	* @param Child
	* @param Parent
	* @param Socket
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SceneComponent", meta = (AutoCreateRefTerm = "Context,Socket"))
	static bool AttachToComponent_KeepWorldTransform(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None);

	/**
	* Attach this component to another scene component, optionally at a named socket. It is valid to call this on components whether or not they have been Registered.
	*
	* @param Context	The calling context
	* @param Child
	* @param Parent
	* @param Socket
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SceneComponent", meta = (AutoCreateRefTerm = "Context,Socket"))
	static bool AttachToComponent_SnapToTargetNotIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None);

	/**
	* Attach this component to another scene component, optionally at a named socket. It is valid to call this on components whether or not they have been Registered.
	*
	* @param Context	The calling context
	* @param Child
	* @param Parent
	* @param Socket
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SceneComponent", meta = (AutoCreateRefTerm = "Context,Socket"))
	static bool AttachToComponent_SnapToTargetIncludingScale(const FString& Context, USceneComponent* Child, USceneComponent* Parent, const FName& Socket = NAME_None);

#pragma endregion Attach

	// Detach
#pragma region
public:

	/**
	* Detach this component from whatever it is attached to. Automatically unwelds components that are welded together (see AttachToComponent), though note that some effects of welding may not be undone.
	* 
	* @param Context	The calling context
	* @param Component
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SceneComponent", meta = (AutoCreateRefTerm = "Context"))
	static bool DetachFromComponent_KeepRelativeTransform(const FString& Context, USceneComponent* Component);

	/**
	* Detach this component from whatever it is attached to. Automatically unwelds components that are welded together (see AttachToComponent), though note that some effects of welding may not be undone.
	* 
	* @param Context	The calling context
	* @param Component
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SceneComponent", meta = (AutoCreateRefTerm = "Context"))
	static bool DetachFromComponent_KeepWorldTransform(const FString& Context, USceneComponent* Component);

#pragma endregion Detach

#pragma endregion Attach / Detach
};