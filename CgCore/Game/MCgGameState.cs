namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgGameState : MonoBehaviour
    {
        #region "Data Members"

        private static MCgGameState _Instance;

        #endregion // Data Members

        public static MCgGameState Get()
        {
            return _Instance;
        }

        public static T Get<T>() where T : MCgGameState
        {
            return (T)_Instance;
        }

        public virtual void Init()
        {
            if (_Instance != null)
                return;

            _Instance = this;
        }

        // Use this for initialization
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {

        }
    }
}
