namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgManager_Prefab
    {
        #region "Constants"

        public static readonly string EMPTY_GAME_OBJECT_NAME = "__EmptyGameObject";

        #endregion // Constants

        #region "Data Members"

        private static FCgManager_Prefab _Instance;
        public static FCgManager_Prefab Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new FCgManager_Prefab();
                }
                return _Instance;
            }
        }

        public GameObject EmptyGameObject;

        #endregion // Data Members

        public FCgManager_Prefab()
        {

        }

        public static FCgManager_Prefab Get()
        {
            return Instance;
        }

        public void Init()
        {
            // TODO: Search for the Prefab rather than the Scene
            EmptyGameObject = GameObject.Find(EMPTY_GAME_OBJECT_NAME);
        }
    }
}