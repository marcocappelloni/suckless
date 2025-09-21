#!/bin/bash
# In your ~/.local/bin/click_block.sh script

# Run the color script and capture its output
FG_COLOR=$(get_xresource_color "color4")
DEFAULT_COLOR=$(get_xresource_color "foreground")

# Home percent Used
percentage=$(df -h / | awk '/\/$/{print $5}')

echo "^c$FG_COLOR^ROOT: $percentage^c$DEFAULT_COLOR^"
