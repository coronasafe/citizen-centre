type t = {
  title: string,
  path: string,
  questions: array(Question.t),
  buttonText: string,
  readMore: string,
  successMessage: string,
  description: string,
  language: string,
  type_: string,
};

let make =
    (
      ~title,
      ~path,
      ~questions,
      ~buttonText,
      ~readMore,
      ~successMessage,
      ~description,
      ~language,
      ~type_,
    ) => {
  {
    title,
    path,
    questions,
    buttonText,
    successMessage,
    readMore,
    description,
    language,
    type_,
  };
};

let title = t => t.title;
let path = t => t.path;
let questions = t => t.questions;
let buttonText = t => t.buttonText;
let readMore = t => t.readMore;
let successMessage = t => t.successMessage;
let description = t => t.description;
let language = t => t.language;
let type_ = t => t.type_;

let makeArray = json => {
  json
  |> Array.map(a =>
       make(
         ~title=a##title,
         ~path=a##path,
         ~questions=a##questions |> Question.makeArray,
         ~buttonText=a##buttonText,
         ~readMore=a##readMore,
         ~successMessage=a##successMessage,
         ~description=a##description,
         ~language=a##language,
         ~type_=a##type_,
       )
     );
};

let findOpt = (path, quiz) => {
  let filteredQuizArray = quiz |> Js.Array.filter(q => q.path == path);
  filteredQuizArray |> ArrayUtils.isEmpty
    ? None : filteredQuizArray |> ArrayUtils.getOpt(0);
};

let filterByLang = (language, quiz) => {
  quiz |> Js.Array.filter(q => q.language == language);
};

let default = quiz => {
  quiz |> filterByLang("malayalam");
};
