cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

get_filename_component(tempVar1 "${output}" DIRECTORY)
if(NOT IS_DIRECTORY "${tempVar1}")
    file(MAKE_DIRECTORY "${tempVar1}")
endif()

file(WRITE "${output}" "")
file(APPEND "${output}" "// command: ${command}\n")
file(APPEND "${output}" "// embed: ${embed}\n")
file(READ "${input}" tempVar1 LIMIT 100 HEX)
file(APPEND "${output}" "\n/*\n")
file(APPEND "${output}" "${tempVar1}")
file(APPEND "${output}" "\n*/\n")
