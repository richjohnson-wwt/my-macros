#include "RecipeItemView.h"

#include "../presenter/RecipePresenter.h"

#include <spdlog/spdlog.h>

RecipeItemView::RecipeItemView(IRecipeCallback *callback, RecipeEditView *recipeEditView)
    : m_recipeCallback(callback), m_recipeEditView(recipeEditView)
{
}

wxPanel *RecipeItemView::createRecipeItemPanel(wxNotebook *parent)
{
    spdlog::debug("RecipeItemView::createRecipeItemPanel");
    m_parent = parent;
    wxPanel *topPanel = new wxPanel(parent);

    createRightFoodItemPanel(topPanel);
    spdlog::debug("RecipeItemView::createRecipePanel bye");
    return topPanel;
}

void RecipeItemView::onNotebookPageChanged() {
    spdlog::info("RecipeItemView::onNotebookPageChanged");
    m_recipeCallback->onFocus();
}

void RecipeItemView::setButtonStatus(bool isEdit)
{
    spdlog::info("RecipeItemView::setButtonStatus {}", isEdit);
    m_recipeEditButton->Enable(!isEdit);
    m_recipeNewButton->Enable(!isEdit);
    m_recipeDeleteButton->Enable(!isEdit);
}

wxSizer *RecipeItemView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(200, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_LEFT);
    return sizerRow;
}

