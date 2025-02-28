#pragma once

#include <qabstractitemmodel.h>
#include <QString>
#include "Back/Game/PatternList.hpp"


class LexiconGridModel final : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LexiconGridModel(std::vector<pattern>& value, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, const int role = Qt::DisplayRole) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    enum Roles
    {
        GridRole = Qt::UserRole + 1,
    };

public slots:
    [[nodiscard]] QVariant getData(int parentIndex, int gridIndex, int elemIndex,
                                   const int role = Qt::DisplayRole) const noexcept;
    [[nodiscard]] int getLineCountForIndex(int patternIndex, int gridIndex) const noexcept;
    [[nodiscard]] int getColumnCountForIndex(int patternIndex, int gridIndex) const noexcept;
    [[nodiscard]] int getSizeForIndex(int patternIndex, int gridIndex) const noexcept;

private:
    [[nodiscard]] inline bool incomingIndicesInBound(int patternIndex, int gridIndex) const noexcept;

    [[nodiscard]] inline bool elementIndexInBound(int parentIndex, int gridIndex, int index) const noexcept;


    std::vector<std::vector<std::reference_wrapper<board_data>>> _grids;
};

class LexiconDescriptionModel final : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(LexiconGridModel* _gridModel READ get_gridModel CONSTANT)

public:
    explicit LexiconDescriptionModel(std::vector<pattern>& value, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, const int role = Qt::DisplayRole) const override;


    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]] LexiconGridModel* get_gridModel() const noexcept
    {
        return _gridModel.get();
    }

    [[nodiscard]] bool checkIfGridIsntEmpty(int patternId, int gridId) const noexcept
    {
        if (!parentIndexInBound(patternId) || !elementIndexInBound(patternId, gridId))
        {
            return false;
        }
        return _gridModel->getSizeForIndex(patternId, gridId) > 0;
    }

    enum Roles
    {
        DescriptionRole = Qt::UserRole + 1,
    };

public slots:
    [[nodiscard]] int getSizeForIndex(int parentIndex) const noexcept;
    [[nodiscard]] QVariant getData(int parentIndex, int elemIndex,
                                   const int role = Qt::DisplayRole) const noexcept;

private:
    [[nodiscard]] bool parentIndexInBound(int index) const noexcept;

    [[nodiscard]] bool elementIndexInBound(int parentIndex, int index) const noexcept;


    std::vector<std::vector<std::string_view>> _descriptions;
    std::unique_ptr<LexiconGridModel> _gridModel;
};

class LexiconNameModel final : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(LexiconDescriptionModel* _descriptionModel READ get_descriptionModel CONSTANT)

public:
    explicit LexiconNameModel(std::vector<pattern>& refPattern, QObject* parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, const int role = Qt::DisplayRole) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]] LexiconDescriptionModel* get_descriptionModel() const noexcept
    {
        return _descriptionModel.get();
    }

    enum Roles
    {
        NameRole = Qt::UserRole + 1,
    };

private:
    std::vector<std::string_view> _patternNames;
    std::unique_ptr<LexiconDescriptionModel> _descriptionModel;
};
