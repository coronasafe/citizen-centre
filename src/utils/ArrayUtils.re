exception UnsafeFindFailed(string);

let copyAndSort = (f, t) => {
  let cp = t |> Array.copy;
  cp |> Array.sort(f);
  cp;
};

let copyAndPush = (e, t) => {
  let copy = t |> Array.copy;
  copy |> Js.Array.push(e) |> ignore;
  copy;
};

let isEmpty = a =>
  switch (a) {
  | [||] => true
  | _ => false
  };

let isNotEmpty = a => !(a |> isEmpty);

let flatten = t => {
  t |> Array.to_list |> List.flatten |> Array.of_list;
};

let sort_uniq = (f, t) =>
  t |> Array.to_list |> List.sort_uniq(f) |> Array.of_list;

let getOpt = (a, i) =>
  try(Some(a |> Array.get(i))) {
  | Not_found => None
  };
