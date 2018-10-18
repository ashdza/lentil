'use strict';

var App = require("./App.bs.js");
var Belt_Debug = require("bs-platform/lib/js/belt_Debug.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");

Belt_Debug.setupChromeDebugger(/* () */0);

ReactDOMRe.renderToElementWithId(App.Demo[/* demoApp */0], "target");

var renderToElementWithId = ReactDOMRe.renderToElementWithId;

exports.renderToElementWithId = renderToElementWithId;
/*  Not a pure module */
