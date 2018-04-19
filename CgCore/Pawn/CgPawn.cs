namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgPawn : MonoBehaviour
    {
        #region "Data Members"

        private Transform MyTransform;

        public Vector3 CurrentDirection;
        public Vector3 CurrentVelocity;

        public float CurrentSpeed;

        #endregion // Data Members

        // Use this for initialization
        void Start()
        {   
        }

        public virtual void Init()
        {
            MyTransform = GetComponent<Transform>();
        }

        public virtual void OnUpdate(float deltaTime)
        {
            OnUpdate_Handle_Movement(deltaTime);
        }

        public virtual void OnUpdate_Handle_Movement(float deltaTime)
        {
            MyTransform.position += deltaTime * CurrentVelocity;
        }

        public void SetSpeed(float speed)
        {
            CurrentSpeed = speed;
            CurrentVelocity = speed * CurrentDirection;
        }
    }
}
