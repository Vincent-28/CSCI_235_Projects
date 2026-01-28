#pragma once

#include <string>

class Command {
public:
/**
 * @brief Executes the command's primary action
 * - Saves the "previous" state before execution of the action
 * - Saves the "after" state after execution of the action.
 */
    virtual void execute() = 0;

/**
 * @brief Undoes the action performed by execute()
 * typically by restoring the "previous" state.
 */
    virtual void undo() = 0;

/**
 * @brief Re-applies the action performed by execute()
 * typically by restoring the "after" state (avoiding recomputing the command).
 */
    virtual void redo() = 0;

/**
 * @brief Returns a stringified version of the command.
 * @return A const std::string describing the command.
 */
    virtual std::string toString() const = 0;

    virtual ~Command() = default;

};