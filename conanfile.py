# Copyright (C) Auron Project by Arkadiusz Choruzy
# All rights reserved.

from conan import ConanFile

class AuronPkgs(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("spdlog/1.13.0")
        self.requires("opengl/system")
        self.requires("glew/2.2.0")
        self.requires("glfw/3.4")
        # self.requires("glm/cci.20230113")
        # self.requires("imgui/cci.20230105+1.89.2.docking")
        # self.requires("assimp/5.3.1")
        # self.requires("openimageio/2.5.10.1")
        # self.requires("openal-soft/1.23.1")
        
    def build_requirements(self):
        self.tool_requires("cmake/[>=3.28]")

    def layout(self):
        self.folders.source = "Auron/Source"
        self.folders.build = "Auron/Binary"