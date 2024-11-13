from conan import ConanFile
from conan.tools.cmake import cmake_layout


class GameOfLifeDependencies(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        # Can't use the conan install because it doesn't include QML
        # self.requires("qt/6.7.3") 
        
        if self.settings.build_type == "Debug":
            self.requires("gtest/1.15.0")
            
    # def layout(self):
    #     cmake_layout(self)