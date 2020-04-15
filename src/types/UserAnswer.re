type value =
  | ShortText(string)
  | Number(int)
  | Date(Js.Date.t)
  | MultiChoice(array(AnswerOption.t));

type t = {value: option(value)};

let make = (~value) => {
  value;
};

let value = t => t.value;

let makeDefault = () => {value: None};

let makeShortAnswer = text => {value: Some(ShortText(text))};

let addChoice = choice => {value: Some(MultiChoice(choice))};

// let makeArrayFromJs = (files, checklist) => {
//   checklist
//   |> Js.Array.map(c =>
//        make(
//          ~title=c##title,
//          ~result=makeResult(c##result, c##kind, makeFiles(files)),
//          ~status=makeStatus(c##status),
//        )
//      );
// };

// let decodeFile = json =>
//   Json.Decode.{
//     name: json |> field("name", string),
//     url: json |> field("url", string),
//     id: json |> field("id", string),
//   };

// let decode = (files, json) => {
//   Json.Decode.{
//     result:
//       makeResult(
//         json |> field("result", string),
//         json |> field("kind", string),
//         files,
//       ),
//     status: makeStatus(json |> field("status", string)),
//     title: json |> field("title", string),
//   };

// let encodeKind = t =>
//   switch (t.result) {
//   | ShortText(_) => "shortText"
//   | LongText(_) => "longText"
//   | Link(_) => "link"
//   | Files(_) => "files"
//   | MultiChoice(_) => "multiChoice"
//   };

// let encodeResult = t =>
//   switch (t.result) {
//   | ShortText(t)
//   | LongText(t)
//   | Link(t) => t
//   | MultiChoice(_)
//   | Files(_) => "files"
//   };

// let encodeStatus = t => {
//   switch (t.status) {
//   | NoAnswer => "noAnswer"
//   | Passed => "passed"
//   | Failed => "failed"
//   };
// };

// let encode = t =>
//   Json.Encode.(
//     object_([
//       ("title", t.title |> string),
//       ("kind", encodeKind(t) |> string),
//       ("status", encodeStatus(t) |> string),
//       ("result", encodeResult(t) |> string),
//     ])
//   );

// let encodeArray = checklist => checklist |> Json.Encode.(array(encode));
