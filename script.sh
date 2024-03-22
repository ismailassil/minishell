#!/bin/bash

YELLOW=$(tput setaf 3)
RESET=$(tput sgr0)

while true; do
    echo "${YELLOW}Opened file descriptor for [./minishell]${RESET}"
    lsof -c minishell | tail -n 4
    echo
    echo "${YELLOW}Leaks [./minishell]${RESET}"
    leaks minishell
    echo
    sleep 3
done
