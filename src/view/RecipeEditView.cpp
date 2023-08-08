#include "RecipeEditView.h"

#include "../presenter/RecipeEditPresenter.h"

#include <spdlog/spdlog.h>

RecipeEditView::RecipeEditView(IRecipeEditCallback *callback)
    : m_recipeEditCallback(callback)
{
}

wxSizer *RecipeEditView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(200, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_LEFT);
    return sizerRow;
}

wxPanel *RecipeEditView::createRecipeEditPanel(wxNotebook *parent)
{
    spdlog::debug("RecipeEditView::createRecipePanel");
    m_parent = parent;
    wxPanel *panel = new wxPanel(parent);

    // createRightFoodItemPanel(topPanel);
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    // Create RecipeID as wxTextCtrl
    m_recipeIdTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe ID:", m_recipeIdTextCtrl), 0, wxALL, 10);

    // Recipe Name wxTextCtrl
    m_recipeNameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Name:", m_recipeNameTextCtrl), 0, wxALL, 10);

    // Recipe Description wxTextCtrl
    m_recipeDescriptionTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Description:", m_recipeDescriptionTextCtrl), 0, wxALL, 10);

    // Recipe URL wxTextCtrl
    m_recipeUrlHyperlinkCtrl = new wxHyperlinkCtrl(panel, wxID_ANY, "Recipe URL", "www.google.com", wxDefaultPosition, wxSize(300, 20));
    wxSizer *urlSizerRow = new wxBoxSizer(wxHORIZONTAL);
    urlSizerRow->Add(new wxStaticText(panel, wxID_ANY, "Url:", wxDefaultPosition, wxSize(200, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    urlSizerRow->Add(m_recipeUrlHyperlinkCtrl, 0, wxALIGN_LEFT);
    topsizer->Add(urlSizerRow, 0, wxALL, 10);

    // Recipe Servings wxTextCtrl
    m_recipeServingsTextCtrl = new wxTextCtrl(panel, wxID_ANY, "1", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Servings:", m_recipeServingsTextCtrl), 0, wxALL, 10);

    // Recipe Instructions wxTextCtrl
    m_recipeInstructionsTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Instructions:", m_recipeInstructionsTextCtrl), 0, wxALL, 10);

    wxBoxSizer *ingredientButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
    m_addRecipeIngredientButton = new wxButton(panel, -1, _T("Add Food With Multiplier"), wxDefaultPosition, wxDefaultSize, 0);
    m_addRecipeIngredientButton->Bind(wxEVT_BUTTON, &RecipeEditView::onAddIngredient, this);

    m_recipeIngredientMultiplierTextCtrl = new wxTextCtrl(panel, wxID_ANY, "1", wxDefaultPosition, wxSize(200, 20));
    ingredientButtonsSizer->Add(m_addRecipeIngredientButton, 0, wxALL, 10);
    ingredientButtonsSizer->Add(m_recipeIngredientMultiplierTextCtrl, 0, wxALL, 10);
    topsizer->Add(ingredientButtonsSizer, 0, wxALL, 10);

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
    m_recipeIngredientsListView->Bind(wxEVT_LIST_ITEM_SELECTED, &RecipeEditView::onIngredientSelChange, this);
    topsizer->Add(m_recipeIngredientsListView, 5, wxEXPAND | wxALL, 10);

    m_deleteRecipeIngredientButton = new wxButton(panel, -1, _T("Delete Selected Ingredient"), wxDefaultPosition, wxDefaultSize, 0);
    m_deleteRecipeIngredientButton->Bind(wxEVT_BUTTON, &RecipeEditView::onDeleteIngredient, this);
    topsizer->Add(m_deleteRecipeIngredientButton, 1, wxALL, 10);

    wxBoxSizer *recipeButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
    m_recipeSaveButton = new wxButton(panel, -1, _T("Save"), wxDefaultPosition, wxDefaultSize, 0);
    m_recipeSaveButton->Bind(wxEVT_BUTTON, &RecipeEditView::onSaveRecipe, this);
    m_recipeCancelNewButton = new wxButton(panel, -1, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
    m_recipeCancelNewButton->Bind(wxEVT_BUTTON, &RecipeEditView::onCancelNewRecipe, this);
    recipeButtonsSizer->Add(m_recipeSaveButton, 0, wxALL, 10);
    recipeButtonsSizer->Add(m_recipeCancelNewButton, 0, wxALL, 10);
    topsizer->Add(recipeButtonsSizer, 0, wxALL, 10);

    panel->SetSizer(topsizer);
    spdlog::debug("RecipeEditView::createRecipePanel bye");
    return panel;
}


// void RecipeEditView::createRightFoodItemPanel(wxPanel *panel)
// {
//     wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

//     // Create RecipeID as wxTextCtrl
//     m_recipeIdTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
//     topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe ID:", m_recipeIdTextCtrl), 0, wxALL, 10);

//     // Recipe Name wxTextCtrl
//     m_recipeNameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
//     topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Name:", m_recipeNameTextCtrl), 0, wxALL, 10);

//     // Recipe Description wxTextCtrl
//     m_recipeDescriptionTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
//     topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Description:", m_recipeDescriptionTextCtrl), 0, wxALL, 10);

//     // Recipe URL wxTextCtrl
//     m_recipeUrlHyperlinkCtrl = new wxHyperlinkCtrl(panel, wxID_ANY, "Recipe URL", "www.google.com", wxDefaultPosition, wxSize(300, 20));
//     wxSizer *urlSizerRow = new wxBoxSizer(wxHORIZONTAL);
//     urlSizerRow->Add(new wxStaticText(panel, wxID_ANY, "Url:", wxDefaultPosition, wxSize(200, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
//     urlSizerRow->Add(m_recipeUrlHyperlinkCtrl, 0, wxALIGN_LEFT);
//     topsizer->Add(urlSizerRow, 0, wxALL, 10);

//     // Recipe Servings wxTextCtrl
//     m_recipeServingsTextCtrl = new wxTextCtrl(panel, wxID_ANY, "1", wxDefaultPosition, wxSize(200, 20));
//     topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Servings:", m_recipeServingsTextCtrl), 0, wxALL, 10);

//     // Recipe Instructions wxTextCtrl
//     m_recipeInstructionsTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
//     topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Instructions:", m_recipeInstructionsTextCtrl), 0, wxALL, 10);

//     wxBoxSizer *ingredientButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
//     m_addRecipeIngredientButton = new wxButton(panel, -1, _T("Add Food With Multiplier"), wxDefaultPosition, wxDefaultSize, 0);
//     m_addRecipeIngredientButton->Bind(wxEVT_BUTTON, &RecipeEditView::onAddIngredient, this);

//     m_recipeIngredientMultiplierTextCtrl = new wxTextCtrl(panel, wxID_ANY, "1", wxDefaultPosition, wxSize(200, 20));
//     ingredientButtonsSizer->Add(m_addRecipeIngredientButton, 0, wxALL, 10);
//     ingredientButtonsSizer->Add(m_recipeIngredientMultiplierTextCtrl, 0, wxALL, 10);
//     topsizer->Add(ingredientButtonsSizer, 0, wxALL, 10);

//     // Recipe Ingredients - List Ctrl
//     m_recipeIngredientsListView = new wxListView(panel);
//     m_recipeIngredientsListView->AppendColumn("ID");
//     m_recipeIngredientsListView->AppendColumn("Name");
//     m_recipeIngredientsListView->AppendColumn("Qty");
//     m_recipeIngredientsListView->AppendColumn("Unit");
//     m_recipeIngredientsListView->AppendColumn("Multiplier");
//     m_recipeIngredientsListView->SetColumnWidth(0, 40);
//     m_recipeIngredientsListView->SetColumnWidth(1, 320);
//     m_recipeIngredientsListView->SetColumnWidth(2, 100);
//     m_recipeIngredientsListView->SetColumnWidth(3, 100);
//     m_recipeIngredientsListView->SetColumnWidth(4, 100);
//     m_recipeIngredientsListView->Bind(wxEVT_LIST_ITEM_SELECTED, &RecipeEditView::onIngredientSelChange, this);
//     topsizer->Add(m_recipeIngredientsListView, 5, wxEXPAND | wxALL, 10);

//     m_deleteRecipeIngredientButton = new wxButton(panel, -1, _T("Delete Selected Ingredient"), wxDefaultPosition, wxDefaultSize, 0);
//     m_deleteRecipeIngredientButton->Bind(wxEVT_BUTTON, &RecipeEditView::onDeleteIngredient, this);
//     topsizer->Add(m_deleteRecipeIngredientButton, 1, wxALL, 10);

//     wxBoxSizer *recipeButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
//     m_recipeSaveButton = new wxButton(panel, -1, _T("Save"), wxDefaultPosition, wxDefaultSize, 0);
//     m_recipeSaveButton->Bind(wxEVT_BUTTON, &RecipeEditView::onSaveRecipe, this);
//     m_recipeCancelNewButton = new wxButton(panel, -1, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
//     m_recipeCancelNewButton->Bind(wxEVT_BUTTON, &RecipeEditView::onCancelNewRecipe, this);
//     recipeButtonsSizer->Add(m_recipeSaveButton, 0, wxALL, 10);
//     recipeButtonsSizer->Add(m_recipeCancelNewButton, 0, wxALL, 10);
//     topsizer->Add(recipeButtonsSizer, 0, wxALL, 10);

//     panel->SetSizer(topsizer);
// }

void RecipeEditView::initNewPage(bool isNew) {
    if (isNew) {
        spdlog::info("RecipeEditView::initNewPage");
        m_recipeEditCallback->initNewPage();
    } else {
        spdlog::info("RecipeEditView::initEditPage");
        m_recipeEditCallback->initEditPage();
    }
}

void RecipeEditView::deleteThisPage()
{
    if ( m_parent )
    {
        int sel = m_parent->GetSelection();

        if (sel != wxNOT_FOUND)
        {
            m_parent->DeletePage(sel);
            m_parent->SetSelection(0);
        }
    }
}

void RecipeEditView::onSaveRecipe(wxCommandEvent &event)
{
    if (m_recipeNameTextCtrl->GetValue().ToStdString() == "")
    {
        wxMessageBox("Recipe name is required");
    }
    else if (m_recipeIngredientsListView->GetItemCount() == 0)
    {
        wxMessageBox("Recipe must have at least one ingredient");
    }
    else
    {
        m_recipeEditCallback->onSaveRecipe();
        deleteThisPage();
    }
}

void RecipeEditView::onCancelNewRecipe(wxCommandEvent &event)
{
    m_recipeEditCallback->onCancelNewRecipe();
    deleteThisPage();
}

void RecipeEditView::onAddIngredient(wxCommandEvent &event)
{
    double unitMultiplier = std::stod(m_recipeIngredientMultiplierTextCtrl->GetValue().ToStdString());
    m_recipeEditCallback->onAddIngredient(unitMultiplier);
}

void RecipeEditView::onDeleteIngredient(wxCommandEvent &event)
{
    m_recipeEditCallback->onDeleteIngredient();
}

void RecipeEditView::onIngredientSelChange(wxListEvent &event)
{
    int id = wxAtoi(event.GetText());
    m_recipeEditCallback->onSelectIngredient(id);
}

void RecipeEditView::setRecipeId(const std::string &id)
{
    m_recipeIdTextCtrl->SetValue(id);
}

void RecipeEditView::setRecipeName(const std::string &name)
{
    m_recipeNameTextCtrl->SetValue(name);
}

void RecipeEditView::setRecipeDescription(const std::string &description)
{
    m_recipeDescriptionTextCtrl->SetValue(description);
}

void RecipeEditView::setRecipeUrl(const std::string &url)
{
    m_recipeUrlHyperlinkCtrl->SetURL(url);
    m_recipeUrlHyperlinkCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    m_recipeUrlHyperlinkCtrl->SetForegroundColour(wxColor(255, 255, 255));
}

void RecipeEditView::setRecipeServings(const std::string &servings)
{
    m_recipeServingsTextCtrl->SetValue(servings);
}

void RecipeEditView::setRecipeInstructions(const std::string &instructions)
{
    m_recipeInstructionsTextCtrl->SetValue(instructions);
}

void RecipeEditView::setRecipeIngredients(const std::vector<Ingredient> &ingredients)
{
    m_recipeIngredientsListView->DeleteAllItems();
    int row = 0;
    for (auto i : ingredients)
    {
        spdlog::debug("RecipePanel::update Add ingredient: {}", i.food.name);

        m_recipeIngredientsListView->InsertItem(row, std::to_string(i.food.id));
        m_recipeIngredientsListView->SetItem(row, 1, i.food.name);
        m_recipeIngredientsListView->SetItem(row, 2, wxString(std::to_string(i.food.quantity)));
        m_recipeIngredientsListView->SetItem(row, 3, i.unit.name);
        m_recipeIngredientsListView->SetItem(row, 4, std::to_string(i.unitMultiplier));
        row++;
    }
}

void RecipeEditView::setRecipeIngredientMultiplier(const std::string &multiplier)
{
    m_recipeIngredientMultiplierTextCtrl->SetValue(multiplier);
}

int RecipeEditView::getRecipeId()
{
    return std::stoi(m_recipeIdTextCtrl->GetValue().ToStdString());
}

std::string RecipeEditView::getRecipeName()
{
    return m_recipeNameTextCtrl->GetValue().ToStdString();
}

std::string RecipeEditView::getRecipeDescription()
{
    return m_recipeDescriptionTextCtrl->GetValue().ToStdString();
}

std::string RecipeEditView::getRecipeUrl()
{
    return m_recipeUrlHyperlinkCtrl->GetURL().ToStdString();
}

std::string RecipeEditView::getRecipeServings()
{
    return m_recipeServingsTextCtrl->GetValue().ToStdString();
}

std::string RecipeEditView::getRecipeInstructions()
{
    return m_recipeInstructionsTextCtrl->GetValue().ToStdString();
}
