open Css;

let none = style(empty);

let appTitle = style([fontSize(rem(1.5)), color(darkgrey)]);

let song =
  style([
    display(`grid),
    gridTemplateColumns([`percent(40.), `percent(30.), `percent(20.)]),
    gridTemplateRows([`auto, `auto, `auto]),
    backgroundColor(Css.lightgrey),
    boxShadow(~y=px(3), ~blur=px(5), rgba(0, 0, 0, 0.6)),
  ]);

let clickable = style([cursor(`pointer)]);

let title = style([backgroundColor(papayawhip), alignItems(`center)]);

let artist = style([backgroundColor(linen), alignItems(`center)]);

let playerEditor = style([gridColumnStart(1), gridColumnEnd(4)]);

let comments = style([alignItems(`center)]);

let actionButton = disabled =>
  style([
    background(disabled ? darkgray : white),
    color(black),
    border(px(1), solid, black),
    borderRadius(px(3)),
  ]);

global("body", [margin(px(15))]);

global("div", [margin(px(15))]);