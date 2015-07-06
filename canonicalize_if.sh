#! /bin/bash
set -e
set -x
set -v
./clang_compile.sh canonicalize_if.cc clang_utility_functions.cc if_stmt_handler.cc
mv a.out canonicalize_if

# Iterate till a fixed point
while [ 1 -lt 2 ] ;
do
  cp $1 old.cc
  ./canonicalize_if $1 -- > repl.yaml
  clang-apply-replacements .
  cp $1 new.cc
  if diff old.cc new.cc;
  then
    break;
  else
    continue;
  fi
done

rm repl.yaml old.cc new.cc
clang-format-3.5 -i $1
