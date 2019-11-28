#!/bin/bash

while IFS= read -r -d '' CMAKE_LIST_FILE; do
  SRC_DIR=$(dirname "${CMAKE_LIST_FILE}")
  BUILD_DIR="./BUILD/${SRC_DIR}"
  rm -rf "${BUILD_DIR}"
  mkdir -p "${BUILD_DIR}"
  cmake -B "${BUILD_DIR}" -G "Ninja" "${SRC_DIR}"
  ninja -C "${BUILD_DIR}"
done < <(find . -type f -name 'CMakeLists.txt' -print0)
