'use strict';

var Belt_Debug = require("bs-platform/lib/js/belt_Debug.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var AppDemo$ReactTemplate = require("./AppDemo.bs.js");

Belt_Debug.setupChromeDebugger(/* () */0);

ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, AppDemo$ReactTemplate.make(/* array */[])), "target");

/*  Not a pure module */
