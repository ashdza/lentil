// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

function str(prim) {
  return prim;
}

var comp = ReasonReact.reducerComponent("counter");

function make(i, _) {
  return /* record */[
          /* debugName */comp[/* debugName */0],
          /* reactClassInternal */comp[/* reactClassInternal */1],
          /* handedOffState */comp[/* handedOffState */2],
          /* willReceiveProps */comp[/* willReceiveProps */3],
          /* didMount */comp[/* didMount */4],
          /* didUpdate */comp[/* didUpdate */5],
          /* willUnmount */comp[/* willUnmount */6],
          /* willUpdate */comp[/* willUpdate */7],
          /* shouldUpdate */comp[/* shouldUpdate */8],
          /* render */(function (self) {
              return React.createElement("div", undefined, React.createElement("h2", undefined, "Counter"), React.createElement("h2", undefined, String(self[/* state */1])), React.createElement("span", undefined, React.createElement("button", {
                                  onClick: (function () {
                                      return Curry._1(self[/* send */3], /* Add */0);
                                    })
                                }, "+"), React.createElement("button", {
                                  onClick: (function () {
                                      return Curry._1(self[/* send */3], /* Sub */1);
                                    })
                                }, "-")));
            }),
          /* initialState */(function () {
              return i;
            }),
          /* retainedProps */comp[/* retainedProps */11],
          /* reducer */(function (a, s) {
              if (a) {
                return /* Update */Block.__(0, [s - 1 | 0]);
              } else {
                return /* Update */Block.__(0, [s + 1 | 0]);
              }
            }),
          /* subscriptions */comp[/* subscriptions */13],
          /* jsElementWrapped */comp[/* jsElementWrapped */14]
        ];
}

var Counter = /* module */[
  /* comp */comp,
  /* make */make
];

var comp$1 = ReasonReact.statelessComponent("top");

function make$1(initCounts, _) {
  return /* record */[
          /* debugName */comp$1[/* debugName */0],
          /* reactClassInternal */comp$1[/* reactClassInternal */1],
          /* handedOffState */comp$1[/* handedOffState */2],
          /* willReceiveProps */comp$1[/* willReceiveProps */3],
          /* didMount */comp$1[/* didMount */4],
          /* didUpdate */comp$1[/* didUpdate */5],
          /* willUnmount */comp$1[/* willUnmount */6],
          /* willUpdate */comp$1[/* willUpdate */7],
          /* shouldUpdate */comp$1[/* shouldUpdate */8],
          /* render */(function () {
              var counters = $$Array.of_list(List.map((function (init) {
                          return ReasonReact.element(undefined, undefined, make(init, /* array */[]));
                        }), initCounts));
              return React.createElement("div", undefined, counters);
            }),
          /* initialState */comp$1[/* initialState */10],
          /* retainedProps */comp$1[/* retainedProps */11],
          /* reducer */comp$1[/* reducer */12],
          /* subscriptions */comp$1[/* subscriptions */13],
          /* jsElementWrapped */comp$1[/* jsElementWrapped */14]
        ];
}

var Top = /* module */[
  /* comp */comp$1,
  /* make */make$1
];

ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, make$1(/* :: */[
              0,
              /* :: */[
                5,
                /* :: */[
                  25,
                  /* [] */0
                ]
              ]
            ], /* array */[])), "body");

exports.str = str;
exports.Counter = Counter;
exports.Top = Top;
/* comp Not a pure module */
