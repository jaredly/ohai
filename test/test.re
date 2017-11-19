let total = ref(0);

let failed = ref(0);

let check = (x, message) => {
  total := total^ + 1;
  if (x) {
    Printf.printf("PASS: %s\n", message)
  } else {
    Printf.printf("FAIL: %s\n", message);
    failed := failed^ + 1
  }
};

let test_args = () => {
  module Args = Lib.Args;
  let fixtures = [
    ([|"ohai"|], Args.Cmds.NoCmd),
    ([|"ohai", "help"|], Args.Cmds.Help),
    ([|"ohai", "--help"|], Args.Cmds.Help),
    ([|"ohai", "-h"|], Args.Cmds.Help)
  ];
  List.iter(
    ((input, output)) =>
      check(Args.parse(input) == output, String.concat(" ", Array.to_list(input))),
    fixtures
  );
  let init = Args.Init.default;
  let init_fixtures = [
    ([|"ohai", "init", "awesome"|], {...init, name: Some("awesome")}),
    ([|"ohai", "awesome", "-i"|], {...init, name: Some("awesome"), interactive: true}),
    /* No command */
    ([|"ohai", "awesome"|], {...init, name: Some("awesome")}),
    /* Kitchen sink */
    (
      [|"ohai", "-i", "awesome", "--overwrite", "--bin"|],
      {...init, name: Some("awesome"), interactive: true, overwrite: true, bin: true}
    ),
    /* dot */
    ([|"ohai", "."|], init)
  ];
  List.iter(
    ((input, output)) =>
      check(Args.parse(input) == Args.Cmds.Init(output), String.concat(" ", Array.to_list(input))),
    init_fixtures
  )
};

let run = () => {
  test_args();
  if (failed^ != 0) {
    Printf.printf("Failures: %d / %d\n", failed^, total^);
    exit(1)
  } else {
    Printf.printf("All %d tests passed\n", total^);
    exit(0)
  }
};

run();
