target_sources(${EXPERT_SYSTEM_LIB} PUBLIC
        ExpertSystem.cpp
        ExpertSystemData.cpp
        Visualizer.cpp
        )

add_subdirectory(Expressions)
add_subdirectory(Parse)