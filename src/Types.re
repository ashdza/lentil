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

type songList = list(song);
type secs = int;

type playingSong = {
  song,
  progress: secs,
};