let str = React.string;
[%bs.raw {|require("./QuizComponent.css")|}];

type page =
  | Quiz
  | Complete;

type state = {
  page,
  quizQuestions: array(Question.t),
  selectedAnswer: option(Answer.t),
  answerInput: string,
  selectedQuestion: int,
};

let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;

let updateAnswer = (setState, answer, _event) => {
  setState(state => {...state, selectedAnswer: Some(answer)});
};

let updateInput = (setState, answerInput) => {
  setState(state => {...state, answerInput: answerInput});
};

let updateUserAnswer = (setState, state) => {
  let question = state.quizQuestions |> ArrayUtils.getOpt(state.selectedQuestion)
  switch(question) {
     | Some(question) => {
       let newQuestion = switch(state.selectedAnswer){
         | Some(answer) => question |> Question.updateAnswer(answer |> Answer.option)
         | None => question |> Question.updateAnswer(state.answerInput)
       }
       setState(state => {
         ...state,
         quizQuestions: state.quizQuestions |> Question.replace(state.selectedQuestion, newQuestion)
       })
     }
     | _ => print_endline("Unhandled Exception")
  }
}

let showAnswerField = question => {
  switch (question |> Question.mode) {
  | "text" =>
    <div className="mt-1 rounded-md shadow-sm">
      <input id="street_address" className="form-input block w-full transition duration-150 ease-in-out sm:text-sm sm:leading-5" />
    </div>
  | "date" =>
    <div className="mt-1 rounded-md shadow-sm">
      <input id="street_address" type_="date" className="form-input block w-full transition duration-150 ease-in-out sm:text-sm sm:leading-5" />
    </div>
  | "select" =>
    <div className="mt-1 rounded-md shadow-sm">
      <select id="country" className="form-select block w-full transition duration-150 ease-in-out sm:text-sm sm:leading-5">
        {question |> Question.answers |> Array.mapi((index,answerOption) => {
            <option>{answerOption |> Answer.option |> str}</option>
          }) |> React.array
        }
      </select>
    </div>
  | _ => React.null
  };
};

let showQuestion =
    (quiz, setState, state, totalQuestions) => {
      <form>
        <div>
          <div className="mt-8 border-t border-gray-200 pt-8">
            {state.quizQuestions |> Array.mapi((index,question) => {
              <div className="sm:col-span-6">
                <label className="block text-sm font-medium leading-5 text-gray-700">
                  {question |> Question.title |> str}
                </label>
                {showAnswerField(question)}
              </div>
              }) |> React.array
            }
          </div>
        </div>
        <div className="mt-8 border-t border-gray-200 pt-5">
          <div className="flex justify-end">
            <span className="inline-flex rounded-md shadow-sm">
              <button type_="button" className="py-2 px-4 border border-gray-300 rounded-md text-sm leading-5 font-medium text-gray-700 hover:text-gray-500 focus:outline-none focus:border-blue-300 focus:shadow-outline-blue active:bg-gray-50 active:text-gray-800 transition duration-150 ease-in-out">
                {"Cancel" |> str}
              </button>
            </span>
            <span className="ml-3 inline-flex rounded-md shadow-sm">
              <button type_="submit" className="inline-flex justify-center py-2 px-4 border border-transparent text-sm leading-5 font-medium rounded-md text-white bg-indigo-600 hover:bg-indigo-500 focus:outline-none focus:border-indigo-700 focus:shadow-outline-indigo active:bg-indigo-700 transition duration-150 ease-in-out">
                {"Save" |> str}
              </button>
            </span>
          </div>
        </div>
      </form>
};

