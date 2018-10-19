open Belt;

/* type stock = {
     stockSymbol: string,
     stockName: string,
     initalPrice: float,
     currentPrice: float
   }; */

type company = {symbol: string};

type stock = {
  price: float,
  company,
};

type state = {stocks: array(stock)};

type action =
  | Search(string)
  | AddStock(stock);

let component = ReasonReact.reducerComponent("Main");

/* TODO MAKE JSON DECODE CORRECTLY */
module Decode = {
  open Json.Decode;
  let company = json: company => {
    symbol: json |> field("symbol", Json.Decode.string),
  };

  let stockJson = json: stock => {
    price: json |> field("price", Json.Decode.float),
    company: json |> field("company", company),
  };
};

let make = _children => {
  ...component,

  initialState: () => {stocks: [||]},

  reducer: (action: action, state: state) =>
    switch (action) {
    | Search(text) =>
      ReasonReact.SideEffects(
        (
          self =>
            Js.Promise.(
              Fetch.fetch(
                "https://api.iextrading.com/1.0/stock/" ++ text ++"/batch?types=price,company",
              )
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> Decode.stockJson
                   |> (stock => self.send(AddStock(stock)))
                   |> resolve
                 )
            )
            |> ignore
        ),
      )
    | AddStock(stock) =>
      ReasonReact.Update({stocks: Array.concat(state.stocks, [|stock|])})
    },
  render: self =>
    <div>
      <Search onSubmit={searchStr => self.send(Search(searchStr))} />
      {
          self.state.stocks 
          |> Array.map(_, x => 
            <div> { x.price |> string_of_float |> ReasonReact.string} </div>) 
          |> ReasonReact.array
      }
    </div>,
};