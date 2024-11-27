#include "LexiconModel.hpp"


LexiconGridModel::LexiconGridModel(std::vector<pattern>& value, size_t sizePattern,
                                   QObject* parent): QAbstractListModel(parent)
{
    // _grids.reserve(sizePattern);
    _grids.reserve(value.size());
    for (auto& pattern : value)
    {
        std::vector<std::reference_wrapper<board_data>> patt;
        patt.reserve(pattern._descriptionAndPattern.size());

        for (auto& [ignore,grid] : pattern._descriptionAndPattern)
        {
            patt.emplace_back(grid);
        }
        _grids.emplace_back(patt);
    }
}

int LexiconGridModel::rowCount(const QModelIndex& parent) const
{
    return _grids.size();
}

QVariant LexiconGridModel::data(const QModelIndex& index, const int role) const
{
    return {};
}


int LexiconGridModel::getSizeForIndex(int patternIndex, int gridIndex) const noexcept
{
    if (!incomingIndicesInBound(patternIndex, gridIndex)) { return -1; }
    return _grids.at(patternIndex).at(gridIndex).get().grid.size();
}

bool LexiconGridModel::incomingIndicesInBound(int patternIndex, int gridIndex) const noexcept
{
    return patternIndex >= 0 && patternIndex < rowCount() && gridIndex >= 0 && gridIndex < _grids.at(patternIndex).
        size();
}

bool LexiconGridModel::elementIndexInBound(int parentIndex, int gridIndex, int index) const noexcept
{
    return index >= 0 && index < _grids.at(parentIndex).at(gridIndex).get().grid.size();
}

int LexiconGridModel::getLineCountForIndex(int patternIndex, int gridIndex) const noexcept
{
    if (!incomingIndicesInBound(patternIndex, gridIndex)) { return -1; }
    return _grids.at(patternIndex).at(gridIndex).get().line;
}

int LexiconGridModel::getColumnCountForIndex(int patternIndex, int gridIndex) const noexcept
{
    if (!incomingIndicesInBound(patternIndex, gridIndex)) { return -1; }
    return _grids.at(patternIndex).at(gridIndex).get().column;
}

QVariant LexiconGridModel::getData(int parentIndex, int gridIndex, int elemIndex, const int role) const noexcept
{
    if (!incomingIndicesInBound(parentIndex, gridIndex) || !elementIndexInBound(parentIndex, gridIndex, elemIndex))
    {
        return {};
    }
    switch (role)
    {
    case GridRole:
        return _grids.at(parentIndex).at(gridIndex).get().grid.at(elemIndex).get_isCurrentlyAlive();
    default:
        return {};
    }
}


QHash<int, QByteArray> LexiconGridModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GridRole] = "grid";
    return roles;
}


LexiconDescriptionModel::LexiconDescriptionModel(std::vector<pattern>& value, size_t sizePattern,
                                                 QObject* parent): QAbstractListModel(parent),
                                                                   _gridModel(
                                                                       std::make_unique<LexiconGridModel>(
                                                                           value, sizePattern))
{
    _descriptions.reserve(value.size());
    for (auto& pattern : value)
    {
        std::vector<std::string_view> desc;
        desc.reserve(pattern._descriptionAndPattern.size());

        for (auto& [description,grid] : pattern._descriptionAndPattern)
        {
            desc.emplace_back(description);
        }
        _descriptions.emplace_back(desc);
    }
}

int LexiconDescriptionModel::rowCount(const QModelIndex& parent) const
{
    return _descriptions.size();
}

QVariant LexiconDescriptionModel::data(const QModelIndex& index, const int role) const
{
    if (!index.isValid() || static_cast<size_t>(index.row()) >= rowCount())
    {
        return {};
    }
    return {};
}

QVariant LexiconDescriptionModel::getData(int parentIndex, int elemIndex,
                                          const int role) const noexcept
{
    if (!parentIndexInBound(parentIndex) || !elementIndexInBound(parentIndex, elemIndex)) { return {}; }
    switch (role)
    {
    case DescriptionRole:
        return QString(_descriptions.at(parentIndex).at(elemIndex).data());
    default:
        return {};
    }
}


QHash<int, QByteArray> LexiconDescriptionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DescriptionRole] = "description";
    return roles;
}

int LexiconDescriptionModel::getSizeForIndex(int parentIndex) const noexcept
{
    if (!parentIndexInBound(parentIndex)) { return -1; }
    return _descriptions.at(parentIndex).size();
}

bool LexiconDescriptionModel::parentIndexInBound(int index) const noexcept
{
    return index >= 0 && index < rowCount();
}

inline bool LexiconDescriptionModel::elementIndexInBound(int parentIndex, int index) const noexcept
{
    return index >= 0 && index < _descriptions.at(parentIndex).size();
}

LexiconNameModel::LexiconNameModel(std::vector<pattern>& refPattern, size_t sizePattern, QObject* parent) :
    QAbstractListModel(parent), _descriptionModel(std::make_unique<LexiconDescriptionModel>(refPattern, sizePattern))
{
    _patternNames.reserve(refPattern.size());
    for (auto& [_name,ignore] : refPattern)
    {
        _patternNames.emplace_back(_name);
    }
}

int LexiconNameModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _patternNames.size();
}

QVariant LexiconNameModel::data(const QModelIndex& index, const int role) const
{
    if (!index.isValid() || static_cast<size_t>(index.row()) >= rowCount())
    {
        return {};
    }


    switch (role)
    {
    case NameRole:
        return QString(_patternNames.at(index.row()).data());
    default:
        return {};
    }
}

QHash<int, QByteArray> LexiconNameModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}
