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
  | AddStock(Types.stock)
  | RemoveStock(string);

let component = ReasonReact.reducerComponent("Main");

module Decode = {
  open Json.Decode;
  let company = json: Types.company => {
    symbol: json |> field("symbol", Json.Decode.string),
    name: json |> field("companyName", Json.Decode.string),
  };

  let stockJson = json: Types.stock => {
    currentPrice: json |> field("price", Json.Decode.float),
    initalPrice: json |> field("price", Json.Decode.float),
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
    | RemoveStock(symbol) => {
      state.stocks 
      -> ArrayLabels.to_list
      -> ListLabels.filter((s) => s.company.symbol !== symbol)
      |> ArrayLabels.of_list
      |> s => ReasonReact.Update({stocks: s})
      }
    },
  render: self =>
    <div className="mw5 center">
      <Search onSubmit={searchStr => self.send(Search(searchStr))} />
      {
          self.state.stocks 
          -> Array.map(x => <StockCard onRemove={(s) => self.send(RemoveStock(s))} company=x.company initalPrice=x.initalPrice/>)
          -> ReasonReact.array
      }
    </div>,
};