# Add Target
ADD_EXECUTABLE (nezumi-sample "source/main.c")

# Add Target Libraries
TARGET_LINK_LIBRARIES (nezumi-sample PRIVATE nezumi-runtime)