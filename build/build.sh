name="card game"

source_directory=../src/*.c
include_directory="../include/"
library_directory="../lib"
frameworks=(CoreVideo IOKit Cocoa GLUT OpenGL)

other=(../lib/libraylib.a -g)

for framework in "${frameworks[@]}"; do
  framework_flags+=("-framework" "$framework")
done

clang -o "$name" $source_directory -I $include_directory -L $library_directory "${framework_flags[@]}" "${other[@]}" -std=c11
