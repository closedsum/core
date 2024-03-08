// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UWorld;
class APlayerController;
class APlayerState;
class APawn;
class UPlayerInput;
class AHUD;
class APlayerCameraManager;

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

	namespace NLocal
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSCORE_API const FString GetSafeControllerId;
				}
			}
		}

		/**
		* Library associated with the Local Player
		*/
		struct CSCORE_API FLibrary
		{
		public:

			static int32 GetSafeControllerId(const FString& Context, const APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning);

			FORCEINLINE static int32 GetSafeControllerId(const APawn* Pawn)
			{
				const FString& Context = NCsPlayer::NLocal::NLibrary::NCached::Str::GetSafeControllerId;

				return GetSafeControllerId(Context, Pawn, nullptr);
			}
		};
	}

	namespace NController
	{
		namespace NLocal
		{
			/**
			* Library associated with the Local Player Controller.
			*/
			struct CSCORE_API FLibrary
			{
			public:

				static APlayerController* Get(const FString& Context, UWorld* World, const int32& ControllerId);

				static APlayerController* GetChecked(const FString& Context, UWorld* World, const int32& ControllerId);

				static APlayerController* GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

				static APlayerController* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

				static APlayerController* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

				static APlayerController* GetSafe(const UObject* WorldContext, const int32& ControllerId);
		
				static void GetAll(UWorld* World, TArray<APlayerController*>& OutControllers);

				static void GetAll(const UObject* WorldContext, TArray<APlayerController*>& OutControllers);

				static void GetAllChecked(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers);

				static bool GetSafeAll(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers, void(*Log)(const FString&) = &FCsLog::Warning);

				static void GetAllChecked(const FString& Context, const UObject* WorldContext, TArray<APlayerController*>& OutControllers);

				static bool GetSafeAll(const FString& Context, const UObject* WorldContext, TArray<APlayerController*>& OutControllers, void(*Log)(const FString&) = &FCsLog::Warning);

			};

			namespace NFirst
			{
				namespace NLibrary
				{
					namespace NCached
					{
						namespace Str
						{
							extern CSCORE_API const FString GetChecked;
						}
					}
				}

				/**
				* Library associated with the First Local Player Controller.
				*/
				struct CSCORE_API FLibrary
				{
				public:

					static APlayerController* Get(const FString& Context, UWorld* World);

					template<typename T>
					FORCEINLINE static T* Get(const FString& Context, UWorld* World)
					{
						return Cast<T>(Get(Context, World));
					}

					static APlayerController* Get(UWorld* World);

					template<typename T>
					FORCEINLINE static T* Get(UWorld* World)
					{
						return Cast<T>(Get(World));
					}

					static APlayerController* GetChecked(const FString& Context, UWorld* World);

					FORCEINLINE static APlayerController* GetChecked(UWorld* World)
					{
						using namespace NCsPlayer::NController::NLocal::NFirst::NLibrary::NCached;

						return GetChecked(Str::GetChecked, World);
					}

					template<typename T>
					FORCEINLINE static T* GetChecked(const FString& Context, UWorld* World)
					{
						T* PC = Cast<T>(GetChecked(Context, World));

						checkf(PC, TEXT("%s: Failed to cast PlayerController to type: %s."), *Context, *(T::StaticClass()->GetName()));

						return PC;
					}

					template<typename T>
					FORCEINLINE static T* GetChecked(UWorld* World)
					{
						using namespace NCsPlayer::NController::NLocal::NFirst::NLibrary::NCached;

						return GetChecked<T>(Str::GetChecked, World);
					}

					static APlayerController* GetSafe(const FString& Context, UWorld* World, void(*Log)(const FString&) = &FCsLog::Warning);

					template<typename T>
					FORCEINLINE static T* GetSafe(const FString& Context, UWorld* World, void(*Log)(const FString&) = &FCsLog::Warning)
					{
						return Cast<T>(GetSafe(Context, World, Log));
					}

					static APlayerController* GetSafe(UWorld* World);

					template<typename T>
					FORCEINLINE static T* GetSafe(UWorld* World)
					{
						return Cast<T>(GetSafe(World));
					}

					static APlayerController* GetChecked(const FString& Context, const UObject* WorldContext);

					static APlayerController* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

					template<typename T>
					FORCEINLINE static T* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
					{
						return Cast<T>(GetSafe(Context, WorldContext, Log));
					}

					static APlayerController* GetSafe(const UObject* WorldContext);

					static void PossessChecked(const FString& Context, APawn* Pawn);

					static bool SafePossess(const FString& Context, APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning);
					
					static bool SafeIsPossessedBy(const FString& Context, const APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning);
					static bool SafeIsPossessedBy(const APawn* Pawn);

					static void EnableAutoManageViewTarget(const FString& Context, const UObject* WorldContext);

					static void DisableAutoManageViewTarget(const FString& Context, const UObject* WorldContext);
				};
			}
		}

		struct CSCORE_API FLibrary
		{
		public:

			static APlayerController* GetOrFirstLocalChecked(const FString& Context, APawn* Pawn);

			static APlayerController* GetChecked(const FString& Context, const UObject* PlayerContext);

			static APlayerController* GetSafe(const FString& Context, const APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning);

			static int32 GetSafeId(const FString& Context, const UObject* PlayerContext, void(*Log)(const FString&) = &FCsLog::Warning);

			static int32 GetSafeId(const UObject* PlayerContext);

			static APlayerCameraManager* GetCameraManagerChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);
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

			static APawn* GetSafeFirstLocal(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

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

			static bool IsSafeFirstLocal(const FString& Context, const UObject* WorldContext, const APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning);

			static bool IsFirstLocal(UWorld* World, const APawn* Pawn);

			static bool IsHuman(APawn* Pawn);

			static bool SafeUnPossess(const FString& Context, APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning);
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