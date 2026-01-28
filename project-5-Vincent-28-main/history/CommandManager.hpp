#pragma once

#include <stack>
#include <memory>
#include "history/Command.hpp"

class CommandManager {
private:
//A stack of std::std::shared_ptr<Command> containing all the commands that can be undone.
    std::stack<std::shared_ptr<Command>> undo_stack_;

//A stack of std::std::shared_ptr<Command> containing all the commands that can be redone.
    std::stack<std::shared_ptr<Command>> redo_stack_;

public:
/**
 * @brief Default constructor.
 */
//CommandManager::CommandManager // You can just use = default
    CommandManager() = default;

/**
 * @brief Executes a new command.
 *
 * @param command A const reference to a shared_ptr<Command> to be executed.
 * @post
 * 1. The command's execute() method is called.
 * 2. The command is pushed onto the undo stack.
 * 3. The redo stack is cleared.
 */
    void doCommand(const std::shared_ptr<Command>& command);

/**
 * @brief Undoes the most recent command.
 * @post
 * 1. If the undo stack is not empty:
 * 2. The top command is popped from the undo stack.
 * 3. The command's undo() method is called.
 * 4. The command is pushed onto the redo stack.
 */
    void undo();

/**
 * @brief Redoes the most recently undone command.
 * @post
 * 1. If the redo stack is not empty:
 * 2. The top command is popped from the redo stack.
 * 3. The command's redo() method is called.
 * 4. The command is pushed onto the undo stack.
 */
    void redo();

/**
 * @brief Checks if an undo operation is possible.
 * @return True if there are moves to be undone, false otherwise.
 */
    bool canUndo() const;

/**
 * @brief Checks if a redo operation is possible.
 * @return True if there are moves to be redone, false otherwise.
 */
    bool canRedo() const;

};