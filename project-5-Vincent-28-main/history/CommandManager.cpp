#include "history/CommandManager.hpp"

void CommandManager::doCommand(const std::shared_ptr<Command>& command) {
    command->execute(); //we want to call execute on the given command in order to perform it's action

    undo_stack_.push(command); //store this command into the undo stack so that we can undo it later if we need to

    while(!redo_stack_.empty()) { //while there are command that can be redone, remove them one by one
        redo_stack_.pop();
    }
}

void CommandManager::undo() {
    if(undo_stack_.empty()) { //if there is nothing to undo (empty) we just return and do nothing
        return;
    }

    std::shared_ptr<Command> topCommand = undo_stack_.top(); //grab the most recent command
    undo_stack_.pop(); //remove it from the undo stack

    topCommand->undo(); //undo the command's action (restore the previous image's state)

    redo_stack_.push(topCommand); //now we can redo this command later so we store it on the redo stack
}

void CommandManager::redo() {
    if(redo_stack_.empty()) { //if there is nothing to redo (empty), we just return and do nothing
        return;
    }

    std::shared_ptr<Command> topCommand = redo_stack_.top(); //get the most resent undone command
    redo_stack_.pop(); //remove it from the redo stack

    topCommand->redo(); //reapply the command's action. In other words, reapply filter to image

    undo_stack_.push(topCommand); //since it is now applied again, it belongs back on the undo stack
}

bool CommandManager::canUndo() const {
    return !undo_stack_.empty(); // returns true if there is at least one command to undo
}

bool CommandManager::canRedo() const {
    return !redo_stack_.empty(); // returns true if there is at least one command to redo
}