namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgPlayerStateBase : MonoBehaviour
    {
        #region "Data Members"

        [FCgReadOnly]
        public byte UniqueMappingId;

        #endregion // Data Members

        public virtual void Init() { }
        public virtual void OnUpdate(float deltaTime) { }
        public virtual void ProcessCurrentLocalSnapShot(float deltaTime) { }
    }
}