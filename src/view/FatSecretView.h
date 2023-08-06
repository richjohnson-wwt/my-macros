#ifndef FAT_SECRET_VIEW_H
#define FAT_SECRET_VIEW_H

#include "../model/FatSecretModel.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/event.h>
#include <wx/srchctrl.h>
#include "wx/notebook.h"

class IFatSecretCallback;

class IFatSecretView
{
public:
    virtual void setSearchResults(const FatSecret::SearchFoods &searchFoods) = 0;
    virtual void setGetFoodName(const std::string& name) = 0;
    virtual void setGetFoodBrand(const std::string &brand) = 0;
    virtual void setGetFoodCalories(const std::string &calories) = 0;
    virtual void setGetFoodCarb(const std::string &carb) = 0;
    virtual void setGetFoodProtein(const std::string &protein) = 0;
    virtual void setGetFoodFat(const std::string &fat) = 0;
    virtual void setGetFoodMetricServingUnit(const std::string &metricServingUnit) = 0;
    virtual void setGetFoodMetricServingAmount(const std::string &metricServingAmount) = 0;
    virtual void setGetFoodServingDescription(const std::string &servingDescription) = 0;
    virtual void setGetFoodFiber(const std::string &fiber) = 0;
};

class FatSecretView : public wxEvtHandler, public IFatSecretView
{
private:
    IFatSecretCallback *m_fatSecretCallback;

    wxButton *m_refreshTokenButton;

    wxSearchCtrl *m_searchText;
    wxListView *m_searchListView;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text);

protected:
    void onRefreshToken(wxCommandEvent &event);
    void onAddFood(wxCommandEvent &event);

    // Search Section
    void onSearch(wxCommandEvent &event);
    void onSearchCancel(wxCommandEvent &event);
    void onGetResult(wxCommandEvent &event);

    void onAddFoodToMyDatabase(wxCommandEvent &event);

    // Get Food Section
    wxTextCtrl *m_getFoodName;
    wxTextCtrl *m_getFoodBrand;
    wxTextCtrl *m_getFoodCalories;
    wxTextCtrl *m_getFoodCarb;
    wxTextCtrl *m_getFoodProtein;
    wxTextCtrl *m_getFoodFat;
    wxTextCtrl *m_getFoodMetricServingUnit;
    wxTextCtrl *m_getFoodMetricServingAmount;
    wxTextCtrl *m_getFoodServingDescription;
    wxTextCtrl *m_getFoodFiber;

    wxButton *m_addToMyDatabase;

public:
    FatSecretView(IFatSecretCallback *callback);

    wxPanel *createPanel(wxNotebook *parent);

    void setSearchResults(const FatSecret::SearchFoods &searchFoods);
    void setGetFoodName(const std::string& name);
    void setGetFoodBrand(const std::string &brand);
    void setGetFoodCalories(const std::string &calories);
    void setGetFoodCarb(const std::string &carb);
    void setGetFoodProtein(const std::string &protein);
    void setGetFoodFat(const std::string &fat);
    void setGetFoodMetricServingUnit(const std::string &metricServingUnit);
    void setGetFoodMetricServingAmount(const std::string &metricServingAmount);
    void setGetFoodServingDescription(const std::string &servingDescription);
    void setGetFoodFiber(const std::string &fiber);
    
};

#endif // FAT_SECRET_VIEW_H