#!/bin/bash
cmake -B build && cmake --build build &&

if [[ -x ./build/GraphWars ]]; then
  echo "========== GraphWars Debug Console =========="
  ./build/GraphWars
  echo "============== Program Exited =============="
fi
