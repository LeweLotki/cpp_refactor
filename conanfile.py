from conan import ConanFile

class MyProjectConan(ConanFile):
    generators = "CMakeDeps", "CMakeToolchain"
    settings = "os", "compiler", "build_type", "arch"
    name = "cpp_refactor"
    version = "0.0.1"

    requires = [
        "opencv/4.5.2",
    ]
    
    default_options = {
        "libpng/*:shared": True,
        "libwebp/*:shared": True,
        "opencv/*:with_ffmpeg": True,
        "opencv/*:with_gstreamer": True,
    }

    def configure(self):
        self.requires("libpng/1.6.42", override=True)
        self.requires("libwebp/1.3.2", override=True)

