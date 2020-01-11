file(GLOB files_command "command/*.cpp")
file(GLOB files_generator "generator/*.cpp")
file(GLOB files_machine "machine/*.cpp")
file(GLOB files_post "post/*.cpp")
file(GLOB files_project "./*.cpp")
list(REMOVE_ITEM files_generator "generator/test.cpp")

add_library(project ${files_command} ${files_generator} ${files_machine} ${files_project} ${files_post})
