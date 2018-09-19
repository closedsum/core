namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgPlayerStateBase : MonoBehaviour
    {

        public virtual void Init() { }
        public virtual void OnUpdate(float deltaTime) { }
        public virtual void ProcessCurrentLocalSnapShot(float deltaTime) { }
    }
}