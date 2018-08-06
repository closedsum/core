namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgDataMapping : MonoBehaviour
    {
        #region "Data Members"

        private static MCgDataMapping _Instance;

        #endregion // Data Members

        public static MCgDataMapping Get()
        {
            return _Instance;
        }

        public static T Get<T>() where T : MCgDataMapping
        {
            return (T)_Instance;
        }

        public virtual void Init()
        {
            if (_Instance != null)
                return;

            _Instance = this;
        }
    }
}