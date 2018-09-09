namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;
#if UNITY_EDITOR
    using UnityEditor;
#endif // #if UNITY_EDITOR

    public class MCgGameInstance : MonoBehaviour
    {
        public sealed class FOnExitingPlayMode : FCgMulticastDelegate { }

        #region "Data Members"

        private static MCgGameInstance _Instance;

        public FOnExitingPlayMode OnExitingPlayMode_Event;

        public MCgGameState GameState;

        public List<MCgPlayerController> PlayerControllers;

        public ulong UniqueObjectIdIndex;

        public Dictionary<ulong, ICgObject> ObjectMap;

        #endregion // Data Members

        public static MCgGameInstance Get()
        {
            return _Instance;
        }

        public static T Get<T>() where T : MCgGameInstance
        {
            return (T)_Instance;
        }

        public virtual void Init()
        {
            if (_Instance != null)
                return;

            _Instance = this;

            OnExitingPlayMode_Event = new FOnExitingPlayMode();

            MCgDataMapping.Init();
            FCgManager_Prefab.Get().Init();

#if UNITY_EDITOR
            FCgPlayInEditor.Get();
#endif // #if UNITY_EDITOR

            PlayerControllers = new List<MCgPlayerController>();

            // Set Editor Callbacks
#if UNITY_EDITOR
            EditorApplication.playModeStateChanged += OnPlayModeStateChanged;
#endif // #if UNITY_EDITOR
        }

        void Start()
        {
        }

        void Update()
        {
        }

        void OnDrawGizmos()
        {
            FCgManager_GizmoDraw.Get().OnDrawGizmos();    
        }

        public virtual void Shutdown()
        {
            FCgManager_GizmoDraw.Get().Shutdown();

            // Blockchain
            if (ICgBlockchainInterface.Get() != null)
                ICgBlockchainInterface.Get().Shutdown();
            // Process
            ICgManager_Process.Shutdown();
        }

#if UNITY_EDITOR

        public void OnPlayModeStateChanged(PlayModeStateChange state)
        {
            if (state == PlayModeStateChange.ExitingPlayMode)
                OnExitingPlayMode();
        }

        public void OnExitingPlayMode()
        {
            OnExitingPlayMode_Event.Broadcast();

            Shutdown();
        }

#endif // #if UNITY_EDITOR

#region "Object"

        public ulong GetUniqueObjectId()
        {
            ++UniqueObjectIdIndex;
            return UniqueObjectIdIndex;
        }

        public ulong RegisterUniqueObject(ICgObject o)
        {
            ulong id = GetUniqueObjectId();

            ObjectMap.Add(id, o);

            return id;
        }

        public void UnregisterUniqueObject(ulong id)
        {
            ObjectMap.Remove(id);
        }

        public ICgObject GetUniqueObjectById(ulong id)
        {
            return ObjectMap[id];
        }

        public T GetUniqueObjectById<T>(ulong id)
            where T : ICgObject
        {
            return (T)GetUniqueObjectById(id);
        }

        public ICgObject GetSafeUniqueObjectId(ulong id)
        {
            ICgObject o;

            if (ObjectMap.TryGetValue(id, out o))
                return o;
            return null;
        }

        public T GetSafeUniqueObjectId<T>(ulong id)
            where T : ICgObject
        {
            return (T)GetSafeUniqueObjectId(id);
        }

#endregion // Object
    }
}
