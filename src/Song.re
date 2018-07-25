let comp = ReasonReact.statelessComponent("song");

type song = {
  title: string,
  artist: string,
  url: string,
};

let make = (~song: song, _children) => {
  ...comp,
  render: _self =>
    <div className="card">
      <div> (Util.str("Title: " ++ song.title)) </div>
      <div> (Util.str("Artist: " ++ song.artist)) </div>
      <div> (Util.str("URL: " ++ song.url)) </div>
    </div>,
};

module Demo = {
  let comp = ReasonReact.statelessComponent("demo");
  let song = {
    title: "Young and Beautiful Love",
    artist: "Ashley D'Souza",
    url: "abcde",
  };
  let make = _children => {
    ...comp,
    render: _self => ReasonReact.element(make(~song, [||])),
  };
};