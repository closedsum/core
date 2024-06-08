/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var NJsDelegate1 = require("Cs/Types/Delegate/Delegate.js")
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;
var IsValidObject = CommonLibrary.IsValidObject;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;

module.exports = class NJsDelegate
{
    static FMulticastBase = class MulticastBase
    {
        /**
         * @param {{?bOrdered: boolean, ArgTypeInfos: {Type: any}[]}} params 
         */
        constructor(params)
        {
            let context = "NJsDelegate.FMulticastBase.ctor";

            check(IsValidObjectChecked(context, params));

            this.bOrdered = false;

            if (CommonLibrary.DoesKeyExist(params, "bOrdered"))
            {
                if (CommonLibrary.IsBool(params.bOrdered))
                this.bOrdered = params.bOrdered;
            }

            if (this.bOrdered)
                console.log(context + ": Ordered Multicast delegate is NOT supported by Unreal Multicast delegate. Make sure to check/update logic in c++.")

            check(CommonLibrary.DoesKeyExistChecked(context, params, "ArgTypeInfos"));

            checkf(Array.isArray(params.ArgTypeInfos), context + ": params.ArgTypeInfos is NOT an array.");

            this.ArgTypeInfos = [];

            for (const info of params.ArgTypeInfos)
            {
                check(CommonLibrary.DoesKeyExistChecked(context, info, "Type"));

                this.ArgTypeInfos.push({Type: info.Type});
            }

            this.ArgCount = this.ArgTypeInfos.length;

            this.InvocationMap = new Map(); // [Guid as string][Delegate]
            this.InvocationList = []; // [Delegate]

            this.bBroadcasting = false;

            this.RemoveQueue = new Set(); // [Guid as string]
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, Id: string, Order: int, TerminationCount: int} 
         * @returns {NJsDelegate.FDelegate}
         */
        // NJsDelegate.FDelegate CreateDelegate(object: params)

        /**
         * @param {function}    fn 
         * @param {object}      caller
         * @returns {string}    Guid as string 
         */
        /*string*/ Add(fn /*function*/, caller /*object*/)
        {
            let context = "NJsDelegate.FMulticastBase.Add";

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));
            check(IsValidObjectChecked(context, caller));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn && value.Caller !== caller, context + ": fn and caller have ALREADY been added.");
            }

            let id = Guid.NewGuid().Conv_GuidToString();

            if (this.bOrdered)
            {
                let index   = this.InvocationList.length;
                let params  = {Fn: fn, Caller: caller, bStatic: false, Order: index, TerminationCount: -1}
                let d       = this.CreateDelegate(params);
    
                this.InvocationList[index] = d;

                this.InvocationMap.set(id, d);
            }
            else
            {
                let params  = {Fn: fn, Caller: caller, bStatic: false, Order: -1, TerminationCount: -1}
                let d       = this.CreateDelegate(params);
    
                this.InvocationMap.set(id, d);
            }
            return id;
        }

        /**
         * @param {function} fn
         * @returns {string} Guid as string
         */
        /*string*/ AddStatic(fn /*function*/)
        {
            let context = "NJsDelegate.FMulticastBase.AddStatic";

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn, context + ": fn has ALREADY been added.");
            }
            
            let id = Guid.NewGuid().Conv_GuidToString();

            if (this.bOrdered)
            {
                let index   = this.InvocationList.length;
                let params  = {Fn: fn, Caller: null, bStatic: true, Id: id, Order: index, TerminationCount: -1}
                let d       = this.CreateDelegate(params);

                this.InvocationList[index] = d;
                this.InvocationMap.set(id, d);
            }
            else
            {
                let params  = {Fn: fn, Caller: null, bStatic: true, Id: id, Order: -1, TerminationCount: -1}
                let d       = this.CreateDelegate(params);

                this.InvocationMap.set(id, d);
            }
            return id;
        }
  
        /*string*/ AddOneShot(fn /*function*/, caller /*object*/)
        {
            let context = "NJsDelegate.FMulticastBase.AddOneShot";

            console.log(context + ": This is NOT supported by Unreal Multicast delegates. Make sure to check/update logic in c++.");

            check(FunctionLibrary.IsArgCountChecked(context, fn, this.ArgCount));

            for (const [key, value] of this.InvocationMap.entries())
            {
                checkf(value.Fn !== fn && value.Caller !== caller, context + ": fn and caller have ALREADY been added.");
            }

            let id = Guid.NewGuid().Conv_GuidToString();

            if (this.bOrdered)
            {
                let index   = this.InvocationList.length;
                let params = {Fn: fn, Caller: caller, bStatic: false, TerminationCount: 1}
                let d      = this.CreateDelegate(params);

                this.InvocationList[index] = d;
                this.InvocationMap.set(id, d);
            }
            else
            {
                let params = {Fn: fn, Caller: caller, bStatic: false, TerminationCount: 1}
                let d      = this.CreateDelegate(params);

                this.InvocationMap.set(id, d);
            }
            return id;
        }

        QueueRemove(id /*string*/)
        {
            if (!this.RemoveQueue.has(id))
                this.RemoveQueue.add(id);

            console.log("NJsDelegate.FMulticastBase.QueueRemove: This behavior is NOT supported by Unreal Multicast delegates. Make sure to check/update logic in c++.");
        }

        /*bool*/ Remove(id /*string*/)
        {
            let d = this.InvocationMap.get(id);

            if (d !== undefined)
            {
                // Ordered
                if (this.bOrdered)
                {
                    let j = 0;
                    let len = this.InvocationList.length;

                    for (let i = 0; j < len; ++i)
                    {
                        if (this.InvocationList[i] === d)
                        {
                            ++j;
                        }
                        this.InvocationList[i] = this.InvocationList[j];
                        this.InvocationList[i].SetOrder(i);
                        ++j;
                    }

                    this.InvocationList.splice(len - 1, 1);
                    this.InvocationMap.delete(id);
                    return true;
                }
                // Unordered
                else
                {
                    if (this.bBroadcasting)
                    {
                        this.QueueRemove(id);
                        return false;
                    }
                    else
                    {
                        this.InvocationMap.delete(id);
                        return true;
                    }
                }
            }
            return false;
        }

        /*bool*/ RemoveByCaller(caller /*object*/)
        {
            let ids = [];

            // Ordered
            if (this.bOrdered)
            {
                let i   = 0;
                let j   = 0;
                let len = this.InvocationList.length;

                for (i = 0; j < len; ++i)
                {
                    let d = this.InvocationList[i];

                    if (d.Caller === caller)
                    {
                        ++j;
                        ids.push(d.GetId());
                    }
                    this.InvocationList[i] = this.InvocationList[j];
                    this.InvocationList[i].SetOrder(i);
                }

                if (i + 1 < len)
                {
                    this.InvocationList.splice(i + 1, len - (i + 1));
                }
            }
            // Unordered
            else
            {
                for (let [key, value] of this.InvocationMap.entries())
                {
                    if (value.Caller === caller)
                    {
                        if (this.bBroadcasting)
                            this.QueueRemove(key);
                        else
                            ids.push(key);
                    }
                }
            }

            for (const id of ids)
            {
                this.InvocationMap.delete(id);
            }
            return ids.length > 0;
        }

        /*bool*/ IsBound() { return this.InvocationMap.size > 0; }
    }

    static FMulticast = class Multicast extends NJsDelegate.FMulticastBase
    {
        /**
         * @param {boolean} ordered (optional) 
         */
        constructor(ordered /*?boolean*/)
        {
            super({bOrdered: ordered, ArgTypeInfos: []});
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, Id: string, Order: int, TerminationCount: int} 
         */
        /*NJsDelegate.FDelegate*/ CreateDelegate(params /*object*/)
        {
            return new NJsDelegate1.FDelegate(params);
        }

        Broadcast()
        {
            this.bBroadcasting = true;

            let ids = [];

            // Ordered
            if (this.bOrdered)
            {
                let i = 0;
                let j = 0;
                let len = this.InvocationList.length;
                
                for (i = 0; i < len; ++i)
                {
                    let d = this.InvocationList[i];

                    d.Execute();

                    if (d.HasExpired())
                    {
                        ++j;
                        ids.push(d.GetId());
                    }

                    if (j < len)
                    {
                        this.InvocationList[i] = this.InvocationList[j];
                        this.InvocationList[i].SetOrder(i);
                    }
                }

                if (i + 1 < len)
                {
                    this.InvocationList.splice(i + 1, len - (i + 1));
                }
            }
            // Unordered
            else
            {
                for (let [key, value] of this.InvocationMap.entries())
                {
                    value.Execute();

                    // Check if the delegate should be removed after execution.
                    if (value.HasExpired())
                        ids.push(key);
                }
            }

            // Remove any delegates that have "expired"
            for (const id of ids)
            {
                this.InvocationMap.delete(id);
            }
            // Remove any queued delegates for removal
            for (const id of this.RemoveQueue.values())
            {
                this.InvocationMap.delete(id);
            }
            this.RemoveQueue.clear();

            this.bBroadcasting = false;
        }
    }

    static FMulticast_OneParam = class Multicast_OneParam extends NJsDelegate.FMulticastBase
    {
        /**
         * @param {{?bOrdered: boolean, ArgTypeInfos: {Type: any}[]}} params 
         */
        constructor(params)
        {
            super(params);
        }

        /**
         * @param {object} params {Fn: function, Caller: object, bStatic: boolean, Id: string, Order: int, TerminationCount: int} 
         */
        /*NJsDelegate.FDelegate*/ CreateDelegate(params /*object*/)
        {
            return new NJsDelegate1.FDelegate_OneParam(params);
        }

        /**
         * @param {any} param1
         * @returns {boolean}
         */
        /*bool*/ IsArgsValidChecked(param1 /*any*/)
        {
            let context = "NJsDelegate.FMulticastBase.IsArgsValidChecked";

            let args = [];

            for (const info of this.ArgTypeInfos)
            {
                args.push({type: info.Type, value: param1});
            }

            check(FunctionLibrary.IsArgsValidChecked(context, args));
            return true;
        }

        /**
         * @param {any} param1 
         */
        Broadcast(param1 /*any*/)
        {
            check(IsArgsValidChecked(param1));

            this.bBroadcasting = true;

            let ids = [];

            // Ordered
            if (this.bOrdered)
            {
                let i = 0;
                let j = 0;
                let len = this.InvocationList.length;
                
                for (i = 0; i < len; ++i)
                {
                    let d = this.InvocationList[i];

                    d.Execute(param1);

                    if (d.HasExpired())
                    {
                        ++j;
                        ids.push(d.GetId());
                    }

                    if (j < len)
                    {
                        this.InvocationList[i] = this.InvocationList[j];
                        this.InvocationList[i].SetOrder(i);
                    }
                }

                if (i + 1 < len)
                {
                    this.InvocationList.splice(i + 1, len - (i + 1));
                }
            }
            // Unordered
            else
            {
                for (let [key, value] of this.InvocationMap.entries())
                {
                    value.Execute(param1);

                    // Check if the delegate should be removed after execution.
                    if (value.HasExpired())
                        ids.push(key);
                }
            }

            // Remove any delegates that have "expired"
            for (const id of ids)
            {
                this.InvocationMap.delete(id);
            }
            // Remove any queued delegates for removal
            for (const id of this.RemoveQueue.values())
            {
                this.InvocationMap.delete(id);
            }
            this.RemoveQueue.clear();

            this.bBroadcasting = false;
        }
    }
};