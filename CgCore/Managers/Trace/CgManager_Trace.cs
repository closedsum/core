namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgManager_Trace
    {
        #region "Data Members"

        private static FCgManager_Trace _Instance;
        public static FCgManager_Trace Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new FCgManager_Trace();
                }
                return _Instance;
            }
        }

        #endregion // Data Members

        public FCgManager_Trace() { }

        public static FCgManager_Trace Get()
        {
            return Instance;
        }
    }
}