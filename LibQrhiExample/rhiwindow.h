// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QOffscreenSurface>
#include <rhi/qrhi.h>

class RhiWindow : public QWindow
{
public:
    RhiWindow();
    QString graphicsApiName() const;
    void releaseSwapChain();

protected:
    void customInit();
    void customRender();

    void exposeEvent(QExposeEvent *) override;
    bool event(QEvent *) override;

private:
    void init();
    void render();
    void resizeSwapChain();
    void ensureFullscreenTexture(const QSize &pixelSize, QRhiResourceUpdateBatch *u);

    bool m_initialized = false;
    bool m_notExposed = false;
    bool m_newlyExposed = false;
    bool m_hasSwapChain = false;
    
    //! [swapchain-data]
        std::unique_ptr<QRhiSwapChain> m_sc;
        std::unique_ptr<QRhiRenderBuffer> m_ds;
        std::unique_ptr<QRhiRenderPassDescriptor> m_rp;
    //! [swapchain-data]
    std::unique_ptr<QRhi> m_rhi;
    std::unique_ptr<QRhiBuffer> m_vbuf;
    std::unique_ptr<QRhiBuffer> m_ubuf;
    std::unique_ptr<QRhiTexture> m_texture;
    std::unique_ptr<QRhiSampler> m_sampler;
    std::unique_ptr<QRhiShaderResourceBindings> m_colorTriSrb;
    std::unique_ptr<QRhiGraphicsPipeline> m_colorPipeline;
    std::unique_ptr<QRhiShaderResourceBindings> m_fullscreenQuadSrb;
    std::unique_ptr<QRhiGraphicsPipeline> m_fullscreenQuadPipeline;

    QRhiResourceUpdateBatch *m_initialUpdates = nullptr;
    QMatrix4x4 m_viewProjection;
    QVulkanInstance inst;
};

#endif
