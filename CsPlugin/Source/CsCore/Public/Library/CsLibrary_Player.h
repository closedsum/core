// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

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
		*
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		*/
		static ULocalPlayer* GetFirstLocalChecked(const FString& Context, UObject* WorldContext);
	};

	namespace NController
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

			static APlayerController* GetFirstLocal(UWorld* World);

			template<typename T>
			FORCEINLINE static T* GetFirstLocal(UWorld* World)
			{
				return Cast<T>(GetFirstLocal(World));
			}

			FORCEINLINE static APlayerController* GetFirstLocalChecked(const FString& Context, UWorld* World)
			{
				APlayerController* PC = GetFirstLocal(World);

				checkf(PC, TEXT("%s: Failed to get PlayerController from World."), *Context);

				return PC;
			}

			FORCEINLINE static APlayerController* GetFirstLocalChecked(UWorld* World)
			{
				using namespace NCsPlayer::NController::NCached;

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
				using namespace NCsPlayer::NController::NCached;

				return GetFirstLocalChecked<T>(Str::GetFirstLocalChecked, World);
			}

			static APlayerController* GetFirstLocalChecked(const FString& Context, UObject* WorldContext);

			static APlayerController* GetLocal(const FString& Context, UWorld* World, const int32& ControllerId);

			static APlayerController* GetLocalChecked(const FString& Context, UWorld* World, const int32& ControllerId);

			static APlayerController* GetLocalChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId);

			static APlayerController* GetOrFirstLocalChecked(const FString& Context, APawn* Pawn);

			static void GetAllLocal(UWorld* World, TArray<APlayerController*>& OutControllers);

			static void GetAllLocal(UObject* WorldContext, TArray<APlayerController*>& OutControllers);

			static void GetAllLocalChecked(const FString& Context, UWorld* World, TArray<APlayerController*>& OutControllers);

			static void GetAllLocalChecked(const FString& Context, UObject* WorldContext, TArray<APlayerController*>& OutControllers);
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
		};
	}

	namespace NInput
	{
		struct CSCORE_API FLibrary
		{
		public:

			static UPlayerInput* GetFirstLocal(UWorld* World);
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