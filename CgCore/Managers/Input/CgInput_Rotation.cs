﻿// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgInput_Rotation : FCgInput_Base
    {
        public class FCgInputRotation_Event : TCgMulticastDelegate_TwoParams<MonoBehaviour, Vector3> { }

        #region "Data Members"

        private Dictionary<ECgInputEvent, FCgInputRotation_Event> Events;

        #endregion // Data Members

        public FCgInput_Rotation()
        {
            Info = new FCgInputInfo(ECgInputType.Rotation, ECgInputValue.Rotator);
            Info.Event = ECgInputEvent.Stationary;
            Info.Last_Event = Info.Event;

            Events = new Dictionary<ECgInputEvent, FCgInputRotation_Event>(new ECgInputEventEqualityComparer());
            Events.Add(ECgInputEvent.FirstMoved, new FCgInputRotation_Event());
            Events.Add(ECgInputEvent.Moved, new FCgInputRotation_Event());
            Events.Add(ECgInputEvent.FirstStationary, new FCgInputRotation_Event());
            Events.Add(ECgInputEvent.Stationary, new FCgInputRotation_Event());
        }

        public void Raw(Vector3 rotation)
        {
            if ((Manager_Input.CurrentInputActionMap & (ActionMap)) == NONE)
                return;

            FCgInput input = Manager_Input.GetPreviousPreviousInputAction(Action);

            if (input == null && Info.Euler != rotation)
                FirstMoved(rotation);
            else
            if (Info.Euler != rotation)
                Moved(rotation);
            else
            if ((input == null && Info.Euler == rotation) || (input != null && input.Rotation != Info.Euler && Info.Euler == rotation))
                FirstStationary(rotation);
            else
            if (Info.Euler == rotation)
                Stationary(rotation);
        }

        public void FirstMoved(Vector3 rotation)
        {
            ECgInputEvent e = ECgInputEvent.FirstMoved;
            Info.Set(e, rotation);
            Manager_Input.AddInput(Action, e, 0.0f, Vector3.zero, rotation);

            Broadcast(e, Manager_Input.InputOwner, rotation);
        }

        public void Moved(Vector3 rotation)
        {
            ECgInputEvent e = ECgInputEvent.Moved;
            Info.Set(e, rotation);
            Manager_Input.AddInput(Action, e, 0.0f, Vector3.zero, rotation);

            Broadcast(e, Manager_Input.InputOwner, rotation);
        }

        public void FirstStationary(Vector3 rotation)
        {
            ECgInputEvent e = ECgInputEvent.FirstStationary;
            Info.Set(e, rotation);
            Manager_Input.AddInput(Action, e, 0.0f, Vector3.zero, rotation);

            Broadcast(e, Manager_Input.InputOwner, rotation);
        }

        public void Stationary(Vector3 rotation)
        {
            ECgInputEvent e = ECgInputEvent.Stationary;
            Info.Set(e, rotation);
            Manager_Input.AddInput(Action, e, 0.0f, Vector3.zero, rotation);

            Broadcast(e, Manager_Input.InputOwner, rotation);
        }

        public void AddEvent(ECgInputEvent e, FCgInputRotation_Event.Event del)
        {
            FCgInputRotation_Event handler;
            Events.TryGetValue(e, out handler);
            handler.Add(del);
        }

        private void Broadcast(ECgInputEvent e, MonoBehaviour mb, Vector3 rotation)
        {
            FCgInputRotation_Event del;
            Events.TryGetValue(e, out del);
            del.Broadcast(mb, rotation);
        }
    }
}
