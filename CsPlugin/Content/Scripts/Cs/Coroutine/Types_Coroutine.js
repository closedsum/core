// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../Cs/custom_typings/Cs.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

const INDEX_NONE = -1;

const ROUTINE_VALUE_SIZE = 16;

// "typedefs" - library
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check         = CommonLibrary.check;
var checkf        = CommonLibrary.checkf;
var IsValidObject = CommonLibrary.IsValidObject;
var IsInstanceOf  = CommonLibrary.IsInstanceOf;

module.exports = class NJsCoroutine
{
    static EState =
        {   
            Free:       { Value: 0, Name: "Free" },
            Init:       { Value: 1, Name: "Init" },
            Update:     { Value: 2, Name: "Update" },
            End:        { Value: 3, Name: "End" },
            EState_MAX: { Value: 4, Name: "EState_MAX" }
        }

    static EMessage =
        {
            Notify:       { Value: 0, Name: "Notify" },
            Listen:       { Value: 1, Name: "Listen" },
            Abort:        { Value: 2, Name: "Abort" },
            EMessage_MAX: { Value: 3, Name: "EMessage_MAX" }
        };

    static EEndReason =
        {
            EndOfExecution: { Value: 0, Name: "EndOfExecution" },
            AbortMessage:   { Value: 1, Name: "AbortMessage" },
            AbortCondition: { Value: 2, Name: "AbortCondition" },
            OwnerIsInvalid: { Value: 3, Name: "OwnerIsInvalid" },
            Parent:         { Value: 4, Name: "Parent" },
            UniqueInstance: { Value: 5, Name: "UniqueInstance" },
            Shutdown:       { Value: 6, Name: "Shutdown" },
            Manual:         { Value: 7, Name: "Manual" },
            EEndReason_MAX: { Value: 8, Name: "EEndReason_MAX" }
        };

    static FOwner = class Owner
    {
        constructor()
        {
            this.Owner    = null;
            this.UEObject = null;
            this.bObject  = false;
            this.UEActor = null;
        }

        IsObject() { return bObject; }

        SetObject(o)
        {
            let context = "NJsCoroutine.FOwner.SetObject";

            this.Owner = o;
            this.UEObject = UObject.C(o);
            this.bObject = IsValidObject(this.UEObject);

            checkf(this.bObject, context + ": o is NOT a UObject.");

            this.UEActor = Actor.C(o);
        }

        Copy(from)
        {
            this.Owner = from.Owner;
            this.UEObject = from.UEObject;
            this.bObject = from.bObject;
            this.UEActor = from.UEActor;
        }

        Reset()
        {
            this.Owner    = null;
            this.UEObject = null;
            this.bObject  = false;
            this.UEActor  = null;
        }
    }

    static NRegister = class Register
    {
        static FInfo = class Info
        {
            constructor()
            {
                this.Index = INDEX_NONE;
            }
        };

        static FMap = class Map
        {
            constructor()
            {
                this.Infos = [];

                this.Values     = new Array(ROUTINE_VALUE_SIZE);
                this.UsedValues = new Array(ROUTINE_VALUE_SIZE);

                for (let i = 0; i < ROUTINE_VALUE_SIZE; i++)
                {
                    this.UsedValues[i] = false;
                }

            }

            SetUsedValue(index)
            {
                if (!this.UsedValues[index])
                {
                    let info   = new NJsCoroutine.NRegister.FInfo();
                    info.Index = index;
                   
                    this.Infos.push(info);

                    this.UsedValues[index] = true;
                }
            }

            SetValue(i, v)
            {
                this.SetUsedValue(i);
                this.Values[i] = v;
            }

            GetValue(i)
            {
                this.SetUsedValue(i);
                return this.Values[i];
            }

            Reset()
            {
                for (const info of this.Infos)
                {
                    this.UsedValues[info.Index] = false;
                }
                this.Infos = [];
            }
        };
    };

    static NPayload = class Payload
    {
        static FImpl = class Impl
        {
            constructor()
            {
                this.Index = INDEX_NONE;

                let UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;
                this.Group             = UpdateGroupLibrary.GetMax();

                this.CoroutineImpl = null;
                this.StartTime = new CsTime();
                this.Owner = new NJsCoroutine.FOwner();
                this.AbortImpls = [];
                this.OnAborts = [];
                this.OnEnds = [];
                this.ParentHandle = new CsRoutineHandle();
                this.bDoInit = true;
                this.bPerformFirstUpdate = true;
                this.AbortMessages = [];
                this.RegisterMap = new NJsCoroutine.NRegister.FMap();
                this.Name = "";
            }

            SetIndex(index) { this.Index = index; }
            GetIndex() { return this.Index; }

            SetValue(index, value)
            {
                this.RegisterMap.SetValue(index, value);
            }

            Reset()
            {
                this.CoroutineImpl = null;
                this.StartTime = new CsTime();
                this.Owner.Reset();
                this.AbortImpls = [];
                this.OnAborts = [];
                this.OnEnds = [];
                this.ParentHandle = new CsRoutineHandle();
                this.bDoInit = true;
                this.bPerformFirstUpdate = true;
                this.AbortMessages = [];
                this.RegisterMap.Reset();
                this.Name = "";
            }

            Copy(from)
            {
                this.Index = from.Index;
                this.Group = from.Group;
                this.CoroutineImpl = from.CoroutineImpl;
                this.StartTime = from.StartTime;
                this.Owner = from.Owner;
                this.AbortImpls = from.AbortImpls;
                this.OnAborts = from.OnAborts;
                this.OnEnds = from.OnEnds;
                this.ParentHandle = from.ParentHandle;
                this.bDoInit = from.bDoInit;
                this.bPerformFirstUpdate = from.bPerformFirstUpdate;
                this.AbortMessages = from.AbortMessages;
                this.RegisterMap = from.RegisterMap;
                this.Name = from.Name;
            }

            IsValidChecked(context)
            {
                check(CommonLibrary.IsGeneratorChecked(context, this.CoroutineImpl));
                return true;
            }
        };
    };

    constructor()
    {
    }
};