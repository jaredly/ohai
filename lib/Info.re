/***
 * This models all of the information needed to make the jbuild & opam files.
 *
 * I've put it in a module `T` to get around ocaml's weird scoping rules for
 * record labels. Basically, in order to use a record, you have to `import *`
 * from the module where it's defined. Now, `import *` is pretty bad for
 * being able to reason about where a given variable etc. was defined, and so
 * I make these very small modules that only contain the type definition.
 * Then, I can do `open Info.T` and I know that I'm only getting what I want
 * -- the record labels.
 */
module T = {
  type t = {
    name: string,
    new_directory: bool,
    version: string,
    maintainer: string,
    reason: bool,
    license: option(string),
    homepage: option(string),
    bug_reports: option(string),
    dev_repo: option(string),
    tags: list(string),
    synopsis: option(string),
    executable: bool
  };
};

let strip_dot_git = (name) =>
  if (String.sub(name, String.length(name) - 4, 4) == ".git") {
    String.sub(name, 0, String.length(name) - 4)
  } else {
    name
  };

let git_homepage = (repo_url) =>
  switch (CCString.split_on_char(':', repo_url)) {
  | ["git@github.com", repo] =>
    let repo = strip_dot_git(repo);
    Some("https://github.com/" ++ repo)
  | _ => None
  };

let git_bug_reports = (repo_url) =>
  switch (git_homepage(repo_url)) {
  | Some(url) => Some(url ++ "/issues")
  | None => None
  };

let get_name = () => Sys.getcwd() |> CCString.split_on_char('/') |> CCList.last_opt;

let git_user = () => {
  let (name, err, ustatus) = CCUnix.call("git config user.name");
  let (email, err, estatus) = CCUnix.call("git config user.email");
  if (ustatus == 0 && estatus == 0) {
    Some(String.trim(name) ++ (" <" ++ (String.trim(email) ++ ">")))
  } else {
    None
  }
};


/***
 * If we're in a git repo w/ a remote origin, we can use that
 * in the opam file.
 */
let find_git_repo = () => {
  let (out, err, status) = CCUnix.call("git remote get-url origin");
  if (status == 0) {
    Some(String.trim(out))
  } else {
    None
  }
};

let default = (args) => {
  open Args.Init;
  let git_repo = find_git_repo();
  let name =
    switch args.name {
    | Some(name) => name
    | None => get_name() |> CCOpt.get_or(~default=args.bin ? "my_cli" : "my_lib")
    };
  let (>>=) = CCOpt.(>>=);
  T.{
    name,
    new_directory: args.name != None,
    version: "1.0.0",
    maintainer: git_user() |> CCOpt.get_or(~default="Unknown"),
    reason: args.reason,
    license: Some("ISC"),
    homepage: git_repo >>= git_homepage,
    bug_reports: git_repo >>= git_bug_reports,
    dev_repo: git_repo,
    executable: args.bin,
    tags: [],
    synopsis: None
  }
};
