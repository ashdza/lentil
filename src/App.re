[%%debugger.chrome];

module Player = ReReactPlayer.Player;

type songInProgress = {
  song: Types.song,
  prog: float,
};

type option('a) =
  | None
  | Some('a);

type current = option(songInProgress);

type state = {
  songList: Types.songList,
  current,
};

type action =
  | Select(Types.song)
  | UpdateProgress(float);

let component = ReasonReact.reducerComponent("App");

let make = (~songList: Types.songList, _children) => {
  ...component,
  initialState: () => {songList, current: None},
  reducer: (action: action, state: state) =>
    switch (action, state) {
    | (Select(newSong), _) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: newSong, prog: 0.0}),
      })
    | (
        UpdateProgress(playedSec),
        {songList: _sl, current: Some({song: s, prog: p})},
      ) =>
      Js.log2(playedSec, p);
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: playedSec}),
      });
    | (UpdateProgress(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    },
  render: self =>
    <div>
      <SongList
        songList
        onSongSelect=((s: Types.song) => self.send(Select(s)))
      />
      (
        switch (self.state.current) {
        | Some({song: s, prog: p}) =>
          <div>
            <Player
              url=s.url
              onProgress=(
                (progress: Player.secs) =>
                  self.send(UpdateProgress(progress))
              )
            />
            <Util.Text label=(string_of_float(p)) />
          </div>
        | None => ReasonReact.null
        }
      )
    </div>,
};