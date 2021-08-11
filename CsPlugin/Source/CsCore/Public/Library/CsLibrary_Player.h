// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UWorld;
class APlayerController;
class APlayerState;
class APawn;
class UPlayerInput;
class AHUD;

namespace NCsPlayer
{
	struct CSCORE_API FLibrary
	{
	public:

		/**
		* Get the first local player.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Local Player
		*/
		static ULocalPlayer* GetFirstLocalChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Safely get the first local player.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log			(optional)
		* return				Local Player
		*/
		static ULocalPlayer* GetSafeFirstLocal(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get the first local player.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Local Player
		*/
		static ULocalPlayer* GetSafeFirstLocal(const UObject* WorldContext);

		/**
		* Get the local player with the given Index.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Index
		* return				Local Player
		*/
		static ULocalPlayer* GetLocalChecked(const FString& Context, const UObject* WorldContext, const int32& Index);

		/**
		* Get the local player with the given Index.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Index
		* @param Log			(optional)
		* return				Local Player
		*/
		static ULocalPlayer* GetSafeLocal(const FString& Context, const UObject* WorldContext, const int32& Index, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get the local player with the given Index.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Index
		* return				Local Player
		*/
		static ULocalPlayer* GetSafeLocal(const UObject* WorldContext, const int32& Index);
	};

	namespace NController
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSCORE_API const FString GetFirstLocalChecked;
				}
			}
		}

		struct CSCORE_API FLibrary
		{
		public:

			static APlayerController* GetFirstLocal(const FString& Context, UWorld* World);

			template<typename T>
			FORCEINLINE static T* GetFirstLocal(const FString& Context, UWorld* World)
			{
				return Cast<T>(GetFirstLocal(Context, World));
			}

			static APlayerController* GetFirstLocal(UWorld* World);

			template<typename T>
			FORCEINLINE static T* GetFirstLocal(UWorld* World)
			{
				return Cast<T>(GetFirstLocal(World));
			}

			static APlayerController* GetFirstLocalChecked(const FString& Context, UWorld* World);

			FORCEINLINE static APlayerController* GetFirstLocalChecked(UWorld* World)
			{
				using namespace NCsPlayer::NController::NLibrary::NCached;

				return GetFirstLocalChecked(Str::GetFirstLocalChecked, World);
			}

			template<typename T>
			FORCEINLINE static T* GetFirstLocalChecked(const FString& Context, UWorld* World)
			{
				T* PC = Cast<T>(GetFirstLocalChecked(Context, World));

				checkf(PC, TEXT("%s: Failed to cast PlayerController to type: %s."), *Context, *(T::StaticClass()->GetName()));

				return PC;
			}

			template<typename T>
			FORCEINLINE static T* GetFirstLocalChecked(UWorld* World)
			{
				using namespace NCsPlayer::NController::NLibrary::NCached;

				return GetFirstLocalChecked<T>(Str::GetFirstLocalChecked, World);
			}

			static APlayerController* GetSafeFirstLocal(const FString& Context, UWorld* World, void(*Log)(const FString&) = &FCsLog::Warning);

			template<typename T>
			FORCEINLINE static T* GetSafeFirstLocal(const FString& Context, UWorld* World, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				return Cast<T>(GetSafeFirstLocal(Context, World, Log));
			}

			static APlayerController* GetSafeFirstLocal(UWorld* World);

			template<typename T>
			FORCEINLINE static T* GetSafeFirstLocal(UWorld* World)
			{
				return Cast<T>(GetSafeFirstLocal(World));
			}

			static APlayerController* GetFirstLocalChecked(const FString& Context, const UObject* WorldContext);

			static APlayerController* GetSafeFirstLocal(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			template<typename T>
			FORCEINLINE static T* GetSafeFirstLocal(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				return Cast<T>(GetSafeFirstLocal(Context, WorldContext, Log));
			}

			static APlayerController* GetLocal(const FString& Context, UWorld* World, const int32& ControllerId);

			static APlayerController* GetLocalChecked(const FString& Context, UWorld* World, const int32& ControllerId);

			static APlayerController* GetLocalChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			static APlayerController* GetSafeLocal(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

			static APlayerController* GetSafeLocal(const UObject* WorldContext, const int32& ControllerId);

			static APlayerController* GetOrFirstLocalChecked(const FString& Context, APawn* Pawn);

			static void GetAllLocal(UWorld* World, TArray<APlayerController*>& OutControllers);

			static void GetAllLocal(const UObject* WorldContext, TArray<APlayerController*>& OutControllers);

			static void GetAllLocalChecked(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers);

			static void GetAllLocalChecked(const FString& Context, const UObject* WorldContext, TArray<APlayerController*>& OutControllers);
		};
	}

	namespace NState
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetFirstLocalChecked;
			}
		}

		struct CSCORE_API FLibrary
		{
		public:

			static APlayerState* GetFirstLocal(UWorld* World);

			template<typename T>
			FORCEINLINE static T* GetFirstLocal(UWorld* World)
			{
				return Cast<T>(GetFirstLocal(World));
			}

			static APlayerState* GetFirstLocalChecked(const FString& Context, UWorld* World);

			FORCEINLINE static APlayerState* GetFirstLocalChecked(UWorld* World)
			{
				using namespace NCsPlayer::NState::NCached;

				return GetFirstLocalChecked(Str::GetFirstLocalChecked, World);
			}

			template<typename T>
			FORCEINLINE static T* GetFirstLocalChecked(const FString& Context, UWorld* World)
			{
				T* PS = Cast<T>(GetFirstLocalChecked(Context, World));

				checkf(PS, TEXT("%s: Failed to cast PlayerState to type: %s."), *Context, (T::StaticClass()->GetName()));

				return PS;
			}

			template<typename T>
			FORCEINLINE static T* GetFirstLocalChecked(UWorld* World)
			{
				using namespace NCsPlayer::NState::NCached;

				return GetFirstLocalChecked<T>(Str::GetFirstLocalChecked, World);
			}

			static bool IsFirstLocal(UWorld* World, APlayerState* PlayerState);
		};
	}

	namespace NPawn
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetFirstLocalChecked;
			}
		}

		struct CSCORE_API FLibrary
		{
		public:

			static APawn* GetFirstLocal(UWorld* World);

			template<typename T>
			FORCEINLINE static T* GetFirstLocal(UWorld* World)
			{
				return Cast<T>(GetFirstLocal(World));
			}

			static APawn* GetFirstLocalChecked(const FString& Context, UWorld* World);

			FORCEINLINE static APawn* GetFirstLocalChecked(UWorld* World)
			{
				using namespace NCsPlayer::NPawn::NCached;

				return GetFirstLocalChecked(Str::GetFirstLocalChecked, World);
			}

			static bool IsFirstLocal(UWorld* World, APawn* Pawn);

			static bool IsHuman(APawn* Pawn);
		};
	}

	namespace NInput
	{
		struct CSCORE_API FLibrary
		{
		public:

			static UPlayerInput* GetFirstLocal(UWorld* World);

			static UPlayerInput* GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			static UPlayerInput* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

			static bool CanGetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);
		};
	}

	namespace NHud
	{
		struct CSCORE_API FLibrary
		{
		public:

			static AHUD* GetFirstLocal(UWorld* World);

			template<typename T>
			FORCEINLINE static T* GetFirstLocal(UWorld* World)
			{
				return Cast<T>(GetFirstLocal(World));
			}
		};
	}
}