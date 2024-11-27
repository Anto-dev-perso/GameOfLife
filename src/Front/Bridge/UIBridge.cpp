#include "UIBridge.hpp"
#include <QTimer>
#include <QFile>


static const QString LEXICON_RESSOURCE_PATH{":/QtGameOfLife/src/Front/assets/lexicon.txt"};

UIBridge::UIBridge(QObject* parent)
    : QObject(parent)

{
    QFile ressourceFile(LEXICON_RESSOURCE_PATH);
    if (!ressourceFile.open(QIODevice::ReadOnly))
    {
        throw std::ios_base::failure("Failed to open resource file:" + LEXICON_RESSOURCE_PATH.toStdString());
    }

    const QString LEXICON_TMP_FILE_PATH{QCoreApplication::applicationDirPath() + "/lexicon.txt"};
    QFile tmpFile(LEXICON_TMP_FILE_PATH);
    if (!tmpFile.open(QIODevice::WriteOnly))
    {
        throw std::ios_base::failure("Failed to open resource file:" + LEXICON_TMP_FILE_PATH.toStdString());
    }
    tmpFile.write(ressourceFile.readAll());
    ressourceFile.close();
    tmpFile.close();


    _backend = std::make_shared<Game>(LEXICON_TMP_FILE_PATH.toStdString(), TypeOfFileToParse::LEXICON);
    if (!_backend->init())
    {
        throw std::ios_base::failure("Failed to initialize backend");
    }

    QFile::remove(LEXICON_TMP_FILE_PATH);

    _threadProxy = std::make_unique<ThreadProxy>(_backend, calculateWaitTimeFromSlider());

    const auto& [patternsStruct, size] = _backend->get_lexiconPatterns();
    _lexiconNameModel = std::make_unique<LexiconNameModel>(patternsStruct, size);
    _mainGridModel = std::make_unique<MainGridModel>(_backend);


    std::ignore = connect(_threadProxy.get(), &ThreadProxy::iterationNumberFinishedEditing, this,
                          &UIBridge::_iterationNumberChanged);
    std::ignore = connect(_threadProxy.get(), &ThreadProxy::requestModelReset, _mainGridModel.get(),
                          &MainGridModel::resetModel);
    std::ignore = connect(_threadProxy.get(), &ThreadProxy::requestDataChange, _mainGridModel.get(),
                          &MainGridModel::updateData);
}

void UIBridge::changePatternBackEnd(int patternIndex, int gridIndex) const noexcept
{
    // TODO data race here
    _mainGridModel->beginResetGrid();
    _backend->changeBoard(patternIndex, gridIndex);
    _mainGridModel->updateGridCounters();
    _mainGridModel->endResetGrid();
}
