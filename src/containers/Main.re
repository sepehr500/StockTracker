open Belt;

/* type stock = {
     stockSymbol: string,
     stockName: string,
     initalPrice: float,
     currentPrice: float
   }; */


type state = {stocks: array(Types.stock)};

type action =
  | Search(string)
  | AddStock(Types.stock);

let component = ReasonReact.reducerComponent("Main");

/* TODO MAKE JSON DECODE CORRECTLY */
module Decode = {
  open Json.Decode;
  let company = json: Types.company => {
    symbol: json |> field("symbol", Json.Decode.string),
  };

  let stockJson = json: Types.stock => {
    price: json |> field("price", Json.Decode.float),
    company: json |> field("company", company),
  };
};

let buildUrl = (text) => "https://api.iextrading.com/1.0/stock/" ++ text ++"/batch?types=price,company"


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
              text 
              |> buildUrl
              |> Fetch.fetch
              |> then_(Fetch.Response.json) 
              |> then_(json =>
                   json
                   |> Decode.stockJson
                   |> stock => AddStock(stock)
                   |> self.send
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
          -> Array.map(x => <StockCard company=x.company price=x.price />)
          -> ReasonReact.array
      }
    </div>,
};