// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QGuiApplication>
#include <QCommandLineParser>
#include "rhiwindow.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QRhi::Implementation graphicsApi;

    // Use platform-specific defaults when no command-line arguments given.

    graphicsApi = QRhi::Vulkan;

    QCommandLineParser cmdLineParser;
    cmdLineParser.addHelpOption();
    QCommandLineOption vkOption({ "v", "vulkan" }, QLatin1String("Vulkan"));
    cmdLineParser.addOption(vkOption);
    cmdLineParser.process(app);

 //! [api-setup]
    // For OpenGL, to ensure there is a depth/stencil buffer for the window.
    // With other APIs this is under the application's control (QRhiRenderBuffer etc.)
    // and so no special setup is needed for those.
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    // Special case macOS to allow using OpenGL there.
    // (the default Metal is the recommended approach, though)
    // gl_VertexID is a GLSL 130 feature, and so the default OpenGL 2.1 context
    // we get on macOS is not sufficient.

    QSurfaceFormat::setDefaultFormat(fmt);

    // For Vulkan.
    QVulkanInstance inst;
    // Request validation, if available. This is completely optional
    // and has a performance impact, and should be avoided in production use.
    inst.setLayers({ "VK_LAYER_KHRONOS_validation" });
    // Play nice with QRhi.
    inst.setExtensions(QRhiVulkanInitParams::preferredInstanceExtensions());
    if (!inst.create()) {
        qWarning("Failed to create Vulkan instance, switching to OpenGL");
        graphicsApi = QRhi::OpenGLES2;
    }

    HelloWindow window;
    window.setVulkanInstance(&inst);
    window.resize(1280, 720);
    window.setTitle(QCoreApplication::applicationName() + QLatin1String(" - ") + window.graphicsApiName());
    window.show();

    int ret = app.exec();

    // RhiWindow::event() will not get invoked when the
    // PlatformSurfaceAboutToBeDestroyed event is sent during the QWindow
    // destruction. That happens only when exiting via app::quit() instead of
    // the more common QWindow::close(). Take care of it: if the QPlatformWindow
    // is still around (there was no close() yet), get rid of the swapchain
    // while it's not too late.
    if (window.handle())
        window.releaseSwapChain();

    return ret;
}
