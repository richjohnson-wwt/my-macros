#ifndef FAT_SECRET_PRESENTER_H
#define FAT_SECRET_PRESENTER_H

#include "../model/FatSecretWrapper.h"
#include "../view/FatSecretView.h"

class IFatSecretCallback {
public:
    virtual void onRefreshToken() = 0;
    virtual void onSearch(std::string& searchText) = 0;
    // virtual void onGetResult(const std::string& id) = 0;
};

class FatSecretPresenter : public IFatSecretCallback {
private:
    IFatSecretView *m_fatSecretView;
    FatSecretWrapper *m_fatSecretWrapper;

public:
    FatSecretPresenter(IFatSecretView *view, FatSecretWrapper *wrapper);

    void onRefreshToken() override;
    void onSearch(std::string& searchText) override;
    // void onGetResult(const std::string& id) override;
};


#endif // FAT_SECRET_PRESENTER_H