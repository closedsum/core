// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UWorld;
class APlayerController;
class APlayerState;
class APawn;
class UPlayerInput;
class AHUD;

namespace NCsLibraryPlayer
{
	namespace NCached
	{
		namespace Str
		{
			extern CSCORE_API const FString GetFirstLocalPlayerControllerChecked;
			extern CSCORE_API const FString GetFirstLocalPlayerStateChecked;
			extern CSCORE_API const FString GetFirstLocalPawnChecked;
		}
	}
}

class CSCORE_API FCsLibrary_Player
{
// PlayerController
#pragma region
public:

	static APlayerController* GetFirstLocalPlayerController(UWorld* World);

	template<typename T>
	FORCEINLINE static T* GetFirstLocalPlayerController(UWorld* World)
	{
		return Cast<T>(GetFirstLocalPlayerController(World));
	}

	FORCEINLINE static APlayerController* GetFirstLocalPlayerControllerChecked(const FString& Context, UWorld* World)
	{
		APlayerController* PC = GetFirstLocalPlayerController(World);

		checkf(PC, TEXT("%s: Failed to get PlayerController from World."), *Context);

		return PC;
	}

	FORCEINLINE static APlayerController* GetFirstLocalPlayerControllerChecked(UWorld* World)
	{
		using namespace NCsLibraryPlayer::NCached;

		return GetFirstLocalPlayerControllerChecked(Str::GetFirstLocalPlayerControllerChecked, World);
	}

	template<typename T>
	FORCEINLINE static T* GetFirstLocalPlayerControllerChecked(const FString& Context, UWorld* World)
	{
		T* PC = Cast<T>(GetFirstLocalPlayerControllerChecked(Context, World));

		checkf(PC, TEXT("%s: Failed to cast PlayerController to type: %s."), *Context, *(T::StaticClass()->GetName()));

		return PC;
	}

	template<typename T>
	FORCEINLINE static T* GetFirstLocalPlayerControllerChecked(UWorld* World)
	{
		using namespace NCsLibraryPlayer::NCached;

		return GetFirstLocalPlayerControllerChecked<T>(Str::GetFirstLocalPlayerControllerChecked, World);
	}

	static APlayerController* GetFirstLocalPlayerControllerChecked(const FString& Context, UObject* WorldContext);

	static APlayerController* GetLocalPlayerController(const FString& Context, UWorld* World, const int32& ControllerId);

	static APlayerController* GetLocalPlayerControllerChecked(const FString& Context, UWorld* World, const int32& ControllerId);

	static APlayerController* GetPlayerControllerOrFirstLocalChecked(const FString& Context, APawn* Pawn);

	static void GetAllLocalPlayerControllersChecked(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers);

#pragma endregion PlayerController

// PlayerState
#pragma region
public:

	static APlayerState* GetFirstLocalPlayerState(UWorld* World);

	template<typename T>
	FORCEINLINE static T* GetFirstLocalPlayerState(UWorld* World)
	{
		return Cast<T>(GetFirstLocalPlayerState(World));
	}

	static APlayerState* GetFirstLocalPlayerStateChecked(const FString& Context, UWorld* World);

	FORCEINLINE static APlayerState* GetFirstLocalPlayerStateChecked(UWorld* World)
	{
		using namespace NCsLibraryPlayer::NCached;

		return GetFirstLocalPlayerStateChecked(Str::GetFirstLocalPlayerStateChecked, World);
	}

	template<typename T>
	FORCEINLINE static T* GetFirstLocalPlayerStateChecked(const FString& Context, UWorld* World)
	{
		T* PS = Cast<T>(GetFirstLocalPlayerStateChecked(Context, World));
		
		checkf(PS, TEXT("%s: Failed to cast PlayerState to type: %s."), *Context, (T::StaticClass()->GetName()));

		return PS;
	}

	template<typename T>
	FORCEINLINE static T* GetFirstLocalPlayerStateChecked(UWorld* World)
	{
		using namespace NCsLibraryPlayer::NCached;

		return GetFirstLocalPlayerStateChecked<T>(Str::GetFirstLocalPlayerStateChecked, World);
	}

	static bool IsFirstLocalPlayerState(UWorld* World, APlayerState* PlayerState);

#pragma endregion PlayerState

// Pawn
#pragma region
public:

	static APawn* GetFirstLocalPawn(UWorld* World);

	template<typename T>
	FORCEINLINE static T* GetFirstLocalPawn(UWorld* World)
	{
		return Cast<T>(GetFirstLocalPawn(World));
	}

	static APawn* GetFirstLocalPawnChecked(const FString& Context, UWorld* World);

	FORCEINLINE static APawn* GetFirstLocalPawnChecked(UWorld* World)
	{
		using namespace NCsLibraryPlayer::NCached;

		return GetFirstLocalPawnChecked(Str::GetFirstLocalPawnChecked, World);
	}

	static bool IsFirstLocalPawn(UWorld* World, APawn* Pawn);

#pragma endregion Pawn

	static UPlayerInput* GetFirstLocalPlayerInput(UWorld* World);

	static AHUD* GetFirstLocalHUD(UWorld* World);

	template<typename T>
	FORCEINLINE static T* GetFirstLocalHUD(UWorld* World)
	{
		return Cast<T>(GetFirstLocalHUD(World));
	}

// Cursor
#pragma region
public:

	/**
	*
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	static void ShowMouseCursorChecked(const FString& Context, UObject* WorldContext);

	/**
	*
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	static void HideMouseCursorChecked(const FString& Context, UObject* WorldContext);

#pragma endregion Cursor
};