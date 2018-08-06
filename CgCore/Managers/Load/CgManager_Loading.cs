namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;
    using UnityEngine.Profiling;
#if UNITY_EDITOR
    using UnityEditor;
#endif // #if UNITY_EDITOR

    public class FCgManager_Loading : MonoBehaviour
    {
#region "CVars"

        public static FCgConsoleVariableLog LogLoading = new FCgConsoleVariableLog("log.manager.loading", false, "Log Manager Loading", (int)ECgConsoleVariableFlag.Console);

#endregion // CVars

        public sealed class FOnStartLoadingAssetReferences : TCgMulticastDelegate_OneParam<int> { }
        public sealed class FOnStartLoadingAssetReference : TCgMulticastDelegate_OneParam<string> { }
        public sealed class FOnFinishedLoadingAssetReference : TCgMulticastDelegate_OneParam<FCgAssetReferenceLoadedCache> { }
        public sealed class FOnFinishedLoadingAssetReferences : TCgMulticastDelegate_TwoParams<List<object>, float> { }

        public sealed class FOnStartLoadProgress : TCgMulticastDelegate_OneParam<int> { }
        public sealed class FOnLoadProgressUpdated : TCgMulticastDelegate_OneParam<float> { }

#region "Constants"

        protected static int EMPTY = 0;
        protected static int FIRST = 0;

#endregion // Constants

#region "Data Members"

        private static FCgManager_Loading _Instance;
        public static FCgManager_Loading Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new FCgManager_Loading();
                }
                return _Instance;
            }
        }

        public List<ECgLoadAsyncOrder> AsyncOrders;
        public List<List<string>> AssetReferencesQueue;
        public List<FOnFinishedLoadingAssetReferences> OnFinishedLoadingAssetReferences_Events;

        public FOnStartLoadingAssetReferences OnStartLoadingAssetReferences_Event;
        public FOnStartLoadingAssetReference OnStartLoadingAssetReference_Event;
        public FOnFinishedLoadingAssetReference OnFinishedLoadingAssetReference_Event;
        public FOnFinishedLoadingAssetReferences OnFinishedLoadingAssetReferences_Event;

        public FOnStartLoadProgress OnStartLoadProgress_Event;
        public FOnLoadProgressUpdated OnLoadProgressUpdated_Event;

        protected int AssetReferencesLoadedCount;

        protected FCgResourceSize ResourceSizeLoaded;

        protected FCgAssetReferenceLoadedCache AssetReferenceLoadedCache;

        protected List<ResourceRequest> Requests;

        protected float LoadingStartTime;
        protected float LoadingTotalStartTime;

        protected List<object> LoadedAssets;