void RecipeItemView::createRightFoodItemPanel(wxPanel *panel)
{
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    // Create RecipeID as wxTextCtrl
    m_recipeIdTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe ID:", m_recipeIdTextCtrl), 0, wxALL, 10);

    // Recipe Name wxTextCtrl
    m_recipeNameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Name:", m_recipeNameTextCtrl), 0, wxALL, 10);

    // Recipe Description wxTextCtrl
    m_recipeDescriptionTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Description:", m_recipeDescriptionTextCtrl), 0, wxALL, 10);

    // Recipe URL wxTextCtrl
    m_recipeUrlHyperlinkCtrl = new wxHyperlinkCtrl(panel, wxID_ANY, "Recipe URL", "www.google.com", wxDefaultPosition, wxSize(300, 20));
    wxSizer *urlSizerRow = new wxBoxSizer(wxHORIZONTAL);
    urlSizerRow->Add(new wxStaticText(panel, wxID_ANY, "Url:", wxDefaultPosition, wxSize(200, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    urlSizerRow->Add(m_recipeUrlHyperlinkCtrl, 0, wxALIGN_LEFT);
    topsizer->Add(urlSizerRow, 0, wxALL, 10);
    // topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe URL:", m_recipeUrlHyperlinkCtrl), 0, wxALL, 10);

    // Recipe Servings wxTextCtrl
    m_recipeServingsTextCtrl = new wxTextCtrl(panel, wxID_ANY, "1", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Servings:", m_recipeServingsTextCtrl), 0, wxALL, 10);

    // Recipe Instructions wxTextCtrl
    m_recipeInstructionsTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Instructions:", m_recipeInstructionsTextCtrl), 0, wxALL, 10);

    // Recipe Ingredients - List Ctrl
    m_recipeIngredientsListView = new wxListView(panel);
    m_recipeIngredientsListView->AppendColumn("ID");
    m_recipeIngredientsListView->AppendColumn("Name");
    m_recipeIngredientsListView->AppendColumn("Qty");
    m_recipeIngredientsListView->AppendColumn("Unit");
    m_recipeIngredientsListView->AppendColumn("Multiplier");
    m_recipeIngredientsListView->SetColumnWidth(0, 40);
    m_recipeIngredientsListView->SetColumnWidth(1, 320);
    m_recipeIngredientsListView->SetColumnWidth(2, 100);
    m_recipeIngredientsListView->SetColumnWidth(3, 100);
    m_recipeIngredientsListView->SetColumnWidth(4, 100);
    topsizer->Add(m_recipeIngredientsListView, 4, wxEXPAND | wxALL, 10);

    wxBoxSizer *recipeButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
    m_recipeDeleteButton = new wxButton(panel, -1, _T("Delete"), wxDefaultPosition, wxDefaultSize, 0);
    m_recipeDeleteButton->Bind(wxEVT_BUTTON, &RecipeItemView::onDeleteRecipe, this);
    m_recipeNewButton = new wxButton(panel, -1, _T("New"), wxDefaultPosition, wxDefaultSize, 0);
    m_recipeNewButton->Bind(wxEVT_BUTTON, &RecipeItemView::onNewRecipe, this);

    m_recipeEditButton = new wxButton(panel, -1, _T("Edit"), wxDefaultPosition, wxDefaultSize, 0);
    m_recipeEditButton->Bind(wxEVT_BUTTON, &RecipeItemView::onEditRecipe, this);
    recipeButtonsSizer->Add(m_recipeDeleteButton, 0, wxALL, 10);
    recipeButtonsSizer->Add(m_recipeNewButton, 0, wxALL, 10);
    recipeButtonsSizer->Add(m_recipeEditButton, 0, wxALL, 10);
    topsizer->Add(recipeButtonsSizer, 1, wxALL, 10);

    panel->SetSizer(topsizer);
}

void RecipeItemView::onDeleteRecipe(wxCommandEvent &event)
{
    m_recipeCallback->onDeleteRecipe();
}

void RecipeItemView::insertNewPage(bool isNew)
{
    static unsigned s_pageIns = 0;
    wxPanel *page = m_recipeEditView->createRecipeEditPanel(m_parent);
    if (m_parent) {
        m_parent->InsertPage( 0, page,
                wxString::Format("NEWBIE" "%u", ++s_pageIns), false, 0 );

        m_parent->SetSelection(0);
        m_recipeEditView->initNewPage(isNew);
    } else {
        spdlog::error("RecipeItemView::insertNewPage: m_parent is null");
    }
}

void RecipeItemView::onNewRecipe(wxCommandEvent &event)
{
    m_recipeCallback->onNewRecipe();
}

void RecipeItemView::onEditRecipe(wxCommandEvent &event)
{
    m_recipeCallback->onEditRecipe();
}

void RecipeItemView::setRecipeId(const std::string &id)
{
    m_recipeIdTextCtrl->SetValue(id);
}

void RecipeItemView::setRecipeName(const std::string &name)
{
    m_recipeNameTextCtrl->SetValue(name);
}

void RecipeItemView::setRecipeDescription(const std::string &description)
{
    m_recipeDescriptionTextCtrl->SetValue(description);
}

void RecipeItemView::setRecipeUrl(const std::string &url)
{
    m_recipeUrlHyperlinkCtrl->SetURL(url);
    m_recipeUrlHyperlinkCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    m_recipeUrlHyperlinkCtrl->SetForegroundColour(wxColor(255, 255, 255));
}

void RecipeItemView::setRecipeServings(const std::string &servings)
{
    m_recipeServingsTextCtrl->SetValue(servings);
}

void RecipeItemView::setRecipeInstructions(const std::string &instructions)
{
    m_recipeInstructionsTextCtrl->SetValue(instructions);
}

void RecipeItemView::setRecipeIngredients(const std::vector<Ingredient> &ingredients)
{
    m_recipeIngredientsListView->DeleteAllItems();
    int row = 0;
    for (auto i : ingredients)
    {
        wxLogMessage("RecipePanel::update Add ingredient: %s", i.food.name);

        m_recipeIngredientsListView->InsertItem(row, std::to_string(i.food.id));
        m_recipeIngredientsListView->SetItem(row, 1, i.food.name);
        m_recipeIngredientsListView->SetItem(row, 2, wxString(std::to_string(i.food.quantity)));
        m_recipeIngredientsListView->SetItem(row, 3, i.unit.name);
        m_recipeIngredientsListView->SetItem(row, 4, std::to_string(i.unitMultiplier));
        row++;
    }
}
