#!/bin/bash
while true; do
    echo -e "\e[1;33mOpened file descriptor for [./minishell]\e[0m"
    lsof -c minishell | tail -n 4
    leaks minishell
    echo
    sleep 3
done
