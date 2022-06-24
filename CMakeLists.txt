
project(Raytrace)


set(SOURCES
    main.cpp
    object.cpp
    vec3.cpp
    camera.cpp
    ray.cpp
    sphere.cpp
)


add_executable(${PROJECT_NAME} ${SOURCES})

