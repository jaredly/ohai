
module T = {
  type t = {
    yes: bool,
    name: option string,
    bin: bool,
  };
};

/* TODO add more options probably
// also better args parsing!
// can take inspiration from yarrgs
// put with a ppx to make everything magic
 */
let parse args => switch args {
  | [|_, "-y"|] => T.{yes: true, name: None, bin: true}
  | _ => T.{yes: false, name: None, bin: true}
};

