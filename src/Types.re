[%%debugger.chrome];

type comment = string;

type feedbackLocation = float;

type feedback = {
  location: feedbackLocation,
  comment,
};

type song = {
  id: int,
  title: string,
  artist: string,
  url: string,
  comments: list(feedback),
};

type songInProgress = {
  song,
  prog: float,
  text: string,
};

type state = {
  songList: list(song),
  current: option(songInProgress),
};

type action =
  | Select(song)
  | UpdateProgress(float)
  | LeaveComment
  | TextChange(string);