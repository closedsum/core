namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgManager_Input
    {
        #region "Constants"

        public static readonly ushort CG_INPUT_POOL_SIZE = 65535;
        public static readonly ushort CS_MAX_INPUT_FRAMES = 300;

        #endregion

        #region "Delegates"

        public delegate void CgManagerInput_Action(ECgInputAction action);
        public delegate void CgManagerInput_Axis(ECgInputAction action, float val);
        public delegate void CgManagerInput_Location_Raw(Vector3 v);

        #endregion

        #region "Data Members"

        public MonoBehaviour InputOwner;

        private CgKeyInput[] RawKeyInputs;
        public List<CgKeyInput> RawKeyInputsPressed;

        public CgInput[] InputPool = new CgInput[CG_INPUT_POOL_SIZE];

        private ushort CurrentInputPoolIndex;

        public int CurrentInputFrameIndex;

        CgInputFrame CurrentInputFrame;

        public int CurrentInputActionMap;

            #region "Actions"

        List<CgInput_Base> Inputs;
        List<CgInputInfo> Info;

                #region "Pressed Events"

        CgManagerInput_Action Default_Event;
        CgManagerInput_Action FirstPressed_Event;
        CgManagerInput_Action Pressed_Event;
        CgManagerInput_Action FirstReleased_Event;

                #endregion // Pressed Events

                #region "Axis Events

        CgManagerInput_Axis Axis_Event;
        CgManagerInput_Axis Axis_FirstMoved_Event;
        CgManagerInput_Axis Axis_Moved_Event;
        CgManagerInput_Axis Axis_FirstStationary_Event;
        CgManagerInput_Axis Axis_Stationary_Event;

                #endregion // Axis Events

                #region "Location Events"

                    // Mouse

        public Vector3 CurrentMousePosition;

        public CgManagerInput_Location_Raw Mouse_Location_Raw;

                    // VR


                #endregion // Location Events

            #endregion // Action

        #endregion // Data Members

        public CgManager_Input()
        {
            // Initialize array of RawKeyInputs
            Array keyValues = Enum.GetValues(typeof(KeyCode));
            int keyCodeCount = keyValues.Length;

            RawKeyInputs = new CgKeyInput[keyCodeCount];

            for (int i = 0; i < keyCodeCount; ++i)
            {
                KeyCode key = (KeyCode)keyValues.GetValue(i);

                RawKeyInputs[i] = new CgKeyInput(key);
            }

            RawKeyInputsPressed = new List<CgKeyInput>();
        }

        private void RecordRawInputs()
        {
            RawKeyInputsPressed.Clear();

            int len = RawKeyInputs.Length;

            for (int i = 0; i < len; ++i)
            {
                CgKeyInput keyInput = RawKeyInputs[i];
                KeyCode key         = keyInput.Key;
                ECgInputEvent e     = keyInput.Event;

                // Pressed
                if (Input.GetKey(key))
                {
                    if (e == ECgInputEvent.FirstPressed)
                        keyInput.Set(ECgInputEvent.Pressed, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.FirstPressed, Time.time, Time.unscaledTime, 0);
                    RawKeyInputsPressed.Add(keyInput);
                }
                // Released
                else
                {
                    if (e == ECgInputEvent.FirstStationary)
                        keyInput.Set(ECgInputEvent.FirstReleased, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.Released, Time.time, Time.unscaledTime, 0);
                }
            }
        }

        public virtual void PreProcessInput(float deltaTime)
        {
            RecordRawInputs();

            CurrentMousePosition = Input.mousePosition;

            if (Mouse_Location_Raw != null)
                Mouse_Location_Raw(CurrentMousePosition);

            // VR
        }

        public virtual void PostProcessInput(float deltaTime)
        {

        }

        public virtual void ProcessInput(MonoBehaviour actionOwner, CgInput previousInput, CgInput currentInput, float deltaTime)
        {
            if (currentInput == CgInput.NULL)
                return;
        }

        public void AllocateInput(ECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 Location = new Vector3(), Vector3 Rotation = new Vector3())
        {
        }

        public virtual void AddInput(ECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 Location = new Vector3(), Vector3 Rotation = new Vector3())
        {
        }
    }
}
