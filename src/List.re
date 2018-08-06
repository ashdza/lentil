type intList =
  | Null
  | Cons(int, intList);

type stringList =
  | Null
  | Cons(string, stringList);

type songList =
  | Null
  | Cons(Types.song, songList);

type list('t) =
  | Null
  | Cons('t, list('t));

type selectable('t) =
  | Null
  | Selected('t);