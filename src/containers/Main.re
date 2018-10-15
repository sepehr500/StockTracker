open Belt

type stock = {
  stockSymbol: string,
  stockName: string,
  initalPrice: float,
  currentPrice: float
};


type state = {
  stocks: array(stock)
};

type action = Search(string) | AddStock(stock)


let component = ReasonReact.reducerComponent("Main");

/* TODO MAKE JSON DECODE CORRECTLY */
module Decode = {
  let dogs = json =>
    Json.Decode.(
      json |> field("message", array(string)) |> Array.map(_, dog => dog)
    );
};



let make = (_children) => {
  ...component,

  initialState: () => {stocks: [||]},

  reducer: (action: action, state: state) => 
    switch(action){
      | Search(text) => ReasonReact.SideEffects( self => {
        Js.Promise.(
        Fetch.fetch("https://api.iextrading.com/1.0/stock/market/batch?symbols=aapl&types=price,company")
        |> then_(Fetch.Response.text)
        |> then_(price => self.send(
            AddStock({stockSymbol: text, stockName: "", initalPrice: 5.0, currentPrice: 1.0 })
           ) 
          |> resolve)
        )
        |> ignore
      })
    | AddStock(stk) => ReasonReact.Update({stocks: Array.concat(state.stocks, [|stk|])})
  },
  render: self => {
    <div>
        <Search onSubmit=(
          searchStr => self.send(Search(searchStr))
        )/>
    </div>;
  },
};