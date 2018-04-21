namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgPlayerState
    {
        public CgPawn Pawn;

        public virtual void OnUpdate(float deltaTime)
        {
            Pawn.OnUpdate(deltaTime);
        }

        public virtual void ProcessGameEvents(List<ECgGameEvent> events) { }
    }
}
