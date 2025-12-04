%Module(name=RhiWindow, keyword_arguments="Optional", use_limited_api=True)
%DefaultSupertype sip.simplewrapper

%Import QtGui/QtGuimod.sip
%Import QtCore/QtCoremod.sip
%Import QtWidgets/QtWidgetsmod.sip

class RhiWindow : public QWindow
{
%TypeHeaderCode
    #include "rhiwindow.h"
%End
public:
    RhiWindow();

    void handle();
    void releaseSwapChain();
};
