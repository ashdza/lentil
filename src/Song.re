[%%debugger.chrome];

let comp = ReasonReact.statelessComponent("song");

let make = (~song: Types.song, _children) => {
  ...comp,
  render: _self =>
    <div className="card">
      <div> (Util.str("Title: " ++ song.title)) </div>
      <div> (Util.str("Artist: " ++ song.artist)) </div>
      <div> (Util.str("URL: " ++ song.url)) </div>
      <ReReactPlayer.Player
        url=song.url
        onPlay=(() => Js.log("Play"))
        onPause=(() => Js.log("Pause"))
        onProgress=(t => Js.log2("Progress", t))
      />
    </div>,
};

module Demo = {
  let comp = ReasonReact.statelessComponent("demo");
  let song: Types.song = {
    title: "Young and Beautiful Love",
    artist: "Ashley D'Souza",
    url: "https://soundcloud.com/ashley-dsouza-106423765/young-and-beautiful-love",
  };
  let make = _children => {
    ...comp,
    render: _self => ReasonReact.element(make(~song, [||])),
  };
};