[%%debugger.chrome];

module Player = ReReactPlayer.Player;

type songInProgress = {
  song: Types.song,
  prog: float,
  text: string,
};

type option('a) =
  | None
  | Some('a);

type state = {
  songList: Types.songList,
  current: option(songInProgress),
};

type action =
  | Select(Types.song)
  | UpdateProgress(float)
  | LeaveComment
  | TextChange(string);

let component = ReasonReact.reducerComponent("App");

let addFeedbackToSong =
    (
      comment: Types.comment,
      location: Types.feedbackLocation,
      song: Types.song,
    )
    : Types.song => {
  let newFeedback: Types.feedback = {location, comment};
  {...song, comments: Belt.List.add(song.comments, newFeedback)};
};

let make = (~initialSongList: Types.songList, _children) => {
  ...component,
  initialState: () => {songList: initialSongList, current: None},
  reducer: (action: action, state: state) =>
    switch (action, state) {
    | (Select(newSong), _) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: newSong, prog: 0.0, text: ""}),
      })
    | (
        UpdateProgress(playedSec),
        {songList: _sl, current: Some({song: s, prog: p, text: t})},
      ) =>
      Js.log2(playedSec, p);
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: playedSec, text: t}),
      });
    | (UpdateProgress(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        LeaveComment,
        {songList: sl, current: Some({song: s, prog: p, text: t})},
      ) =>
      let updatedSong = addFeedbackToSong(t, p, s);
      Js.log(updatedSong);
      let updatedState = {
        let updatedSongList: Types.songList =
          List.map(
            s' =>
              if (s'.Types.id != s.Types.id) {
                s';
              } else {
                updatedSong;
              },
            sl,
          );
        {
          songList: updatedSongList,
          current: Some({song: updatedSong, prog: p, text: t}),
        };
      };
      ReasonReact.Update(updatedState);
    | (LeaveComment, _state) =>
      Js.log("ERROR: LEAVE COMMENT WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        TextChange(txt),
        {songList: _sl, current: Some({song: s, prog: p, text: t})},
      ) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: p, text: txt}),
      })
    | (TextChange(_), _) =>
      Js.log("ERROR: ENTER TEXT WHEN NO SONG PLAYING");
      ReasonReact.NoUpdate;
    },
  render: self =>
    <div>
      <h1 className="title is-1"> (Util.str("Lentil")) </h1>
      <SongList
        songList=self.state.songList
        onSongSelect=((s: Types.song) => self.send(Select(s)))
      />
      (
        switch (self.state.current) {
        | Some({song: s, prog: p, text: t}) =>
          <div>
            <Player
              url=s.url
              onProgress=(
                (progress: Player.secs) =>
                  self.send(UpdateProgress(progress))
              )
            />
            <Util.Text label=(string_of_float(p)) />
            <input
              value=t
              onChange=(
                ev => {
                  let newText = ReactDOMRe.domElementToObj(
                                  ReactEventRe.Form.target(ev),
                                )##value;
                  self.send(TextChange(newText));
                }
              )
            />
            <Util.Button
              label="submit"
              onClick=(_event => self.send(LeaveComment))
            />
          </div>
        | None => ReasonReact.null
        }
      )
    </div>,
};