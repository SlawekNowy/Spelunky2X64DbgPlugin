#pragma once

#include "Data/CharacterDB.h"
#include "QtHelpers/StyledItemDelegateHTML.h"
#include "QtHelpers/TreeViewMemoryFields.h"
#include "ViewToolbar.h"
#include <QCheckBox>
#include <QComboBox>
#include <QCompleter>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>

namespace S2Plugin
{
    class ViewCharacterDB : public QWidget
    {
        Q_OBJECT
      public:
        ViewCharacterDB(ViewToolbar* toolbar, size_t index = 0, QWidget* parent = nullptr);
        void showIndex(size_t index);

      protected:
        void closeEvent(QCloseEvent* event) override;
        QSize sizeHint() const override;
        QSize minimumSizeHint() const override;

      private slots:
        void searchFieldReturnPressed();
        void searchFieldCompleterActivated(const QString& text);
        void label();
        void fieldUpdated(const QString& fieldName);
        void fieldExpanded(const QModelIndex& index);
        void comparisonFieldChosen(const QString& fieldName);
        void compareGroupByCheckBoxClicked(int state);
        void comparisonCellClicked(int row, int column);
        void groupedComparisonItemClicked(QTreeWidgetItem* item, int column);

      private:
        ViewToolbar* mToolbar;
        std::unique_ptr<StyledItemDelegateHTML> mHTMLDelegate;

        QVBoxLayout* mMainLayout;
        QTabWidget* mMainTabWidget;
        QWidget* mTabLookup;
        QWidget* mTabCompare;

        // LOOKUP
        size_t mLookupIndex;
        TreeViewMemoryFields* mMainTreeView;
        QLineEdit* mSearchLineEdit;
        QCompleter* mCharacterNameCompleter;

        // COMPARE
        QComboBox* mCompareFieldComboBox;
        QTableWidget* mCompareTableWidget;
        QTreeWidget* mCompareTreeWidget;

        void initializeUI();
        void updateFieldValues();
        void populateComparisonTableWidget();
        void populateComparisonTreeWidget();
        std::pair<QString, QVariant> valueForField(const MemoryField& field, size_t characterDBIndex);
    };
} // namespace S2Plugin
