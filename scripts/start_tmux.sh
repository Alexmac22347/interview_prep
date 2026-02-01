#!/bin/bash
SESSION="neetcode"
tmux new-session -d -s $SESSION
tmux rename-window -t 0 'vim'
tmux send-keys -t 'vim' 'vim .' C-m
tmux new-window -t $SESSION:1 -n 'bash'

tmux attach-session -t $SESSION:0
