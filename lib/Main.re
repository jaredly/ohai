
let info_for opts => {
  open Args.T;
  let default = Info.default opts.bin opts.name;
  if (opts.yes) {
    default
  } else {
    default /* TODO interactive */
  };
};

let run () => {
  let opts = Args.parse (Sys.argv);
  let info = info_for opts;
  let files = Files.generate info;
  print_endline (Opam.build info)
};
