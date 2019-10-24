#!/bin/bash



while IFS= read -r -d '' CMAKE_LIST_FILE; do
  SRC_DIR=$(dirname "${CMAKE_LIST_FILE}")
  BUILD_DIR="./BUILD/${SRC_DIR}"
  mkdir -p "${BUILD_DIR}"
  cmake -B "${BUILD_DIR}" "${SRC_DIR}"
  make -C "${BUILD_DIR}"
done < <(find . -type f -name 'CMakeLists.txt' -print0)
