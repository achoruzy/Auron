from conan import ConanFile

class AuronPkgs(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("spdlog/1.13.0")
        
    def build_requirements(self):
        self.tool_requires("cmake/[>=3.28]")

    def layout(self):
        self.folders.source = "Auron/Source"
        self.folders.build = "Auron/Binary"