#endregion // Data Members

        public FCgManager_Loading()
        {
            AsyncOrders = new List<ECgLoadAsyncOrder>();
            AssetReferencesQueue = new List<List<string>>();
            OnFinishedLoadingAssetReferences_Events = new List<FOnFinishedLoadingAssetReferences>();

            OnStartLoadingAssetReferences_Event = new FOnStartLoadingAssetReferences();
            OnStartLoadingAssetReference_Event = new FOnStartLoadingAssetReference();
            OnFinishedLoadingAssetReference_Event = new FOnFinishedLoadingAssetReference();
            OnFinishedLoadingAssetReferences_Event = new FOnFinishedLoadingAssetReferences();

            AssetReferencesLoadedCount = 0;

            ResourceSizeLoaded.Reset();

            Requests = new List<ResourceRequest>();

            LoadingStartTime = 0.0f;
            LoadingTotalStartTime = 0.0f;

            LoadedAssets = new List<object>();
        }

        public static FCgManager_Loading Get()
        {
            return Instance;
        }

        public void CleanUp()
        {

        }

        public static void Shutdown()
        {
            if (_Instance == null)
                return;

            _Instance.CleanUp();
            _Instance = null;
        }

        public void OnUpdate(float deltaTime)
        {
            // If Queue Empty, EXIT
            if (AssetReferencesQueue.Capacity == EMPTY)
                return;

            List<string> assetReferences = AssetReferencesQueue[FIRST];

            if (AsyncOrders[FIRST] == ECgLoadAsyncOrder.Bulk)
                OnLoadProgressUpdated_Event.Broadcast((float)AssetReferencesLoadedCount / (float)assetReferences.Capacity);

            // If Still Loading, EXIT
            if (AssetReferencesLoadedCount < assetReferences.Capacity)
                return;

            float currentTime = Time.realtimeSinceStartup;
            float loadingTime = currentTime - LoadingTotalStartTime;

            // All AssetReferences are LOADED
            if (LogLoading.Log())
            {
                // FirstToLast
                if (AsyncOrders[FIRST] == ECgLoadAsyncOrder.FirstToLast)
                {
                    FCgDebug.Log("FCsManager_Loading.OnUpdate: Finished Loading " + AssetReferencesLoadedCount + " Assets. " + ResourceSizeLoaded.ToString_Megabytes() + " in " + loadingTime + " seconds");
                }
                // None | Bulk
                else
                {
                    FCgDebug.Log("FCsManager_Loading.OnUpdate: Finished Loading " + AssetReferencesLoadedCount + " Assets in " + loadingTime + " seconds");
                }
            }

            AsyncOrders.RemoveAt(FIRST);
            AssetReferencesQueue.RemoveAt(FIRST);

            OnFinishedLoadingAssetReferences_Events[FIRST].Broadcast(LoadedAssets, loadingTime);
            OnFinishedLoadingAssetReferences_Events.RemoveAt(FIRST);

            OnFinishedLoadingAssetReferences_Event.Broadcast(LoadedAssets, loadingTime);

            // Assume the Callback holds onto the references for LoadedAssets
            LoadedAssets.Clear();

            // If Queue is NOT Empty, Load the next batch of AssetReferences 
            if (AssetReferencesQueue.Capacity != EMPTY)
            {
                LoadAssetReferences_Internal(AssetReferencesQueue[FIRST], AsyncOrders[FIRST]);
            }
        }

        protected void OnFinishedLoadingAssetReference(AsyncOperation operation)
        {
            ResourceRequest request = (ResourceRequest)operation;

            List<string> assetReferences = AssetReferencesQueue[FIRST];
            string assetReference        = assetReferences[AssetReferencesLoadedCount];

            if (request.asset == null)
            {
                FCgDebug.LogError("FCgManager_Loading.OnFinishedLoadingAssetReference: Failed to load asset at: " + assetReference);
                return;
            }

            LoadedAssets.Add(request.asset);

            int lastCount = AssetReferencesLoadedCount;

            ++AssetReferencesLoadedCount;

            // Get Memory loaded and the time it took
            int bytes       = (int)Profiler.GetRuntimeMemorySizeLong(request.asset);
            float kilobytes = FCgCommon.BytesToKilobytes(bytes);
            float megabytes = FCgCommon.BytesToMegabytes(bytes);

            ResourceSizeLoaded.Bytes += bytes;
            ResourceSizeLoaded.Kilobytes += kilobytes;
            ResourceSizeLoaded.Megabytes += megabytes;

            float currentTime = Time.realtimeSinceStartup;
            float loadingTime = currentTime - LoadingStartTime;

            if (LogLoading.Log())
            {
                FCgDebug.Log("FCsManager_Loading.OnFinishedLoadingAssetReference: Finished Loading " + assetReference + ". " + megabytes + " mb (" + kilobytes + " kb, " + bytes + " bytes) in " + loadingTime + " seconds.");
            }

            // Broadcast the event to anyone listening
            AssetReferenceLoadedCache.Reference     = assetReference;
            AssetReferenceLoadedCache.Count         = lastCount;
            AssetReferenceLoadedCache.Size.Bytes    = bytes;
            AssetReferenceLoadedCache.Size.Kilobytes = kilobytes;
            AssetReferenceLoadedCache.Size.Megabytes = megabytes;
            AssetReferenceLoadedCache.Time          = loadingTime;

            OnFinishedLoadingAssetReference_Event.Broadcast(AssetReferenceLoadedCache);
            // FirstToLast, Queue the NEXT Asset for Async Load
            if (AssetReferencesLoadedCount < assetReferences.Capacity)
            {
                if (LogLoading.Log())
                {
                    FCgDebug.Log("FCsManager_Loading.OnFinishedLoadingAssetReference: Requesting Load of " + assetReferences[AssetReferencesLoadedCount]);
                }
                OnStartLoadingAssetReference_Event.Broadcast(assetReferences[AssetReferencesLoadedCount]);

                ResourceRequest r = Resources.LoadAsync(assetReferences[AssetReferencesLoadedCount]);
                r.completed      += OnFinishedLoadingAssetReference;
            }
            LoadingStartTime = currentTime;
        }

        protected void OnFinishedLoadingAssetReference_Bulk(AsyncOperation operation)
        {
            ResourceRequest request = (ResourceRequest)operation;

#if UNITY_EDITOR
            string assetReference = AssetDatabase.GetAssetPath(request.asset);
#endif // #if UNITY_EDITOR

            if (request.asset == null)
            {
#if UNITY_EDITOR
                FCgDebug.LogError("FCgManager_Loading.OnFinishedLoadingAssetReference_Bulk: Failed to load asset at: " + assetReference);
#else
                FCgDebug.LogError("FCgManager_Loading.OnFinishedLoadingAssetReference_Bulk: Failed to load asset");
#endif // #if UNITY_EDITOR
                return;
            }

            LoadedAssets.Add(request.asset);

            int lastCount = AssetReferencesLoadedCount;

            ++AssetReferencesLoadedCount;

            // Get Memory loaded and the time it took
            int bytes       = (int)Profiler.GetRuntimeMemorySizeLong(request.asset);
            float kilobytes = FCgCommon.BytesToKilobytes(bytes);
            float megabytes = FCgCommon.BytesToMegabytes(bytes);

            ResourceSizeLoaded.Bytes += bytes;
            ResourceSizeLoaded.Kilobytes += kilobytes;
            ResourceSizeLoaded.Megabytes += megabytes;

            float currentTime = Time.realtimeSinceStartup;
            float loadingTime = currentTime - LoadingStartTime;

            if (LogLoading.Log())
            {
#if UNITY_EDITOR
                FCgDebug.Log("FCsManager_Loading.OnFinishedLoadingAssetReference_Bulk: Finished Loading " + assetReference + ". " + megabytes + " mb (" + kilobytes + " kb, " + bytes + " bytes).");
#else
                FCgDebug.Log("FCsManager_Loading.OnFinishedLoadingAssetReference_Bulk: Finished Loading an asset. " + megabytes + " mb (" + kilobytes + " kb, " + bytes + " bytes).");
#endif // #if UNITY_EDITOR
            }

            // Broadcast the event to anyone listening
            AssetReferenceLoadedCache.Reference     = assetReference;
            AssetReferenceLoadedCache.Count         = lastCount;
            AssetReferenceLoadedCache.Size.Bytes    = bytes;
            AssetReferenceLoadedCache.Size.Kilobytes = kilobytes;
            AssetReferenceLoadedCache.Size.Megabytes = megabytes;
            AssetReferenceLoadedCache.Time          = loadingTime;

            OnFinishedLoadingAssetReference_Event.Broadcast(AssetReferenceLoadedCache);
        }

        public void LoadAssetReferences(List<string> assetReferences, ECgLoadAsyncOrder asyncOrder, FOnFinishedLoadingAssetReferences.Event e)
        {
            // Add Callback
            OnFinishedLoadingAssetReferences_Events.Add(new FOnFinishedLoadingAssetReferences());

            int count = OnFinishedLoadingAssetReferences_Events.Capacity;

            OnFinishedLoadingAssetReferences_Events[count - 1].Add(e);

            AsyncOrders.Add(asyncOrder);
            AssetReferencesQueue.Add(new List<string>());

            count = AssetReferencesQueue.Capacity;

            int size = assetReferences.Capacity;

            for (int i = 0; i < size; ++i)
            {
                AssetReferencesQueue[count - 1].Add(assetReferences[i]);
            }

            // If the FIRST batch of AssetReferences, queue loading immediately
            if (AssetReferencesQueue.Capacity == 1)
                LoadAssetReferences_Internal(AssetReferencesQueue[count - 1], asyncOrder);
        }

        public void LoadAssetReferences_Internal(List<string> assetReferences, ECgLoadAsyncOrder asyncOrder)
        {
            AssetReferencesLoadedCount = 0;

            ResourceSizeLoaded.Reset();

            // Start Loading - Load All References

            int size = assetReferences.Capacity;

            OnStartLoadingAssetReferences_Event.Broadcast(size);
            OnStartLoadProgress_Event.Broadcast(size);

            if (LogLoading.Log())
            {
                FCgDebug.Log("FCgManager_Loading.LoadAssetReferences_Internal: Requesting Load of " + size + " Assets");
                // None | Bulk
                if (asyncOrder == ECgLoadAsyncOrder.None ||
                    asyncOrder == ECgLoadAsyncOrder.Bulk)
                {
                    for (int i = 0; i < size; ++i)
                    {
                        FCgDebug.Log("FCsManager_Loading.LoadAssetReferences_Internal: Requesting Load of " + assetReferences[i]);
                    }
                }
            }
            // Start the Async Load

            // FirstToLast
            if (asyncOrder == ECgLoadAsyncOrder.FirstToLast)
            {
                if (LogLoading.Log())
                {
                    FCgDebug.Log("FCsManager_Loading.LoadAssetReferences_Internal: Requesting Load of " + assetReferences[FIRST]);
                }
                OnStartLoadingAssetReference_Event.Broadcast(assetReferences[FIRST]);

                ResourceRequest r = Resources.LoadAsync(assetReferences[FIRST]);
                r.completed      += OnFinishedLoadingAssetReference;
            }
            // Bulk
            else
            {
                for (int i = 0; i < size; ++i)
                {
                    ResourceRequest r = Resources.LoadAsync(assetReferences[i]);
                    r.completed      += OnFinishedLoadingAssetReference_Bulk;
                }
            }

            LoadingStartTime      = Time.realtimeSinceStartup;
            LoadingTotalStartTime = LoadingStartTime;
        }
    }
}