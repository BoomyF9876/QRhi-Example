%Module(name=RhiWindow, keyword_arguments="Optional", use_limited_api=True)

%Import QtCore/QtCoremod.sip
%Import QtWidgets/QtWidgetsmod.sip
%Import QtGui/QtGuimod.sip

%DefaultSupertype sip.simplewrapper

class HelloWindow : public RhiWindow
{
%TypeHeaderCode
#include "rhiwindow.h"
%End
public:
    HelloWindow();

    void customInit() override;
    void customRender() override;

private:
    void ensureFullscreenTexture(const QSize &pixelSize, QRhiResourceUpdateBatch *u);
};
