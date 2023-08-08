#ifndef OUTLOOK_PRESENTER_H
#define OUTLOOK_PRESENTER_H



class IOutlookModel;
class IOutlookView;

class IOutlookCallback {
public:

};

class OutlookPresenter : public IOutlookCallback {
private:
    IOutlookModel *m_outlookModel;
    IOutlookView *m_outlookView;

public:
    OutlookPresenter(IOutlookView *view, IOutlookModel *model);

    void postInit();
};

#endif // OUTLOOK_PRESENTER_H