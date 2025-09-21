#!/bin/bash

DEFAULT_COLOR=$(get_xresource_color "foreground")

input=$(kb_status_icon)
color_code=$(echo "$input" | sed 's/\^c#\([[:xdigit:]]\{6\}\)\^.*/#\1/')
icon=$(echo "$input" | sed 's/\^c#[[:xdigit:]]\{6\}\^\(.*\)/\1/')

echo "^c$color_code^$icon^c$DEFAULT_COLOR^"
