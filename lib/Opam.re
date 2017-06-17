
/* Build an Opam file */

let build info => {
  open Info.T;
  let start = Printf.sprintf
  {|opam-version: "2.0"
name: %S
version: %S
maintainer: %S
authors: [%S]
homepage: %S
bug-reports: %S
dev-repo: %S
license: [%s]
tags: []
build: [["jbuilder" "build" "-p" name "-j" jobs]]
build-test: [["jbuilder" "runtest" "-p" name "-j" jobs]]
depends: [
  "jbuilder" {build}%s
]
|}
  info.name
  info.version
  info.maintainer
  info.maintainer
  (info.homepage |> CCOpt.get_or default::"")
  (info.bug_reports |> CCOpt.get_or default::"")
  (info.dev_repo |> CCOpt.get_or default::"")
  (switch (info.license) {
  | Some s => Printf.sprintf "%S" s
  | None => ""
  })
  (info.reason ? {|
  "reason" {>= "2.0.0"} {build}|} : "");
  start
};