let showSuccess = (quiz, state) => {
  <div className="px-3 md:px-0 py-4 ">
    <div
      className="quiz-component__container border-2 border-gray-800 rounded-lg bg-orange-100 px-6 py-6 md:px-10">
      <h2 className="text-green-600 leading-tight">
        {quiz |> Quiz.successMessage |> str}
      </h2>
      <p>
        {"Your Response:" |> str}
        {state.quizQuestions |> Array.map(question => <p> {question |> Question.userAnswer |> str} </p>) |> React.array}
      </p>
      <a
        href={quiz |> Quiz.readMore}
        target="_blank"
        className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-3">
        {"Read More" |> str}
      </a>
    </div>
    <button
      onClick={_ => ReasonReactRouter.push("/")}
      className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-10">
      <span className="mr-1">
        <svg
          className="w-4"
          xmlns="http://www.w3.org/2000/svg"
          viewBox="0 0 24 24">
          <path
            fill="currentColor"
            d="M23.6 10.12L20.9 8l-8.27-6.46a1 1 0 0 0-1.24 0L3.14 8 .4 10.12a1 1 0 0 0-.18 1.41 1 1 0 0 0 .8.39 1 1 0 0 0 .61-.22l1.13-.88v9a2.84 2.84 0 0 0 2.84 2.84h4.67V12.5h3.48v10.16h4.67a2.84 2.84 0 0 0 2.84-2.84v-9l1.13.88a1 1 0 0 0 .61.22 1 1 0 0 0 .8-.39 1 1 0 0 0-.18-1.42zm-4.37 9.7a.83.83 0 0 1-.83.83h-2.66V11.5a1 1 0 0 0-1-1h-5.5a1 1 0 0 0-1 1v9.16H5.6a.83.83 0 0 1-.83-.83V9.25l3.5-2.74L12 3.6l3.6 2.8 3.63 2.83z"
          />
        </svg>
      </span>
      {"Home" |> str}
    </button>
  </div>;
};

let showQuiz =
    (quiz, setState, state) => {
  let totalQuestions = state.quizQuestions |> Array.length;
  let currentQuestion = state.quizQuestions |> ArrayUtils.getOpt(state.selectedQuestion);
  let isLastQuestion = !(state.selectedQuestion < totalQuestions - 1);

  <div>
    <div>
      {switch (currentQuestion) {
       | Some(question) =>
         showQuestion(
           quiz,
           setState,
           state,
           totalQuestions
         )
       | None => React.null
       }}
    </div>
    <div className="max-w-screen-sm mx-auto">
      <div className="px-3 md:px-0 pb-4">
        {switch (state.selectedAnswer, state.answerInput!="") {
         | (_,true)
         | (Some(_),_)=>
           isLastQuestion
             ? <button
                 onClick={_ => {
                   updateUserAnswer(setState, state);
                   setState(state => {...state, page: Complete})}
                 }
                 className="btn border-2 border-green-600 bg-green-500 text-white hover:bg-green-600 hover:text-white focus:text-white focus:bg-green-600 button-xl w-full">
                 {"Complete" |> str}
               </button>
             : <Link
                 onClick={_ =>{
                   updateUserAnswer(setState, state);
                   setState(state => {
                     ...state,
                     selectedAnswer: None,
                     answerInput: "",
                     selectedQuestion: switch(state.selectedAnswer, state.quizQuestions |> ArrayUtils.getOpt(state.selectedQuestion)){
                                         | (Some(answer), _) =>  answer |> Answer.nextQues
                                         | (_, Some(question)) => question |> Question.nextQues
                                         | _ => 0
                                       }
                  })}
                 }
                 className="btn border-2 border-gray-800 bg-orange-100 hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl w-full">
                 {"Next Question" |> str}
                 <span className="ml-2">
                   <svg
                     className="w-5"
                     xmlns="http://www.w3.org/2000/svg"
                     viewBox="0 0 24 24">
                     <path
                       fill="currentColor"
                       d="M19.92 12.38a1 1 0 0 0 0-.76 1 1 0 0 0-.21-.33l-7-7a1 1 0 0 0-1.42 1.42l5.3 5.3H5a1 1 0 0 0 0 2h11.6l-5.3 5.3a1 1 0 1 0 1.42 1.42l7-7a1 1 0 0 0 .21-.33z"
                     />
                   </svg>
                 </span>
               </Link>
         | (_,_) => React.null
         }}
      </div>
    </div>
  </div>;
};

[@react.component]
let make = (~quiz) => {
  let questions = quiz |> Quiz.questions;
  let (state, setState) = React.useState(() => {selectedAnswer: None, page: Quiz, quizQuestions: questions, selectedQuestion: 0, answerInput: ""});


  <div>
    {switch (state.page) {
     | Quiz => showQuiz(quiz, setState, state)
     | Complete => showSuccess(quiz, state)
     }}
  </div>;
};
