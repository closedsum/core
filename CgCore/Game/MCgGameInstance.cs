namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;
#if UNITY_EDITOR
    using UnityEditor;
#endif // #if UNITY_EDITOR

    #region "Enums"

        #region "GameInstanceOnBoard"

    public sealed class FECgGameInstanceOnBoard : FECgEnum_byte
    {
        public FECgGameInstanceOnBoard(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgGameInstanceOnBoardEqualityComparer : IEqualityComparer<FECgGameInstanceOnBoard>
    {
        public bool Equals(FECgGameInstanceOnBoard lhs, FECgGameInstanceOnBoard rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgGameInstanceOnBoard x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgGameInstanceOnBoard : TCgEnumMap<FECgGameInstanceOnBoard, byte>
    {
        private static EMCgGameInstanceOnBoard _Instance;
        public static EMCgGameInstanceOnBoard Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgGameInstanceOnBoard();
                }
                return _Instance;
            }
        }

        public static EMCgGameInstanceOnBoard Get()
        {
            return Instance;
        }
    }

        #endregion // GameInstanceOnBoard

        #region "GameInstanceState"

    public sealed class FECgGameInstanceState : FECgEnum_byte
    {
        public FECgGameInstanceState(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgGameInstanceStateEqualityComparer : IEqualityComparer<FECgGameInstanceState>
    {
        public bool Equals(FECgGameInstanceState lhs, FECgGameInstanceState rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgGameInstanceState x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgGameInstanceState : TCgEnumMap<FECgGameInstanceState, byte>
    {
        private static EMCgGameInstanceState _Instance;
        public static EMCgGameInstanceState Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgGameInstanceState();
                }
                return _Instance;
            }
        }

        public static EMCgGameInstanceState Get()
        {
            return Instance;
        }
    }

        #endregion // GameInstanceState

    #endregion // Enums

    public class MCgGameInstance : MonoBehaviour
    {
        public sealed class FOnExitingPlayMode : FCgMulticastDelegate { }

        #region "Data Members"

        private static MCgGameInstance _Instance;

        public FOnExitingPlayMode OnExitingPlayMode_Event;

        [FCgReadOnly]
        public MCgGameState GameState;

        public FECgGameInstanceOnBoard OnBoardState;
        public FECgGameInstanceState CurrentState;

            #region "Unique Id"

        [FCgReadOnly]
        public ulong UniqueObjectIdIndex;

        public Dictionary<ulong, ICgObject> ObjectMap;

        #endregion // Unique Id

        #endregion // Data Members

        public static MCgGameInstance Get()
        {
            return _Instance;
        }

        public static T Get<T>() 
            where T : MCgGameInstance
        {
            return (T)_Instance;
        }

        public virtual void Init()
        {
            if (_Instance != null)
                return;

            _Instance = this;

            OnExitingPlayMode_Event = new FOnExitingPlayMode();

            ObjectMap = new Dictionary<ulong, ICgObject>();

            MCgDataMapping.Init();
            FCgManager_Prefab.Get().Init();

#if UNITY_EDITOR
            FCgPlayInEditor.Get();
#endif // #if UNITY_EDITOR

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
