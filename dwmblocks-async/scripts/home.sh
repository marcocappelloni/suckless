#!/bin/bash
# In your ~/.local/bin/click_block.sh script

# Run the color script and capture its output
FG_COLOR=$(get_xresource_color "color3")
DEFAULT_COLOR=$(get_xresource_color "foreground")

# Home percent Used
percentage=$(df -h /home | awk '/home$/{print $5}')

echo "^c$FG_COLOR^HOME: $percentage^c$DEFAULT_COLOR^"
