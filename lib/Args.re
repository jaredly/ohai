
module T = {
  type t = {
    yes: bool,
  };
};

/* TODO add more options probably
// also better args parsing!
// can take inspiration from yarrgs
// put with a ppx to make everything magic
 */
let parse args => switch args {
  | [|_, "-y"|] => T.{yes: true}
  | _ => T.{yes: false}
};

