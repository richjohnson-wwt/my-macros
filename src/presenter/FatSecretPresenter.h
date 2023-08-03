#ifndef FAT_SECRET_PRESENTER_H
#define FAT_SECRET_PRESENTER_H

class IFatSecretCallback {
public:
    virtual void onFoodFatSecretBookPageChanged() = 0;
};

class FatSecretPresenter : public IFatSecretCallback {
public:
    void onFoodFatSecretBookPageChanged() override;
};


#endif // FAT_SECRET_PRESENTER_H