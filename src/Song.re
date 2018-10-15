[%%debugger.chrome];

let comp = ReasonReact.statelessComponent("song");

let nullRend = _ => ReasonReact.null;
let ignore = _ => ();

let renderSongHeader = (song: Types.song, onSelect, style) =>
  <div className=style>
    <div
      className=(Styles.title ++ " " ++ Styles.clickable)
      onClick=(_e => onSelect(song))>
      (Util.str(song.title))
    </div>
    <div className=Styles.artist> (Util.str(song.artist)) </div>
    <div className=Styles.comments>
      (Util.str("Comments: " ++ string_of_int(List.length(song.comments))))
    </div>
  </div>;

let make =
    (
      ~song: Types.song,
      ~onSelect=ignore,
      ~customRender=Util.ignoreRender,
      ~style=Styles.song,
      _children,
    ) => {
  ...comp,
  render: _self =>
    <div className=style>
      <div
        className=(Styles.title ++ " " ++ Styles.clickable)
        onClick=(_e => onSelect(song))>
        (Util.str(song.title))
      </div>
      <div className=Styles.artist> (Util.str(song.artist)) </div>
      <div className=Styles.comments>
        (
          Util.str("Comments: " ++ string_of_int(List.length(song.comments)))
        )
      </div>
      (customRender(song))
    </div>,
};

let example: Types.song = {
  id: 1,
  title: "Young and Beautiful Love",
  artist: "Ashley D'Souza",
  url: "https://soundcloud.com/ashley-dsouza-106423765/young-and-beautiful-love",
  comments: [],
};

let demoSongHeader = renderSongHeader(example, ignore, "");

module Demo = {
  let comp = ReasonReact.statelessComponent("demo");
  let song: Types.song = {
    id: 1,
    title: "Young and Beautiful Love",
    artist: "Ashley D'Souza",
    url: "https://soundcloud.com/ashley-dsouza-106423765/young-and-beautiful-love",
    comments: [],
  };
  let make = _children => {
    ...comp,
    render: _self => ReasonReact.element(make(~song, [||])),
  };
};