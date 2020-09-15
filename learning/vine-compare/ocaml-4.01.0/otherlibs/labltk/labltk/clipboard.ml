(***********************************************************************)
(*                                                                     *)
(*                 MLTk, Tcl/Tk interface of OCaml                     *)
(*                                                                     *)
(*    Francois Rouaix, Francois Pessaux, Jun Furuse and Pierre Weis    *)
(*               projet Cristal, INRIA Rocquencourt                    *)
(*            Jacques Garrigue, Kyoto University RIMS                  *)
(*                                                                     *)
(*  Copyright 2002 Institut National de Recherche en Informatique et   *)
(*  en Automatique and Kyoto University.  All rights reserved.         *)
(*  This file is distributed under the terms of the GNU Library        *)
(*  General Public License, with the special exception on linking      *)
(*  described in file LICENSE found in the OCaml source tree.          *)
(*                                                                     *)
(***********************************************************************)
open StdLabels
open Tk
open Tkintf
open Widget
open Textvariable

open Protocol
let append ~data:v2 ?displayof:v1 =
clipboard_append_icccm_optionals (fun opts () ->
tkCommand [|TkToken "clipboard";
    TkToken "append";
    TkTokenList (match v1 with
 | Some v1 -> [TkToken "-displayof"; cCAMLtoTKwidget v1]
 | None -> []);
    TkTokenList opts;
    TkToken "--";
    TkToken v2|])

let clear ?displayof:v1 () =
tkCommand [|TkToken "clipboard";
    TkToken "clear";
    TkTokenList (match v1 with
 | Some v1 -> [TkToken "-displayof"; cCAMLtoTKwidget v1]
 | None -> [])|]
