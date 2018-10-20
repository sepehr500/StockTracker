open Types
let component = ReasonReact.statelessComponent("StockCard");

let make = (~price, ~company: company, _children) => {
  ...component,
  render: _self =>
  <div>
    <div>{company.symbol ++ "  " |> ReasonReact.string}
     { price |> string_of_float |> ReasonReact.string} </div>
  </div>
};

