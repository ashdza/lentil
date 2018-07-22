// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.reducerComponent("Example");

function make(greeting, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var message = "You have clicked this " + (String(self[/* state */1][/* count */0]) + " times(s)");
              var match = self[/* state */1][/* show */1];
              return React.createElement("div", undefined, React.createElement("button", {
                              onClick: (function () {
                                  return Curry._1(self[/* send */3], /* Click */0);
                                })
                            }, message), React.createElement("button", {
                              onClick: (function () {
                                  return Curry._1(self[/* send */3], /* Toggle */1);
                                })
                            }, "Toggle greeting"), React.createElement("button", {
                              onClick: (function () {
                                  return Curry._1(self[/* send */3], /* Dec */2);
                                })
                            }, "Decrement"), match ? greeting : null);
            }),
          /* initialState */(function () {
              return /* record */[
                      /* count */0,
                      /* show */true
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              switch (action) {
                case 0 : 
                    return /* Update */Block.__(0, [/* record */[
                                /* count */state[/* count */0] + 1 | 0,
                                /* show */state[/* show */1]
                              ]]);
                case 1 : 
                    return /* Update */Block.__(0, [/* record */[
                                /* count */state[/* count */0],
                                /* show */!state[/* show */1]
                              ]]);
                case 2 : 
                    return /* Update */Block.__(0, [/* record */[
                                /* count */state[/* count */0] - 1 | 0,
                                /* show */state[/* show */1]
                              ]]);
                
              }
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */
