[%%debugger.chrome];

open Types;

let component = ReasonReact.reducerComponent("App");

let make = (~initialSongs: list(song), _children) => {
  ...component,
  initialState: () => {songList: initialSongs, current: None},
  reducer: (action: action, state: state) =>
    /* Js.log(string_of_action(action)); */
    switch (action, state) {
    | (Select(newSong), _) =>
      ReasonReact.Update({
        ...state,
        current: Some({song: newSong, prog: 0.0, text: ""}),
      })
    | (
        UpdateProgress(playedSec),
        {songList: _sl, current: Some({song: s, prog: _p, text: t})},
      ) =>
      /* Js.log2("UpdateProgress: ", playedSec); */
      ReasonReact.Update({
        ...state,
        current: Some({song: s, prog: playedSec, text: t}),
      })
    | (UpdateProgress(_), _) =>
      Js.log("ERROR: UPDATE PROGRESS WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        LeaveComment,
        {songList: sl, current: Some({song: s, prog: p, text: txt})},
      ) =>
      /* Js.log4("LeaveComment: ", s.title, txt, p); */
      let updatedSong = Song.addFeedbackToSong(txt, p, s);
      let updatedState = {
        songList:
          List.map((s': song) => s'.id == s.id ? updatedSong : s', sl),
        current: Some({song: updatedSong, prog: p, text: ""}),
      };
      /* Js.log2("Updated State: ", updatedState); */
      ReasonReact.Update(updatedState);
    | (LeaveComment, _state) =>
      Js.log("ERROR: LEAVE COMMENT WHILE NO SONG PLAYING");
      ReasonReact.NoUpdate;
    | (
        TextChange(txt),
        {songList: _sl, current: Some({song: s, prog: p, text: _t})},
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
    <div className="app">
      <div className=Styles.(appTitle ++ " app-header bold")>
        (Util.str("Lentil"))
      </div>
      <div className="app-menu">
        <Util.Text label="MENU" />
        <Util.Text label="Performer" />
        <Util.Text style="bold" label="Reviewer" />
        <Util.Text label="Settings" />
      </div>
      <div className="app-content">
        (
          Song.renderSongList(
            self.state.songList,
            self.state.current,
            self.send,
          )
        )
      </div>
    </div>,
};