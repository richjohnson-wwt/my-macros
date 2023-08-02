
from conan import ConanFile

class MultiQueue(ConanFile):
    """Deps on RecipeMacros"""
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        """ Deps on RecipeMacros"""
        self.requires("catch2/3.3.2")
        self.requires("fakeit/2.4.0")
        self.requires("spdlog/1.11.0")
        self.requires("cli11/2.3.2")
        self.requires("ccache/4.8.1")
        self.requires("sqlitecpp/3.3.0")
        self.requires("nlohmann_json/3.11.2")

    def build_requirements(self):
        """ Deps on RecipeMacros"""
        self.tool_requires("cmake/3.22.6")