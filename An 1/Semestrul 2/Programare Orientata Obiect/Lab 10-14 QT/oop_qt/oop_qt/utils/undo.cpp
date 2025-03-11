#include "undo.h"

void UndoAdauga::doUndo() {
    //Reface optiunea de adauga
    repo.destroy(addedLocatar.get_apartament(), addedLocatar.get_nume_proprietar());
}

void UndoSterge::doUndo() {
    //Reface optiunea de sterge
    repo.store(deletedLocatar);
}

void UndoModifica::doUndo() {
    //Reface optiunea de modifica
    repo.modify(oldLocatar.get_apartament(), oldLocatar.get_nume_proprietar(), oldLocatar.get_suprafata(), oldLocatar.get_tip_apartament());
}