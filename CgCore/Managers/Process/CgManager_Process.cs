namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgManager_Process : MonoBehaviour
    {
        public sealed class CgManager_Internal : TCgManager<ECgProcess, CgProcess> { }

        public CgManager_Internal Internal;

        void Start()
        {
            Internal = new CgManager_Internal();
        }

        void Update(){}
    }
}