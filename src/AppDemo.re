let comp = ReasonReact.statelessComponent("demo");
let songList: list(Types.song) = [
  Song.Demo.song,
  {
    title: "Sunday Morning",
    artist: "Maroon 5",
    url: "https://soundcloud.com/maroon-5/sunday-morning",
  },
];

let make = _children => {...comp, render: _self => <App songList />};