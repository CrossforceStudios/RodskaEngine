@echo off

echo "Setting up dependencies..."
pushd ..\..\
    echo "1) GLFW"
    git clone https://github.com/TheCherno/GLFW RodskaEngine/vendor/GLFW
    echo "2) imgui"
    git clone https://github.com/CrossforceStudios/imgui RodskaEngine/vendor/imgui
    echo "3) glm"
    git clone https://github.com/CrossforceStudios/glm RodskaEngine/vendor/glm
    echo "4) tinyobjloader"
    git clone https://github.com/CrossforceStudios/tinyobjloader RodskaEngine/vendor/tinyobjloader
    echo "5) yaml-cpp"
    git clone https://github.com/CrossforceStudios/yaml-cpp RodskaEngine/vendor/yaml-cpp
    echo "6) spdlog"
    git clone git://github.com/gabime/spdlog.git RodskaEngine/vendor/spdlog
    echo "7) DirectXTK"
    git clone https://github.com/Microsoft/DirectXTK RodskaEngine/vendor/DirectXTK
    echo "8) ImGuizmo"
    echo git clone https://github.com/CedricGuillemet/ImGuizmo RodskaEngine/vendor/ImGuizmo
    echo "9) Zipped Dependencies"
    SetupZippedDeps.bat
    echo "Done."
popd
pause