#pragma once
#include "../domain/locatar.h"
#include "../repository/locatar_repo.h"
#include <memory>

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
    Locatar addedLocatar;
    LocatarRepository& repo;

public:
    UndoAdauga(LocatarRepository& repo, Locatar const& locatar)
            : addedLocatar(locatar), repo(repo) {}


    void doUndo() override;
};

class UndoSterge : public ActiuneUndo {
    Locatar deletedLocatar;
    LocatarRepository& repo;

public:
    UndoSterge(LocatarRepository& repo, Locatar const& locatar)
            : deletedLocatar(locatar), repo(repo) {}

    void doUndo() override;
};

class UndoModifica : public ActiuneUndo {
    Locatar oldLocatar;
    Locatar newLocatar;
    LocatarRepository& repo;

public:
    UndoModifica(LocatarRepository& repo, Locatar const& oldLoc, Locatar const& newLoc)
            : oldLocatar(oldLoc), newLocatar(newLoc), repo(repo) {}

    void doUndo() override;
};
