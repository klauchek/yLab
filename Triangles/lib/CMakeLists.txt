set(LIBLIST
  common
  intersection
  primitives
)

foreach(LIB ${LIBLIST})
  add_subdirectory(${LIB})
endforeach()

set(LIBLIST "${LIBLIST}" PARENT_SCOPE)