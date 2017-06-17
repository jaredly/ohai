
let run () => {
  let opts = Args.parse (Sys.argv);
  let info = Info.default true;
  print_endline (Opam.build info)
};

