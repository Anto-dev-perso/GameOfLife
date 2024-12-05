#include "UIBridge.hpp"
#include <QTimer>
#include <QFile>

#include "MainGridImageProvider.hpp"


static const QString LEXICON_RESSOURCE_PATH{":/QtGameOfLife/src/Front/assets/lexicon.txt"};

UIBridge::UIBridge(QObject* parent)
    : QObject(parent)
{
}

void UIBridge::initialize(QQmlEngine* engine)
{
    QFile ressourceFile{LEXICON_RESSOURCE_PATH};
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

    auto back = std::make_shared<Game>(LEXICON_TMP_FILE_PATH.toStdString(), TypeOfFileToParse::LEXICON);
    if (!back->init())
    {
        throw std::ios_base::failure("Failed to initialize backend");
    }

    QFile::remove(LEXICON_TMP_FILE_PATH);

    _threadProxy = std::make_unique<ThreadProxy>(back, calculateWaitTimeFromSlider());

    const auto& [patternsStruct, size] = back->get_lexiconPatterns();
    _lexiconNameModel = std::make_unique<LexiconNameModel>(patternsStruct, size);

    if (engine)
    {
        _mainGridImageProvider = new MainGridImageProvider(back);
        engine->addImageProvider(IMAGE_PROVIDER_NAME, _mainGridImageProvider);
    }

    std::ignore = connect(_threadProxy.get(), &ThreadProxy::iterationNumberFinishedEditing, this,
                          &UIBridge::_iterationNumberChanged);
    std::ignore = connect(_threadProxy.get(), &ThreadProxy::requestModelReset, this,
                          &UIBridge::reDrawEntirely);
    std::ignore = connect(_threadProxy.get(), &ThreadProxy::requestDataChange, this,
                          &UIBridge::updateCells);
}

void UIBridge::changePatternBackEnd(int patternIndex, int gridIndex) noexcept
{
    // TODO data race here
    _mainGridImageProvider->changeMainGridWithPatternIndices(patternIndex, gridIndex);
    emit _iterationNumberChanged();
    emit _imageUpdated();
}

void UIBridge::resetPattern() noexcept
{
    _mainGridImageProvider->resetMainGrid();
    emit _iterationNumberChanged();
    emit _imageUpdated();
}

void UIBridge::clearPattern() noexcept
{
    // TODO data race here
    _mainGridImageProvider->clearMainGrid();
    emit _imageUpdated();
}
