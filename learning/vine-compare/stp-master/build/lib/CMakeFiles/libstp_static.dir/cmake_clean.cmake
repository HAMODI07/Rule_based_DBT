file(REMOVE_RECURSE
  "libstp.pdb"
  "libstp.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/libstp_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
