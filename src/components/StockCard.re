open Types
let component = ReasonReact.statelessComponent("StockCard");

let make = (~initalPrice: float, ~company: company, ~onRemove,  _children) => {
  ...component,
  render: _self =>
  <div className="br2 ba dark-gray b--black-10 mv4 w-100 mw5 center">
    <div>{"Name: " ++ company.name|> ReasonReact.string}</div>
    <div>{"Symbol: " ++ company.symbol |> ReasonReact.string}</div>
    <div>{initalPrice |> string_of_float |> s => "Inital price: " ++ s |> ReasonReact.string} </div>
    <button onClick={_ => onRemove(company.symbol)}>
      {"Remove" |> ReasonReact.string}
    </button>
  </div>
};

