import os
import sys
import cgitb

# export LD_LIBRARY_PATH=/home/ubuntu/repo/forward_pass/venv/profile/lib/python3.10/site-packages/taichi/_lib/c_api/lib:$LD_LIBRARY_PATH
# export LD_LIBRARY_PATH=/home/ubuntu/projects/yaml-cpp/build/:$LD_LIBRARY_PATH
# export LD_LIBRARY_PATH=/home/ubuntu/repo/forward_pass/src/qt_aot_renderer_w_cmake/dist/:$LD_LIBRARY_PATH
sys.path.append(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "build/RhiWindow")
)

from PyQt6.QtGui import QGuiApplication, QSurfaceFormat
from PyQt6.QtCore import QCommandLineParser, QCommandLineOption, QLoggingCategory
from RhiWindow import RhiWindow

if __name__ == "__main__":
    cgitb.enable(format="text")

    QLoggingCategory.setFilterRules("qt.vulkan=true")

    app = QGuiApplication(sys.argv)

    cmdLineParser = QCommandLineParser()
    cmdLineParser.addHelpOption()
    vkOption = QCommandLineOption({ "v", "vulkan" }, "Vulkan")
    cmdLineParser.addOption(vkOption)
    cmdLineParser.process(app)

    fmt = QSurfaceFormat()
    fmt.setDepthBufferSize(24)
    fmt.setStencilBufferSize(8)

    QSurfaceFormat.setDefaultFormat(fmt)

    w = RhiWindow()
    w.resize(1280, 720)
    w.setTitle("Test QRhi")
    w.show()

    ret = app.exec()

    if w.handle():
        w.releaseSwapChain()

    sys.exit(ret)
