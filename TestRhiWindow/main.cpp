// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QGuiApplication>
#include <QLoggingCategory>
#include <QCommandLineParser>
#include "rhiwindow.h"

const QString SHADER_PATH = "/home/ubuntu/projects/RhiExample_6.8.3/QRhi-Example/LibQrhiExample/shaders/prebuilt/";

int main(int argc, char **argv)
{
    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    QGuiApplication app(argc, argv);

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

    RhiWindow window(SHADER_PATH);
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
