file(REMOVE_RECURSE
  "libMain.pdb"
  "libMain.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/Main.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
