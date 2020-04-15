type t = {
  title: string,
  nextQues: int,
};

let make = (~title, ~nextQues) => {
  title;
  nextQues;
};

let title = t => t.title;
let nextQues = t => t.nextQues;

let makeArray = answers => {
  answers |> Array.map(a => {make(~title=a##title, ~nextQues=a##nextQues)});
};
