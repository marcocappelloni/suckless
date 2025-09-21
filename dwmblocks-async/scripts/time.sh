#!/bin/bash
# In your ~/.local/bin/click_block.sh script

# Run the color script and capture its output
FG_COLOR=$(get_xresource_color "color1")
DEFAULT_COLOR=$(get_xresource_color "foreground")

echo "^c$FG_COLOR^$(date '+%a %d %b %H:%M')^c$DEFAULT_COLOR^"
