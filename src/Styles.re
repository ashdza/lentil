open Css;

let none = style(empty);

let song =
  style([
    display(flexBox),
    flexDirection(column),
    alignItems(stretch),
    backgroundColor(Css.lightgrey),
    boxShadow(~y=px(3), ~blur=px(5), rgba(0, 0, 0, 0.3)),
    /* padding(Theme.basePadding), */
  ]);

let title =
  style([
    fontSize(rem(1.5)),
    color(lightgrey),
    /* marginBottom(Theme.basePadding), */
  ]);

let actionButton = disabled =>
  style([
    background(disabled ? darkgray : white),
    color(black),
    border(px(1), solid, black),
    borderRadius(px(3)),
  ]);

global("body", [margin(px(15))]);

global("div", [margin(px(15))]);