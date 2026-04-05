#include "managers/UndoManager.h"

void UndoManager::clear()
{
    while (!_records.empty())
    {
        _records.pop();
    }
}

void UndoManager::record(const UndoRecord& record)
{
    _records.push(record);
}

bool UndoManager::canUndo() const
{
    return !_records.empty();
}

UndoRecord UndoManager::popUndo()
{
    UndoRecord undoRecord;
    if (_records.empty())
        return undoRecord;

    undoRecord = _records.top();
    _records.pop();
    return undoRecord;
}
