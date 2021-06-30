// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

namespace NCsDelegate
{
	namespace NMulticast
	{
		template<typename... ParamTypes>
		class TWrapper
		{
		private:

			TMulticastDelegate<void(ParamTypes...)> Delegate;

			TArray<FDelegateHandle> RemoveQueue;
		
			bool bBroadcasting;

		public:

			TWrapper() :
				Delegate(),
				RemoveQueue(),
				bBroadcasting(false)
			{
			}

			FORCEINLINE TMulticastDelegate<void(ParamTypes...)>& Get() { return Delegate; }

			FORCEINLINE bool Remove(const FDelegateHandle& Handle)
			{
				if (bBroadcasting)
				{
					RemoveQueue.Add(Handle);
					return false;
				}
				return Delegate.Remove(Handle);
			}

		private:

			FORCEINLINE void ResolveRemoveQueue()
			{
				if (RemoveQueue.Num() > 0)
				{
					for (const FDelegateHandle& Handle : RemoveQueue)
					{
						Delegate.Remove(Handle);
					}
					RemoveQueue.Reset(RemoveQueue.Max());
				}
			}

			FORCEINLINE void StartBroadcasting() { bBroadcasting = true; }
			FORCEINLINE void StopBroadcasting() { bBroadcasting = false; }

		public:

			void Broadcast(ParamTypes... Params) const
			{
				const_cast<TWrapper*>(this)->ResolveRemoveQueue();
				const_cast<TWrapper*>(this)->StartBroadcasting();
				
				Delegate.Broadcast(Params...);

				const_cast<TWrapper*>(this)->StopBroadcasting();
				const_cast<TWrapper*>(this)->ResolveRemoveQueue();
			}
		};
	}
}