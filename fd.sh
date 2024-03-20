#!/bin/bash

# Find the PID of the minishell process
pid=$(ps > fd && < fd grep ./minishell | awk '{print $1}' && rm -f fd)

# Check if the PID was found
if [ -n "$pid" ]; then
    echo "PID of minishell process: $pid"
    echo "Open files for minishell process:"
    lsof -p "$pid"
else
    echo "minishell process not found."
fi
