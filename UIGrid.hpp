#pragma once

#include <QAbstractListModel>

class UIGrid : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(size_t _UILineCount READ get_UILineCount WRITE set_UILineCount NOTIFY _UILineCountChanged FINAL)
    Q_PROPERTY(size_t _UIColumnCount READ get_UIColumnCount WRITE set_UIColumnCount NOTIFY _UIColumnCountChanged FINAL)

    enum Roles {
        ValueRole = Qt::UserRole + 1
    };

public:
    explicit UIGrid(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] inline int get_lineCount() const noexcept{
        return _lineCount;
    }

    [[nodiscard]] inline int get_columnCount() const noexcept{
        return _columnCount;
    }

    [[nodiscard]] inline int get_UILineCount() const noexcept{
        return _UILineCount;
    }

    inline void set_UILineCount(size_t newUILine) noexcept{
        if(_UILineCount !=newUILine)  {
            _UILineCount=newUILine;
            updateFirstLine();
            emit _UILineCountChanged();
        }
    }

    [[nodiscard]] inline int get_UIColumnCount() const noexcept{
        return _UIColumnCount;
    }

    inline void set_UIColumnCount(size_t newUIColumn) noexcept{
        if(_UIColumnCount !=newUIColumn)  {
            _UIColumnCount=newUIColumn;
            updateFirstColumn();
            emit _UIColumnCountChanged();
        }
    }


    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    [[nodiscard]] inline QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[0] = "value";
        return roles;
    }


signals:
    void _UILineCountChanged();
    void _UIColumnCountChanged();


private:

    inline void updateFirstLine() noexcept{
        _gridFirstRow=(_UILineCount - _lineCount) / 2;
    }

    inline void updateFirstColumn() noexcept{
        _gridFirstColumn=(_UIColumnCount - _columnCount) / 2;
    }

    [[nodiscard]] std::optional<size_t> calculateIndexFromUIRow(const QModelIndex &index)const noexcept;

    std::vector<bool> _gridUI{{true, true,true, true,true, true, true , true, true}};
    size_t _columnCount{3};
    size_t _lineCount{3};
    size_t _UILineCount{20};
    size_t _UIColumnCount{40};

    size_t _gridFirstRow{(_UILineCount - _lineCount) / 2};
    size_t _gridFirstColumn{(_UIColumnCount - _columnCount) / 2};
};
