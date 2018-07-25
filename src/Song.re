let comp = ReasonReact.statelessComponent("song");
let make = (~title: string, ~artist: string, ~url: string, _children) => {
  ...comp,
  render: _self =>
    <div className="card">
      <div> (Util.str("Title: " ++ title)) </div>
      <div> (Util.str("Artist: " ++ artist)) </div>
      <div> (Util.str("URL: " ++ url)) </div>
    </div>,
};

module Demo = {
  let comp = ReasonReact.statelessComponent("demo");
  let make = _children => {
    ...comp,
    render: _self =>
      ReasonReact.element(
        make(
          ~title="Young and Beautiful Love",
          ~artist="Ashley D'Souza",
          ~url=
            "https://soundcloud.com/ashley-dsouza-106423765/young-and-beautiful-love",
          [||],
        ),
      ),
  };
};