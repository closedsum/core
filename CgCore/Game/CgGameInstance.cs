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
        private static MCgGameInstance _Instance;

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

            FCgManager_Prefab.Get().Init();

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

        public virtual void Shutdown()
        {
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
            Shutdown();
        }

#endif // #if UNITY_EDITOR
    }
}
